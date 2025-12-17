from fastapi import APIRouter, UploadFile, File, HTTPException, Form, WebSocket, WebSocketDisconnect, Depends
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from fastapi.responses import FileResponse, JSONResponse
from jose import JWTError, jwt
from passlib.context import CryptContext
from . import utils
from typing import List, Optional
import os
import qrcode
import socket
import io
import base64

# --- Security Configuration ---
SECRET_KEY = "a_very_secret_key_change_me" 
ALGORITHM = "HS256" 
APP_PASSWORD = "Illuminati" 

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")
oauth2_scheme = OAuth2PasswordBearer(tokenUrl="api/token", auto_error=False)

# --- Helper Functions for Auth ---
def verify_password(plain_password, hashed_password):
    return plain_password == hashed_password

def create_access_token(data: dict):
    to_encode = data.copy()
    encoded_jwt = jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)
    return encoded_jwt

async def get_current_user(token: str):
    credentials_exception = HTTPException(
        status_code=401,
        detail="Could not validate credentials",
        headers={"WWW-Authenticate": "Bearer"},
    )
    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=[ALGORITHM])
        username: Optional[str] = payload.get("sub")
        if username is None or username != "user":
            raise credentials_exception
    except JWTError:
        raise credentials_exception
    return {"username": username}

async def get_token(header_token: Optional[str] = Depends(oauth2_scheme), token: Optional[str] = None):
    if header_token:
        return header_token
    if token:
        return token
    raise HTTPException(status_code=401, detail="Not authenticated")

router = APIRouter()

# --- Token Endpoint ---
@router.post("/token")
async def login_for_access_token(form_data: OAuth2PasswordRequestForm = Depends()):
    if not verify_password(form_data.password, APP_PASSWORD):
        raise HTTPException(
            status_code=401,
            detail="Incorrect password",
            headers={"WWW-Authenticate": "Bearer"},
        )
    access_token = create_access_token(data={"sub": "user"})
    return {"access_token": access_token, "token_type": "bearer"}


# --- WebSocket Connection Manager ---
class ConnectionManager:
    # ... (No changes here)
    def __init__(self):
        self.active_connections: List[WebSocket] = []
        self.editor_content: str = ""

    async def connect(self, websocket: WebSocket):
        await websocket.accept()
        self.active_connections.append(websocket)
        await websocket.send_text(self.editor_content)

    def disconnect(self, websocket: WebSocket):
        self.active_connections.remove(websocket)

    async def broadcast(self, message: str):
        self.editor_content = message
        for connection in self.active_connections:
            await connection.send_text(message)

manager = ConnectionManager()

@router.websocket("/ws/editor")
async def websocket_endpoint(websocket: WebSocket):
    await manager.connect(websocket)
    try:
        while True:
            data = await websocket.receive_text()
            await manager.broadcast(data)
    except WebSocketDisconnect:
        manager.disconnect(websocket)

# --- PROTECTED File Sharing Routes using the unified dependency ---

@router.post("/upload/", status_code=201)
async def upload_files(files: List[UploadFile] = File(...), paths: List[str] = Form(...), token: str = Depends(get_token)):
    await get_current_user(token)
    for i, file in enumerate(files):
        if not file.filename:
            raise HTTPException(status_code=400, detail="No file name found")
        
        path = paths[i] if i < len(paths) else ""
        
        if utils.file_exists(os.path.join(path, file.filename)):
            raise HTTPException(
                status_code=409,
                detail=f"File with name '{file.filename}' already exists."
            )
        utils.save_file(file, path)

    return {"message": f"Successfully uploaded {len(files)} files"}


@router.get("/files/")
async def list_files_and_folders(token: str = Depends(get_token)):
    await get_current_user(token)
    items = utils.get_all_files_and_folders()
    if not items["files"] and not items["folders"]:
        return {"message": "No files or folders available for download."}
    return items

@router.get("/download/{item_name}")
async def download_item(item_name: str, token: str = Depends(get_token)):
    await get_current_user(token)
    item_path = utils.get_file_path(item_name)
    if not utils.file_exists(item_name):
        raise HTTPException(status_code=404, detail="Item not found")

    if os.path.isdir(item_path):
        zip_path = utils.create_zip_for_folder(item_name)
        return FileResponse(path=zip_path, media_type='application/zip', filename=f"{item_name}.zip")
    else:
        return FileResponse(path=item_path, media_type='application/octet-stream', filename=item_name)


@router.delete("/delete/{item_name}", status_code=200)
async def delete_item(item_name: str, token: str = Depends(get_token)):
    await get_current_user(token)
    if not utils.file_exists(item_name):
        raise HTTPException(status_code=404, detail="Item not found")
    utils.delete_item(item_name)
    return {"message": f"Successfully deleted {item_name}"}

@router.get("/qr-code")
async def get_qr_code():
    """
    Generates and returns the server's local URL as a Base64-encoded QR code
    and the URL string.
    """
    try:
        # Discover the local IP address
        hostname = socket.gethostname()
        ip_address = socket.gethostbyname(hostname)
        url = f"http://{ip_address}:8000"

        # Generate QR code in memory
        img = qrcode.make(url)
        
        # Save image to a memory buffer
        buffer = io.BytesIO()
        img.save(buffer, kind="png")
        buffer.seek(0)

        # Encode the image bytes to a Base64 string
        qr_code_base64 = base64.b64encode(buffer.getvalue()).decode("utf-8")
        
        # --- MODIFICATION ---
        # Return both the base64 string AND the url string
        return JSONResponse(content={
            "qr_code_base64": qr_code_base64,
            "url": url  # <-- Add this line
        })
    
    except Exception as e:
        # Handle cases where IP cannot be determined or other errors
        raise HTTPException(status_code=500, detail=f"Could not generate QR code: {e}")


@router.get("/")
async def root():
    return JSONResponse(content={"message": "Welcome to the Local File Sharer API!"})

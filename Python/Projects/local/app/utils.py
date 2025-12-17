import os
import shutil
from fastapi import HTTPException, UploadFile
import qrcode
import socket
import io
import subprocess
from pathlib import Path
import zipfile

HOME = Path.home()
UPLOAD_DIRECTORY = f"{HOME}/Downloads/srv-uploads"
ABS_UPLOAD_DIRECTORY = os.path.abspath(UPLOAD_DIRECTORY)

os.makedirs(UPLOAD_DIRECTORY, exist_ok=True)

def save_file(file: UploadFile, path: str = "") -> str:
    if not file.filename:
        raise HTTPException(status_code=400, detail="No file name found")
    
    safe_filename = os.path.basename(file.filename)
    if not safe_filename:
         raise HTTPException(status_code=400, detail="Invalid file name")

    # Create the full path for the destination directory
    dest_dir = os.path.abspath(os.path.join(ABS_UPLOAD_DIRECTORY, path))
    
    # Ensure the final path is within the UPLOAD_DIRECTORY
    if not dest_dir.startswith(ABS_UPLOAD_DIRECTORY):
        raise HTTPException(status_code=400, detail="Invalid path specified")

    # The final path for the file itself
    file_path = os.path.join(dest_dir, safe_filename)
    
    # Create the subdirectory if it doesn't exist
    os.makedirs(os.path.dirname(file_path), exist_ok=True)
    
    with open(file_path, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)
    return file_path

# The rest of your utils.py file remains the same...
def get_file_path(filename: str) -> str:
    return os.path.join(UPLOAD_DIRECTORY, filename)

def file_exists(filename: str) -> bool:
    return os.path.exists(get_file_path(filename))

def get_all_files_and_folders() -> dict:
    items = os.listdir(UPLOAD_DIRECTORY)
    files = [item for item in items if os.path.isfile(os.path.join(UPLOAD_DIRECTORY, item))]
    folders = [item for item in items if os.path.isdir(os.path.join(UPLOAD_DIRECTORY, item))]
    return {"files": files, "folders": folders}

def delete_item(item_name: str):
    item_path = get_file_path(item_name)
    if os.path.isfile(item_path):
        os.remove(item_path)
    elif os.path.isdir(item_path):
        shutil.rmtree(item_path)

def create_zip_for_folder(folder_name: str) -> str:
    folder_path = get_file_path(folder_name)
    zip_path = f"/tmp/{folder_name}.zip"
    with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for root, _, files in os.walk(folder_path):
            for file in files:
                file_path = os.path.join(root, file)
                arcname = os.path.relpath(file_path, folder_path)
                zipf.write(file_path, arcname)
    return zip_path


def print_ip_and_qr():
    url = f"http://{socket.gethostbyname(socket.gethostname())}:8000"
    img = qrcode.make(url)
    buffer = io.BytesIO()
    img.save(buffer, kind="png")
    image_data = buffer.getvalue()
    try:
        subprocess.run(
            ["kitty", "+kitten", "icat"], 
            input=image_data, 
            check=True
        )
    except FileNotFoundError:
        print("kitty terminal not found, skipping QR code display.")
    print(f"URL: {url}")
    return url

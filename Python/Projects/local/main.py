import subprocess
import uvicorn
from fastapi import FastAPI, HTTPException
from fastapi.staticfiles import StaticFiles
from fastapi.responses import FileResponse
from app.utils import print_ip_and_qr
from app.routes import router as api_router
import os
import asyncio

app = FastAPI(
    title="Local File Sharer",
    description="A simple API to share files over a local network.",
    version="1.0.0"
)

# Include your API routes (e.g., /upload, /files, etc.)
# We prefix them with /api to avoid conflicts with frontend routes
app.include_router(api_router, prefix="/api")

# Define the directory where the built React app is located
STATIC_FILES_DIR = "/home/Vatsal/Codes/Python/Projects/local/dist"

# Mount the 'assets' directory from the build folder
app.mount(
    "/assets",
    StaticFiles(directory=os.path.join(STATIC_FILES_DIR, "assets")),
    name="assets"
)

# A catch-all route to serve the index.html for any other path
# This is crucial for single-page applications like React
@app.get("/{full_path:path}", response_class=FileResponse)
# async def serve_react_app(full_path: str):
async def serve_react_app():
    index_path = os.path.join(STATIC_FILES_DIR, "index.html")
    if not os.path.exists(index_path):
        raise HTTPException(status_code=404, detail="Frontend build not found.")
    return FileResponse(index_path)

async def after_server_start():
    url = print_ip_and_qr()
    try:
        subprocess.run(["firefox", url])
    except FileNotFoundError:
        print("firefox not found")
    await asyncio.sleep(1)

class CustomServer(uvicorn.Server):
    async def startup(self, sockets=None):
        await super().startup(sockets)
        asyncio.create_task(after_server_start())

async def main():
    config = uvicorn.Config("main:app", host="0.0.0.0", port=8000, log_level="info")
    server = CustomServer(config)
    try:
        await server.serve()
    except asyncio.CancelledError:
        pass

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

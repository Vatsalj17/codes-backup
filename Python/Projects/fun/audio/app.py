from fastapi import FastAPI, UploadFile
import os
import tempfile
import subprocess
import json
from vosk import Model, KaldiRecognizer

def transcribe_audio(input_path: str, model_path: str, sample_rate: int = 16000) -> str:
    ffmpeg_cmd = [
        "ffmpeg", "-i", input_path,
        "-ar", str(sample_rate),      # resample
        "-ac", "1",                   # mono
        "-f", "s16le",                # 16-bit PCM
        "-"                           # output to stdout
    ]

    process = subprocess.Popen(ffmpeg_cmd, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    model = Model(model_path)
    rec = KaldiRecognizer(model, sample_rate)
    full_text = []
    assert process.stdout is not None  # For type checkers
    while True:
        data = process.stdout.read(4000)
        if len(data) == 0:
            break
        if rec.AcceptWaveform(data):
            result = json.loads(rec.Result())
            if "text" in result:
                full_text.append(result["text"])
        else:
            pass

    final_result = json.loads(rec.FinalResult())
    if "text" in final_result:
        full_text.append(final_result["text"])

    return " ".join(full_text)

app = FastAPI()

@app.get("/")
async def root():
    return {"message": "Hello World"}

@app.post("/transcribe/")
async def create_upload_file(file: UploadFile | None = None):
    if not file:
        return {"message": "No upload file sent"}

    filename = file.filename or ""
    ext = os.path.splitext(filename)[1] or ".tmp"

    with tempfile.NamedTemporaryFile(delete=False, suffix=ext) as tmp:
        tmp.write(await file.read())
        tmp_path = tmp.name

    model = "/home/Vatsal/Codes/Python/fun/audio/vosk-model-small-en-us-0.15"
    text = transcribe_audio(tmp_path, model)
    return {"filename": file.filename, "text": text}

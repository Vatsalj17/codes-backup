import sys
import pytesseract
import pyperclip
from PIL import ImageGrab, Image

def main():
    try:
        # Grab image from clipboard
        img = ImageGrab.grabclipboard()
        if img is None:
            print("No image found in clipboard.")
            sys.exit(0)

        # Extract text using Tesseract
        text = pytesseract.image_to_string(img)

        # Print to terminal
        print("\nExtracted Text:\n" + "-"*50)
        print(text.strip())
        print("-"*50)

        # Copy to clipboard
        pyperclip.copy(text.strip())
        print("\n✅ Text copied to clipboard!")

    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    main()

import os

def unit_4_masterclass():
    """
    A complete demonstration of Python File Operations (Unit 4).
    Topics: File Modes, Read/Write primitives, Buffering, Seek/Tell, and Exception Handling.
    """
    print("--- 🐍 UNIT 4: ADVANCED FILE OPERATIONS MASTERCLASS ---\n")

    # ==================================================================================
    # PART 1: THE BASICS - WRITING & FILE DESCRIPTORS
    # ==================================================================================
    # In C (which you know), opening a file returns a file descriptor (an integer).
    # Python's open() returns a file object (TextIOWrapper) that wraps this descriptor.
    # [cite: 359, 360]
    
    filename = "engineering_logs.txt"
    
    print(f"[1] Creating and writing to '{filename}' using Write Mode ('w')...")
    # 'w' mode opens for writing. IMPORTANT: It truncates (wipes) the file if it exists! 
    
    file_obj = open(filename, "w") 
    
    # Writing string data into the buffer
    file_obj.write("Log Entry 1: System Booted.\n") 
    
    # writelines() takes an iterable (list) of strings. It does NOT add newlines automatically. [cite: 406]
    lines_data = ["Log Entry 2: Kernel loaded.\n", "Log Entry 3: Drivers initialized.\n"]
    file_obj.writelines(lines_data)
    
    # BONUS FACT: Data isn't always written to disk immediately; it sits in a buffer.
    # close() flushes the buffer to the disk and releases the file descriptor. [cite: 398]
    file_obj.close() 
    print("    -> File created and data written successfully.\n")


    # ==================================================================================
    # PART 2: READING PRIMITIVES & MEMORY MANAGEMENT
    # ==================================================================================
    print(f"[2] Reading strategies for '{filename}'...")

    # Strategy A: read() - Reads the ENTIRE file into memory. 
    # Engineer's Note: Dangerous for large files (GBs) as it can cause Out Of Memory (OOM). [cite: 373]
    file_obj = open(filename, "r")
    full_content = file_obj.read()
    print(f"    [A] read() output (Raw):\n{repr(full_content)}")
    file_obj.close()

    # Strategy B: readline() - Reads a single line (up to \n). Memory efficient. [cite: 374, 386]
    file_obj = open(filename, "r")
    line1 = file_obj.readline()
    print(f"    [B] readline() first call: {line1.strip()}")
    file_obj.close()

    # Strategy C: readlines() - Reads all lines into a Python LIST. [cite: 375]
    file_obj = open(filename, "r")
    lines_list = file_obj.readlines()
    print(f"    [C] readlines() output type: {type(lines_list)}")
    print(f"        Data: {lines_list}")
    file_obj.close()
    print()


    # ==================================================================================
    # PART 3: THE 'WITH' STATEMENT (CONTEXT MANAGERS)
    # ==================================================================================
    # Low-Level Insight: The 'with' statement uses the __enter__() and __exit__() magic methods.
    # It ensures the file descriptor is closed even if an error crashes the code block. [cite: 401, 402]
    
    print("[3] Appending data using Context Manager ('with' statement)...")
    
    # 'a' mode: Append. Moves the pointer to the end immediately. Does not truncate. [cite: 362, 394]
    with open(filename, "a") as f:
        f.write("Log Entry 4: User 'Vatsal' logged in via Hyprland.\n")
        print("    -> Data appended securely.")
    print()


    # ==================================================================================
    # PART 4: MANIPULATING THE FILE POINTER (SEEK & TELL)
    # ==================================================================================
    # This is where we get into random access—crucial for database systems or reading binary headers.
    # tell() returns current byte position. seek(offset, whence) moves it. [cite: 407, 416]

    print("[4] Manipulating File Pointers (The Low-Level Stuff)...")
    
    with open(filename, "r") as f:
        # Initial position
        print(f"    Initial Pointer Position: {f.tell()} bytes") # [cite: 435]
        
        # Read first 10 bytes
        chunk = f.read(10)
        print(f"    Read 10 bytes: '{chunk}'")
        print(f"    Current Pointer Position: {f.tell()} bytes") # [cite: 437]
        
        # SEEK OPERATION [cite: 414, 446]
        # Move pointer to the 5th byte from the beginning
        print("    -> Executing f.seek(5)...")
        f.seek(5) 
        print(f"    New Pointer Position: {f.tell()} bytes")
        rest_of_line = f.readline()
        print(f"    Reading from new position: '{rest_of_line.strip()}'")

        # SEEK FROM END (Reading logs in reverse/tailing a file) 
        # In text mode ('r'), Python insists on seek from start (0). 
        # For relative seeking (1 or 2), you usually need binary mode ('rb').
        # However, seek(0, 2) is allowed in text mode to jump to the very end.
        f.seek(0, 2) 
        print(f"    Jumped to EOF. Total File Size: {f.tell()} bytes") # [cite: 500]
    print()


    # ==================================================================================
    # PART 5: OS MODULE & ROBUST ERROR HANDLING
    # ==================================================================================
    # Engineering requires checking preconditions. Don't just open a file; check if it exists.
    
    target_file = "missing_driver.conf"
    print(f"[5] Robust Handling with '{target_file}'...")

    # Using OS module to check existence before removal [cite: 196]
    if os.path.exists(target_file):
        os.remove(target_file)
    
    # Try/Except block for File I/O [cite: 212, 299]
    try:
        # Trying to read a file that doesn't exist
        with open(target_file, "r") as f:
            _ = f.read()
    except FileNotFoundError as e:
        # This catches Errno 2 [cite: 112]
        print(f"    [ERROR CAUGHT] Exception type: {type(e).__name__}")
        print(f"    System message: {e}")
        print("    -> This prevents the program from crashing (Segfault/Abort in C terms).")
    finally:
        # finally runs regardless of error - good for cleanup
        print("    -> 'finally' block executed. Cleanup complete.")

    # Cleanup our demo file
    if os.path.exists(filename):
        os.remove(filename) # [cite: 201]
        print(f"\n[Cleanup] Removed '{filename}'. Demo complete.")

# Executing the masterclass
if __name__ == "__main__":
    unit_4_masterclass()

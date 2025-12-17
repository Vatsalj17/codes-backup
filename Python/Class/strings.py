def unit_3_strings_masterclass():
    """
    A comprehensive deep-dive into Python Strings (Unit 3).
    Demonstrating memory internals, slicing mechanics, and 15+ essential methods.
    """
    print("--- 🐍 UNIT 3: ADVANCED STRING OPERATIONS & INTERNALS ---\n")

    # ==================================================================================
    # PART 1: THE BASICS & MEMORY INTERNALS (C Engineer Perspective)
    # ==================================================================================
    # In C: char s[] = "hello"; (mutable, ends with \0)
    # In Python: PyObject (immutable, stores length, hash, and pointer to data)
    
    print("[1] Memory & Immutability Analysis...")
    s1 = "archlinux"
    s2 = "archlinux"
    
    # String Interning: Python reuses small/common immutable objects to save memory.
    # Check 'id()' to see the memory address.
    print(f"    s1 id: {id(s1)}, s2 id: {id(s2)}")
    print(f"    Are they the same object? {s1 is s2}") 
    
    # Immutability check
    try:
        s1[0] = 'A' # pyright: ignore
        # This would work in C (s1[0] = 'A'), but raises TypeError in Python
    except TypeError as e:
        print(f"    [Error] Mutation failed as expected: {e}")
        print("    -> Python strings are immutable (essential for Dict keys hashing).\n")


    # ==================================================================================
    # PART 2: SLICING MECHANICS (Pointer Arithmetic Abstraction)
    # ==================================================================================
    # Syntax: string[start:stop:step]
    
    print("[2] Advanced Slicing Techniques...")
    kernel = "vmlinuz-linux-zen"
    
    print(f"    Original: '{kernel}'")
    print(f"    [0:7]   (Head):      '{kernel[0:7]}'")
    print(f"    [-3:]   (Tail):      '{kernel[-3:]}'")
    print(f"    [::2]   (Step):      '{kernel[::2]}'  (Skipping every 2nd char)")
    print(f"    [::-1]  (Reverse):   '{kernel[::-1]}' (Classic interview one-liner)")
    print(f"    [8:13]  (Middle):    '{kernel[8:13]}'")
    print(f"    [::-2]  (Rev Step):  '{kernel[::-2]}'")
    print("    -> Note: Slicing creates a NEW copy of the string (unlike C pointers/views).\n")


    # ==================================================================================
    # PART 3: THE 15+ ESSENTIAL METHODS (Categorized)
    # ==================================================================================
    
    text = "  sudo Pacman -Syu  "
    print(f"[3] Essential String Methods (Original: '{text}')")
    
    # --- Category A: Cleaning & Normalization ---
    clean = text.strip() # Removes leading/trailing whitespace (like trimming in C)
    print(f"    1. strip():      '{clean}'")
    print(f"    2. lower():      '{clean.lower()}'")
    print(f"    3. upper():      '{clean.upper()}'")
    print(f"    4. title():      '{clean.title()}' (CamelCase-ish)")
    print(f"    5. swapcase():   '{clean.swapcase()}'")
    print(f"    6. casefold():   '{clean.casefold()}' (Aggressive lower for Unicode matching)")

    # --- Category B: Searching & Inspecting ---
    sentence = "compile the kernel with gcc"
    print(f"\n    Analyzing: '{sentence}'")
    print(f"    7. find('kern'):  {sentence.find('kern')} (Returns index, -1 if missing)")
    print(f"    8. count('e'):    {sentence.count('e')} (Frequency analysis)")
    print(f"    9. startswith():  {sentence.startswith('comp')} (Bool check)")
    print(f"    10. endswith():   {sentence.endswith('gcc')} (File extension checks)")
    
    # --- Category C: Modification & Assembly ---
    # Performance Note: 'join' is O(n), loop concatenation is O(n^2)
    words = ["usr", "bin", "env", "python"]
    path = "/".join(words)
    print(f"\n    11. join():       '{path}' (Optimized concatenation)")
    
    split_path = path.split("/")
    print(f"    12. split():      {split_path} (Tokenizing)")
    
    # replace() is efficient, replaces all occurrences by default
    config = "Resolution=1920x1080"
    print(f"    13. replace():    '{config.replace('1920', '2560')}'")
    
    # --- Category D: Alignment & Formatting (TUI/CLI helpers) ---
    print(f"\n    14. center():     '|{'Title'.center(10)}|'")
    print(f"    15. ljust():      '|{'Item'.ljust(10)}|'")
    print(f"    16. zfill():      '{'42'.zfill(5)}' (Binary/Hex padding)")
    
    # --- Category E: Checks (Validation) ---
    print(f"\n    17. isdigit():    '123'.isdigit() -> {'123'.isdigit()}")
    print(f"    18. isalpha():    'Arch'.isalpha() -> {'Arch'.isalpha()}")
    print(f"    19. isalnum():    'v3'.isalnum() -> {'v3'.isalnum()}")


    # ==================================================================================
    # PART 4: BONUS - UNICODE & ENCODING (The "Network Engineer" Stuff)
    # ==================================================================================
    # Since you work with Sockets/TCP, you know the wire only understands bytes.
    # Python 3 strings are Unicode. They MUST be encoded to bytes for networking.
    
    print("\n[4] Encoding/Decoding (Bytes vs Strings)...")
    payload_str = "Héllø"
    payload_bytes = payload_str.encode('utf-8') # Converting to bytes for network xmission
    
    print(f"    String: '{payload_str}' (Len: {len(payload_str)})")
    print(f"    Bytes:  {payload_bytes} (Len: {len(payload_bytes)})") 
    print(f"    -> Notice length increased! (UTF-8 is variable width: 1-4 bytes)")
    print(f"    Decoded: '{payload_bytes.decode('utf-8')}'")
    

    # ==================================================================================
    # PART 5: FORMATTING (f-strings)
    # ==================================================================================
    print("\n[5] Advanced Formatting...")
    pkg = "htop"
    ver = 3.2
    # f-strings evaluate expressions at runtime (fastest method)
    print(f"    Status: Installing {pkg.upper()} v{ver:.2f}...")

if __name__ == "__main__":
    unit_3_strings_masterclass()

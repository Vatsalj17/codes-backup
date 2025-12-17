import sys
from collections import namedtuple

def unit_3_tuples_masterclass():
    """
    A comprehensive deep-dive into Python Tuples (Unit 3).
    Demonstrating Struct-like behavior, Memory Optimization, and Immutability Traps.
    """
    print("--- 🐍 UNIT 3: ADVANCED TUPLE OPERATIONS & INTERNALS ---\n")

    # ==================================================================================
    # PART 1: MEMORY & PERFORMANCE (The "Static Block" Advantage)
    # ==================================================================================
    # Engineering Insight: Tuples are stored in a single fixed memory block.
    # Lists need two blocks: one for the object, one for the pointers to data.
    
    print("[1] Memory Optimization Analysis...")
    data_list = [10, 20, 30, 40, 50]
    data_tuple = (10, 20, 30, 40, 50)
    
    print(f"    List Size:  {sys.getsizeof(data_list)} bytes (Dynamic overhead)")
    print(f"    Tuple Size: {sys.getsizeof(data_tuple)} bytes (Static compact)")
    print("    -> Tuples have less overhead because they don't need 'extra' slots for resizing.\n")


    # ==================================================================================
    # PART 2: PACKING & UNPACKING (Destructuring)
    # ==================================================================================
    # This is the most "Pythonic" feature, heavily used in function returns.
    
    print("[2] Packing and Unpacking (The Swap Logic)...")
    
    # 1. Packing: Implicit tuple creation
    coordinates = 1920, 1080 # Parentheses are optional!
    print(f"    Packed: {coordinates} (Type: {type(coordinates)})")
    
    # 2. Unpacking: Assigning to variables
    w, h = coordinates
    print(f"    Unpacked: Width={w}, Height={h}")
    
    # 3. The C-style Swap (Under the hood, this uses a temporary tuple)
    a, b = 5, 10
    a, b = b, a 
    print(f"    Swapped: a={a}, b={b}")
    
    # 4. Extended Unpacking (The '*' operator - like 'rest' in Rust/JS)
    kernel_ver = (6, 8, 9, "arch1", "1")
    major, minor, *patch_details = kernel_ver
    print(f"    Extended: Major={major}, Rest={patch_details}\n")


    # ==================================================================================
    # PART 3: IMMUTABILITY & THE "CONTAINER" TRAP
    # ==================================================================================
    # Critical Systems Concept: Shallow Immutability.
    # The tuple holds POINTERS. You can't change the pointer, but if the pointer
    # points to a mutable object (like a list), THAT object can change.
    
    print("[3] The 'Immutable' Trap...")
    
    # A tuple containing a list
    hybrid = (1, 2, ["Standard", "User"]) 
    
    print(f"    Original: {hybrid}")
    
    try:
        hybrid[0] = 99 # pyright: ignore
        # Error: Cannot change the tuple's slot
    except TypeError:
        print("    -> Direct assignment failed (Expected).")
        
    # BUT, we can modify the list INSIDE the tuple
    hybrid[2].append("Admin") 
    print(f"    Mutated:  {hybrid}")
    print("    -> WARNING: The tuple contents changed because the inner list is mutable!\n")


    # ==================================================================================
    # PART 4: OPERATIONS & METHODS (The Limited Toolset)
    # ==================================================================================
    # Tuples are lean. They only have 2 public methods.
    
    print("[4] Essential Operations...")
    t = (1, 2, 3, 2, 4, 2)
    
    # 1. count(x) - Frequency
    print(f"    1. count(2):      {t.count(2)}")
    
    # 2. index(x) - Location
    print(f"    2. index(4):      {t.index(4)}")
    
    # 3. Concatenation (+)
    t_new = t + (5, 6)
    print(f"    3. Concat:        {t_new}")
    
    # 4. Repetition (*)
    print(f"    4. Repeat:        {('Ack',) * 3}")
    
    # 5. Membership (in)
    print(f"    5. Contains 3?    {3 in t}")
    
    # 6. Slicing (Same as lists, returns NEW tuple)
    print(f"    6. Slice [::-1]:  {t[::-1]}\n")


    # ==================================================================================
    # PART 5: THE SINGLETON TUPLE QUIRK
    # ==================================================================================
    # A common bug source in configuration files.
    
    print("[5] The Singleton Syntax...")
    not_tuple = ("hello") # This is just a string in parentheses (math grouping)
    real_tuple = ("hello",) # The COMMA makes it a tuple
    
    print(f"    ('x'):  Type is {type(not_tuple)}")
    print(f"    ('x',): Type is {type(real_tuple)}\n")


    # ==================================================================================
    # PART 6: NAMED TUPLES (The True C-Struct)
    # ==================================================================================
    # Using 'collections.namedtuple' to create readable, struct-like objects.
    # Very popular in database APIs and network parsers.
    
    print("[6] NamedTuples (Engineering Best Practice)...")
    
    # Define the "Struct"
    Process = namedtuple('Process', ['pid', 'name', 'status'])
    
    # Instantiate
    p1 = Process(pid=101, name="systemd", status="running")
    
    print(f"    Struct Representation: {p1}")
    print(f"    Access by Name:        {p1.name} (PID: {p1.pid})")
    print(f"    Access by Index:       {p1[0]} (Backward compatible)")

if __name__ == "__main__":
    unit_3_tuples_masterclass()

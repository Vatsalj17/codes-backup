import sys
import copy

def unit_3_lists_masterclass():
    """
    A comprehensive deep-dive into Python Lists (Unit 3).
    Demonstrating dynamic array internals, memory management, and advanced comprehension.
    """
    print("--- 🐍 UNIT 3: ADVANCED LIST OPERATIONS & INTERNALS ---\n")

    # ==================================================================================
    # PART 1: THE BASICS & MEMORY INTERNALS (C Engineer Perspective)
    # ==================================================================================
    # In C: int arr[5]; (Fixed size, same type, contiguous memory for VALUES)
    # In Python: Dynamic array of POINTERS (PyObject*).
    
    print("[1] Memory & Dynamic Resizing...")
    my_list = []
    print(f"    Empty list size: {sys.getsizeof(my_list)} bytes (Overhead structure)")

    # Demonstrating amortized O(1) appending
    # Python over-allocates memory to avoid realloc() on every append.
    for i in range(5):
        my_list.append(i)
        print(f"    Items: {len(my_list)} | Size in RAM: {sys.getsizeof(my_list)} bytes")
    print("    -> Notice the size jumps in chunks? That's the over-allocation strategy.\n")


    # ==================================================================================
    # PART 2: SLICING & MODIFICATION
    # ==================================================================================
    # Slicing lists works just like strings, but lists are MUTABLE.
    
    print("[2] Slicing & Mutable Operations...")
    kernel_modules = ["nvidia", "i915", "e1000e", "usb_storage", "snd_hda_intel"]
    
    print(f"    Original: {kernel_modules}")
    print(f"    [1:3]     (Slice):  {kernel_modules[1:3]}")
    
    # Advanced: Slice Assignment (Replacing a chunk of the list in-place)
    kernel_modules[1:3] = ["amdgpu", "iwlwifi"] 
    print(f"    Modified: {kernel_modules} (Replaced 'i915' & 'e1000e')")
    
    # Deleting via slice
    del kernel_modules[::2]
    print(f"    Deleted every 2nd: {kernel_modules}\n")


    # ==================================================================================
    # PART 3: THE ESSENTIAL METHODS (Stack/Queue behavior)
    # ==================================================================================
    print("[3] Essential Methods (Stack & Queue Ops)...")
    stack = [10, 20, 30]
    
    # 1. append(x) - Push to stack
    stack.append(40)
    print(f"    1. append(40):   {stack}")
    
    # 2. extend(iterable) - Concatenation (faster than + operator)
    stack.extend([50, 60])
    print(f"    2. extend(...):  {stack}")
    
    # 3. insert(i, x) - O(n) operation! (Shifts elements)
    stack.insert(0, 5)
    print(f"    3. insert(0,5):  {stack}")
    
    # 4. remove(x) - Removes first occurrence
    stack.remove(60)
    print(f"    4. remove(60):   {stack}")
    
    # 5. pop([i]) - Returns and removes element. O(1) at end, O(n) at start.
    popped = stack.pop()
    print(f"    5. pop():        {stack} (Popped: {popped})")
    
    # 6. index(x) - Linear search
    idx = stack.index(20)
    print(f"    6. index(20):    Found at index {idx}")
    
    # 7. count(x) - Frequency
    print(f"    7. count(5):     {stack.count(5)}")
    
    # 8. sort() - Timsort algorithm (highly optimized stable sort)
    stack.sort(reverse=True)
    print(f"    8. sort(rev):    {stack}")
    
    # 9. reverse() - In-place reversal
    stack.reverse()
    print(f"    9. reverse():    {stack}")
    
    # 10. clear() - Wipe content, keep object identity
    stack.clear()
    print(f"    10. clear():     {stack}\n")


    # ==================================================================================
    # PART 4: LIST COMPREHENSION (The Pythonic "Map/Filter")
    # ==================================================================================
    # Syntax: [expression for item in iterable if condition]
    # This is compiled to C-speed bytecodes, faster than a Python 'for' loop.
    
    print("[4] List Comprehension (Engineering Syntax)...")
    raw_data = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    
    # Filtering even numbers (The C way would take 4 lines)
    evens = [x for x in raw_data if x % 2 == 0] # [cite: 282, 287, 292]
    print(f"    Evens (Filter):  {evens}")
    
    # Mapping (Squaring)
    squares = [x**2 for x in raw_data] # [cite: 317]
    print(f"    Squares (Map):   {squares}")
    
    # Nested Comprehension (Flattening a 2D matrix)
    matrix = [[1, 2], [3, 4], [5, 6]]
    flat = [num for row in matrix for num in row]
    print(f"    Flattened:       {flat}\n")


    # ==================================================================================
    # PART 5: THE SHALLOW COPY TRAP (Crucial for System Devs)
    # ==================================================================================
    # In C, copying a pointer != copying the data. Same in Python.
    
    print("[5] Deep vs Shallow Copy (The Trap)...")
    original = [[1, 2], [3, 4]]
    
    # Shallow Copy
    shallow = original.copy() # or list(original) or original[:]
    
    # Modifying the NESTED object
    shallow[0][0] = 999
    
    print(f"    Original: {original}")
    print(f"    Shallow:  {shallow}")
    print("    -> WOAH! Changing 'shallow' changed 'original' because they share inner pointers.")
    
    # Deep Copy (The fix)
    deep = copy.deepcopy(original)
    deep[0][0] = 777
    print(f"    Deep Mod: {deep}")
    print(f"    Original: {original} (Safe!)")

if __name__ == "__main__":
    unit_3_lists_masterclass()

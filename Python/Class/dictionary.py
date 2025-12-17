import sys

def unit_3_dictionaries_masterclass():
    """
    A comprehensive deep-dive into Python Dictionaries (Unit 3).
    Demonstrating Hash Table mechanics, Views, Comprehension, and Optimization.
    """
    print("--- 🐍 UNIT 3: ADVANCED DICTIONARY OPERATIONS & INTERNALS ---\n")

    # ==================================================================================
    # PART 1: THE INTERNALS (Hash Tables & Layout)
    # ==================================================================================
    # Engineering Insight:
    # Python dicts used to be sparse arrays. Now (Python 3.6+), they are "compact".
    # They split storage into:
    #   1. Indices Array: [None, 0, None, 1, ...] (Sparse, small integers)
    #   2. Entries Array: [[hash, key, value], [hash, key, value]] (Dense)
    # This saves 20-25% RAM compared to older Python versions.
    
    print("[1] Creation & Memory Overhead...")
    # Literal syntax (Faster than dict() constructor due to bytecode optimization)
    server_config = {
        "host": "127.0.0.1",
        "port": 8080,
        "debug": True
    }
    
    print(f"    Config: {server_config}")
    print(f"    Size:   {sys.getsizeof(server_config)} bytes (Base overhead)")
    
    # dict() constructor (Good for converting lists of tuples)
    headers_list = [("Content-Type", "application/json"), ("Authorization", "Bearer X")]
    headers_dict = dict(headers_list)
    print(f"    From List: {headers_dict}\n")


    # ==================================================================================
    # PART 2: ACCESS PATTERNS (Safety vs Speed)
    # ==================================================================================
    print("[2] Access Methods (Handling Missing Keys)...")
    
    # 1. Direct Access (Fastest, but risky)
    try:
        print(f"    Direct: {server_config['timeout']}")
    except KeyError:
        print("    -> Direct access failed (KeyError) - standard C-style crash.")

    # 2. .get(key, default) - The Engineering Standard
    # Returns None (or specified default) instead of crashing.
    timeout = server_config.get("timeout", 60) # Default to 60s if missing
    print(f"    .get(): {timeout} (Safe fallback)")
    
    # 3. .setdefault(key, default) - The "Cache Miss" Helper
    # If key exists, return value. If not, SET it to default and return it.
    val = server_config.setdefault("retry_count", 3)
    print(f"    .setdefault(): {server_config['retry_count']} (Added because it was missing)\n")


    # ==================================================================================
    # PART 3: MODERN MERGING & UPDATING
    # ==================================================================================
    print("[3] Merging & Union Operators...")
    defaults = {"theme": "dark", "notifications": True, "cache": False}
    user_prefs = {"theme": "light", "cache": True} # User overrides
    
    # 1. .update() - In-place modification (Old school)
    temp = defaults.copy()
    temp.update(user_prefs)
    print(f"    1. .update(): {temp}")
    
    # 2. The Union Operator '|' (Python 3.9+) - Clean & Functional
    # Merges two dicts into a NEW one. Right side wins conflicts.
    merged = defaults | user_prefs 
    print(f"    2. Union (|): {merged} (Preferred in modern Python)")
    
    # 3. Unpacking (**) - The "Hack" way
    merged_hack = {**defaults, **user_prefs}
    print(f"    3. Unpacking: {merged_hack}\n")


    # ==================================================================================
    # PART 4: VIEW OBJECTS (Dynamic Links)
    # ==================================================================================
    # In Python 2, keys() returned a static List. In Python 3, it returns a View.
    # A View is a dynamic window into the dict. If dict changes, View changes.
    
    print("[4] Dictionary Views (Dynamic Windows)...")
    d = {"a": 1, "b": 2}
    keys_view = d.keys() # Not a list! A 'dict_keys' object.
    
    print(f"    View before: {list(keys_view)}")
    d["c"] = 3 # Modify dict
    print(f"    View after:  {list(keys_view)} (It updated automatically!)")
    
    # Set Operations on Views (Keys behave like Sets!)
    d1 = {"a": 1, "b": 2}
    d2 = {"b": 3, "c": 4}
    print(f"    Common Keys: {d1.keys() & d2.keys()} (Intersection)\n")


    # ==================================================================================
    # PART 5: DICTIONARY COMPREHENSION (From Syllabus)
    # ==================================================================================
    # Syntax: {k:v for item in iterable}
    
    print("[5] Dictionary Comprehension...")
    users = ["vatsal", "root", "daemon"]
    # Create map of User -> UID (arbitrary logic)
    uid_map = {name: idx + 1000 for idx, name in enumerate(users)}
    
    print(f"    User Map: {uid_map}")
    
    # Filtering: Keep only users with 'a' in name
    filtered = {k: v for k, v in uid_map.items() if 'a' in k}
    print(f"    Filtered: {filtered}\n")


    # ==================================================================================
    # PART 6: THE HASHABILITY TRAP (Key Constraints)
    # ==================================================================================
    # Keys MUST be immutable (hashable). Values can be anything.
    
    print("[6] The Hashability Constraint...")
    
    try:
        # Lists are mutable -> Unhashable -> Cannot be keys
        my_dict = {[1, 2]: "List Key"} # pyright: ignore
    except TypeError as e:
        print(f"    Error: {e} (Lists cannot be keys)")
        
    # Tuples are immutable -> Hashable -> Can be keys
    # Useful for coordinate maps or sparse matrices
    valid_dict = {(1920, 1080): "FullHD", (3840, 2160): "4K"}
    print(f"    Tuple Keys: {valid_dict[(1920, 1080)]} (Works!)\n")

    # ==================================================================================
    # PART 7: ITERATION MECHANICS
    # ==================================================================================
    print("[7] Iteration Best Practices...")
    target = {"cpu": "i7-13620H", "ram": "16GB", "distro": "Arch"}
    
    # 1. Iterating keys (Default)
    print("    Keys:", end=" ")
    for k in target: # Implicitly calls target.keys()
        print(k, end=" ")
    print()
        
    # 2. Iterating items (Key+Value) - Most common
    print("    Items:")
    for k, v in target.items():
        print(f"      -> {k}: {v}")

if __name__ == "__main__":
    unit_3_dictionaries_masterclass()

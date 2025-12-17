import timeit

def unit_3_sets_masterclass():
    """
    A comprehensive deep-dive into Python Sets (Unit 3).
    Demonstrating Hash Table internals, Mathematical Operations, and Optimization.
    """
    print("--- 🐍 UNIT 3: ADVANCED SET OPERATIONS & INTERNALS ---\n")

    # ==================================================================================
    # PART 1: THE INTERNALS (Hash Tables & Uniqueness)
    # ==================================================================================
    # Engineering Concept: A set eliminates duplicates by checking hash collisions.
    # If hash(a) == hash(b), Python checks if a == b. If both true, it's a duplicate.
    
    print("[1] Hash Table Internals & The 'Bool-Int' Trap...")
    
    # TRAP: True is 1, False is 0 in Python's boolean algebra.
    # They hash to the same value!
    trap_set = {1, True, 1.0, "1"} 
    
    print(f"    Raw inputs: {{1, True, 1.0, '1'}}")
    print(f"    Result:     {trap_set}")
    print(f"    -> Why? hash(1) == {hash(1)} and hash(True) == {hash(True)}")
    print("    -> Python treats 1, 1.0, and True as the same key in the Hash Map.\n")


    # ==================================================================================
    # PART 2: CREATION & IMMUTABILITY (Frozen Sets)
    # ==================================================================================
    print("[2] Mutability vs Immutability...")
    
    # 1. Standard Set (Mutable)
    mutable_set = {1, 2, 3}
    mutable_set.add(4)
    
    # 2. The Empty Set Trap
    empty = {} # This is a DICT, not a set!
    real_empty = set()
    print(f"    type({{}}):      {type(empty)} (Trap!)")
    print(f"    type(set()):   {type(real_empty)} (Correct)")
    
    # 3. Frozenset (Immutable - Hashable)
    # You cannot put a set inside a set (because sets are mutable/unhashable).
    # You MUST use frozenset if you need nested sets.
    try:
        nested_fail = {{1, 2}, {3, 4}} # pyright: ignore
    except TypeError as e:
        print(f"    Error: {e} (Cannot nest mutable sets)")
        
    valid_nested = {frozenset({1, 2}), frozenset({3, 4})}
    print(f"    Nested Frozenset: {valid_nested}\n")


    # ==================================================================================
    # PART 3: MATHEMATICAL OPERATIONS (Bitwise Syntax)
    # ==================================================================================
    # As a C coder, you'll love this. Python overloads bitwise operators for sets.
    # | (OR), & (AND), - (SUB), ^ (XOR)
    
    print("[3] Set Algebra (The Bitwise Way)...")
    
    # Scenario: Linux Permission Groups
    admins = {"root", "vatsal", "sysadmin"}
    users  = {"vatsal", "guest", "intern"}
    
    print(f"    Admins: {admins}")
    print(f"    Users:  {users}")
    
    # Union (|) -> All unique people
    print(f"    1. Union (|):             {admins | users}")
    
    # Intersection (&) -> Who has BOTH accesses?
    print(f"    2. Intersection (&):      {admins & users}")
    
    # Difference (-) -> Admins who are NOT regular users
    print(f"    3. Difference (-):        {admins - users}")
    
    # Symmetric Difference (^) -> People in EITHER group, but NOT both
    print(f"    4. Sym. Difference (^):   {admins ^ users}\n")


    # ==================================================================================
    # PART 4: METHODS VS OPERATORS (Safety Checks)
    # ==================================================================================
    print("[4] Essential Methods (Safety First)...")
    s = {"gcc", "clang", "make"}
    
    # add() - O(1)
    s.add("gdb")
    
    # remove() vs discard()
    # remove() raises KeyError if missing (Dangerous for production)
    # discard() does nothing if missing (Safe)
    
    try:
        s.remove("msvc")
    except KeyError:
        print("    remove('msvc') failed (KeyError)")
        
    s.discard("msvc") # No error
    print("    discard('msvc') passed safely")
    
    # pop() - Removes a RANDOM element (Sets are unordered!)
    # Do not rely on pop() to remove the "first" item.
    item = s.pop()
    print(f"    pop() removed random item: '{item}'\n")


    # ==================================================================================
    # PART 5: PERFORMANCE BENCHMARK (List vs Set)
    # ==================================================================================
    print("[5] Performance: Membership Lookup (O(n) vs O(1))...")
    
    large_n = 1000000
    # Creating a large dataset
    large_list = list(range(large_n))
    large_set = set(range(large_n))
    
    target = 999999 # Worst case for list (at the end)
    
    # Timing List Lookup
    list_time = timeit.timeit(lambda: target in large_list, number=100)
    
    # Timing Set Lookup
    set_time = timeit.timeit(lambda: target in large_set, number=100)
    
    print(f"    List Lookup Time: {list_time:.6f} sec")
    print(f"    Set Lookup Time:  {set_time:.6f} sec")
    print(f"    -> Speedup Factor: {list_time / set_time:.1f}x faster!")

if __name__ == "__main__":
    unit_3_sets_masterclass()

items = ["apple", "mango", "banana", "apple"]
uniqueItem = set()

for item in items:
    if item in uniqueItem:
        print(item)
        break
    uniqueItem.add(item)

import netstack

print("\n--- Start of Script ---")

# Usage 1: Accessing via the sub-package shortcut we created
eth = netstack.layers.EthernetFrame("AA:BB:CC", "11:22:33")

# Usage 2: Accessing the IP packet
ip = netstack.layers.IPPacket("192.168.1.1", b"DEADBEEF")

# Usage 3: Accessing the utility hoisted to the top level
print(f"Direct Utility Access: {netstack.to_hex(b'CAFEBABE')}")

class EthernetFrame:
    def __init__(self, src: str, dst: str):
        self.src = src
        self.dst = dst
        print(f"[L2] Ethernet Frame created: {src} -> {dst}")

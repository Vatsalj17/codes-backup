# Notice the relative import!
# We are going up one level (..) to find utils
from .. import utils 

class IPPacket:
    def __init__(self, ip_src: str, payload: bytes):
        self.ip = ip_src
        self.payload = payload
        # Using the utility we imported from the parent package
        hex_dump = utils.to_hex(payload)
        print(f"[L3] IP Packet created. Payload hex: {hex_dump}")

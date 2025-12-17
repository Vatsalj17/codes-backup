import binascii

def to_hex(data: bytes) -> str:
    """Helper to dump bytes as hex string."""
    return binascii.hexlify(data).decode('utf-8')

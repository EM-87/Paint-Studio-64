# FILE: fast_memcpy.S
# Purpose: Optimized memory copy on MIPS R4300 (Nintendo 64 CPU)
# Copies data in 8-byte chunks, using 'pref' instructions for cache prefetch.
# Also handles alignment by copying byte-by-byte until data is aligned.

.text
.align 4
.globl fast_memcpy
.ent fast_memcpy

fast_memcpy:
    # a0 -> dst (destination)
    # a1 -> src (source)
    # a2 -> n   (size in bytes to copy)

    beq a2, zero, done       # if n == 0, nothing to do
    andi t0, a0, 7           # check alignment of dst
    andi t1, a1, 7           # check alignment of src
    or t2, t0, t1
    bnez t2, align_copy      # if not aligned, jump to align_copy

aligned_copy:
    dsubu t2, a2, 8
    bltz t2, tail_copy       # if n < 8, skip directly to tail copy
    nop

copy_loop:
    pref 0, 32(a1)           # prefetch 32 bytes from src into cache
    ld t3, 0(a1)             # load 8 bytes from src
    sd t3, 0(a0)             # store 8 bytes to dst
    daddiu a1, a1, 8         # advance src pointer
    daddiu a0, a0, 8         # advance dst pointer
    daddiu a2, a2, -8        # reduce remaining size
    bgez a2, copy_loop
    nop

tail_copy:
    beq a2, zero, done       # if no leftover bytes, done
    nop

byte_loop:
    lb t3, 0(a1)             # load one byte
    sb t3, 0(a0)             # store one byte
    daddiu a1, a1, 1
    daddiu a0, a0, 1
    daddiu a2, a2, -1
    bgtz a2, byte_loop
    nop

done:
    jr ra
    nop

align_copy:
    # Copy byte-by-byte until both src & dst become aligned to 8
    andi t2, a0, 7
    subu t2, 8, t2
    bgeu a2, t2, aligned_fix
    move t2, a2

align_loop:
    lb t3, 0(a1)
    sb t3, 0(a0)
    daddiu a1, a1, 1
    daddiu a0, a0, 1
    daddiu a2, a2, -1
    daddiu t2, t2, -1
    bgtz t2, align_loop
    nop

aligned_fix:
    b aligned_copy
    nop

.end fast_memcpy

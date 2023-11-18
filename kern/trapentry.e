# 0 "trapentry.S"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "trapentry.S"


# 1 "../inc/mmu.h" 1
# 4 "trapentry.S" 2
# 1 "../inc/memlayout.h" 1
# 5 "trapentry.S" 2
# 1 "../inc/trap.h" 1
# 6 "trapentry.S" 2



###################################################################
# exceptions/interrupts
###################################################################
# 44 "trapentry.S"
.text




.globl vector0; .type vector0, @function; .align 2; vector0: pushl $0; pushl $(0); jmp _alltraps
.globl vector1; .type vector1, @function; .align 2; vector1: pushl $0; pushl $(1); jmp _alltraps
.globl vector2; .type vector2, @function; .align 2; vector2: pushl $0; pushl $(2); jmp _alltraps
.globl vector3; .type vector3, @function; .align 2; vector3: pushl $0; pushl $(3); jmp _alltraps
.globl vector4; .type vector4, @function; .align 2; vector4: pushl $0; pushl $(4); jmp _alltraps
.globl vector5; .type vector5, @function; .align 2; vector5: pushl $0; pushl $(5); jmp _alltraps
.globl vector6; .type vector6, @function; .align 2; vector6: pushl $0; pushl $(6); jmp _alltraps
.globl vector7; .type vector7, @function; .align 2; vector7: pushl $0; pushl $(7); jmp _alltraps
.globl vector8; .type vector8, @function; .align 2; vector8: pushl $(8); jmp _alltraps
.globl vector9; .type vector9, @function; .align 2; vector9: pushl $0; pushl $(9); jmp _alltraps
.globl vector10; .type vector10, @function; .align 2; vector10: pushl $(10); jmp _alltraps
.globl vector11; .type vector11, @function; .align 2; vector11: pushl $(11); jmp _alltraps
.globl vector12; .type vector12, @function; .align 2; vector12: pushl $(12); jmp _alltraps
.globl vector13; .type vector13, @function; .align 2; vector13: pushl $(13); jmp _alltraps
.globl vector14; .type vector14, @function; .align 2; vector14: pushl $(14); jmp _alltraps
.globl vector15; .type vector15, @function; .align 2; vector15: pushl $0; pushl $(15); jmp _alltraps
.globl vector16; .type vector16, @function; .align 2; vector16: pushl $0; pushl $(16); jmp _alltraps
.globl vector17; .type vector17, @function; .align 2; vector17: pushl $0; pushl $(17); jmp _alltraps
.globl vector18; .type vector18, @function; .align 2; vector18: pushl $0; pushl $(18); jmp _alltraps
.globl vector19; .type vector19, @function; .align 2; vector19: pushl $0; pushl $(19); jmp _alltraps
.globl vector20; .type vector20, @function; .align 2; vector20: pushl $0; pushl $(20); jmp _alltraps
.globl vector21; .type vector21, @function; .align 2; vector21: pushl $0; pushl $(21); jmp _alltraps
.globl vector22; .type vector22, @function; .align 2; vector22: pushl $0; pushl $(22); jmp _alltraps
.globl vector23; .type vector23, @function; .align 2; vector23: pushl $0; pushl $(23); jmp _alltraps
.globl vector24; .type vector24, @function; .align 2; vector24: pushl $0; pushl $(24); jmp _alltraps
.globl vector25; .type vector25, @function; .align 2; vector25: pushl $0; pushl $(25); jmp _alltraps
.globl vector26; .type vector26, @function; .align 2; vector26: pushl $0; pushl $(26); jmp _alltraps
.globl vector27; .type vector27, @function; .align 2; vector27: pushl $0; pushl $(27); jmp _alltraps
.globl vector28; .type vector28, @function; .align 2; vector28: pushl $0; pushl $(28); jmp _alltraps
.globl vector29; .type vector29, @function; .align 2; vector29: pushl $0; pushl $(29); jmp _alltraps
.globl vector30; .type vector30, @function; .align 2; vector30: pushl $0; pushl $(30); jmp _alltraps
.globl vector31; .type vector31, @function; .align 2; vector31: pushl $0; pushl $(31); jmp _alltraps

.global vectors
vectors:
 .long vector0
 .long vector1
 .long vector2
 .long vector3
 .long vector4
 .long vector5
 .long vector6
 .long vector7
 .long vector8
 .long vector9
 .long vector10
 .long vector11
 .long vector12
 .long vector13
 .long vector14
 .long vector15
 .long vector16
 .long vector17
 .long vector18
 .long vector19
 .long vector20
 .long vector21
 .long vector22
 .long vector23
 .long vector24
 .long vector25
 .long vector26
 .long vector27
 .long vector28
 .long vector29
 .long vector30
 .long vector31






.global _alltraps
_alltraps:

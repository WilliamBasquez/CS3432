divide_unsigned:
    addi    sp,sp,-32
    sw      ra,28(sp)
    sw      s0,24(sp)
    addi    s0,sp,32
    
    # a0 = *quot, a1 = *rem, a2 = a, a3 = b
    # a4 = i, a5 = q, a6 = r, a7 = temp
    
    bne a3, x0, divide_unsigned_after_first_if
    mv a0, x0
    mv a1, a2
    j divide_unsigned_done

divide_unsigned_after_first_if:
    mv a5, x0
    mv a6, x0
    li a4, 31               # i = (32-1)

divide_unsigned_loop_start:
    slt a7, a4, x0          # a7 = (i < 0) {
    # if a7 == 0, (i < 0) is false, therefore i >= 0 is true
    # if a7 == 1, (i < 0) is true, therefore i >= 0 is false
    bne a7, x0, divide_unsigned_done
    slli a6, a6, 1          # r <<= 1
    srl a7, a2, a4          # (a >> i)
    andi a7, a7, 1          # ((a >> i) & 1)
    or a6, a6, a7           # r = r | ((a >> i) & 1)
    blt a6, a3, divide_unsigned_loop_end
    li a7, 1
    sll a7, a7, a4          # 1 << i
    or a5, a5, a7           # q = q | (1 << i)
    sub a6, a6, a3          # r = r - b

divide_unsigned_loop_end:
    addi a4, a4, -1         # i--
    j divide_unsigned_loop_start

divide_unsigned_done:
    sw a0, 0(a0)            # change quot address
	sw a1, 0(a1)            # change res address
    lw ra, 28(sp)
    lw s0, 24(sp)
    addi sp, sp, 32
    jr ra
    .size divide_unsigned, .-divide_unsigned

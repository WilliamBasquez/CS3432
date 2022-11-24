    # a0 = *quot
    # a1 = *rem
    # a2 = a
    # a3 = b
    # a4 = abs_a
    # a5 = abs_b
    # a6 = abs_quot
    # a7 = abs_rem

    # t0 = sa
    # t1 = sb
    # t2 = sr
divide_signed: # 45 lines
    addi    sp, sp, -32
	sw      ra, 28(sp)
	sw      s0, 24(sp)
	addi    s0, sp, 32
    bge     a2, x0, divide_signed_first_else
    neg     a4, a2
    li      t0, 1
    j       divide_signed_second_if
divide_signed_first_else:
    mv      a4, a2
    mv      t0, x0
divide_signed_second_if:
    bge     a3, x0, divide_signed_second_else
    neg     a5, a3
    li      t1, 1
    j       divide_signed_after_second_else
divide_signed_second_else:
    mv      a5, a3
    mv      t1, x0
divide_signed_after_second_else:
    xor     t2, t1, t0
    sw      a6, 20(sp)
    sw      a7, 16(sp)
    sw      a4, 12(sp)
    sw      a5, 8(sp)
    call    divide_unsigned
    lw      a5, 8(sp)
    lw      a4, 12(sp)
    lw      a7, 16(sp)
    lw      a6, 20(sp)
    beq     t2, x0, divide_signed_third_else
    neg     a6, a6
    sw      a6, 0(a0)
    neg     a7, a7
    sw      a7, 0(a1)
    j       divide_signed_done
divide_signed_third_else:
    sw      a6, 0(a0)
    sw      a7, 0(a1)
divide_signed_done:
    lw      ra, 28(sp)
    lw      s0, 24(sp)
    addi    sp, sp, 32
    jr      ra
    .size   divide_signed, .-divide_signed

# OPTIMIZED CODE (RE-USING REGs FOR a AND b
    # a0 = *quot
    # a1 = *rem
    # a2 = a/abs_a
    # a3 = b/abs_b
    # a4 = abs_quot
    # a5 = abs_rem

    # t0 = sa/sr
    # t1 = sb
divide_signed: # 43 lines
    addi    sp, sp, -32
	sw      ra, 28(sp)
	sw      s0, 24(sp)
	addi    s0, sp, 32
    bge     a2, x0, divide_signed_first_else
    neg     a2, a2
    li      t0, 1
    j       divide_signed_second_if
divide_signed_first_else:
    mv      t0, x0
divide_signed_second_if:
    bge     a3, x0, divide_signed_second_else
    neg     a3, a3
    li      t1, 1
    j       divide_signed_after_second_else
divide_signed_second_else:
    mv      t1, x0
divide_signed_after_second_else:
    xor     t0, t0, t1
    sw      a4, 20(sp)
    sw      a5, 16(sp)
    sw      a2, 12(sp)
    sw      a3, 8(sp)
    call    divide_unsigned
    lw      a3, 8(sp)
    lw      a2, 12(sp)
    lw      a5, 16(sp)
    lw      a4, 20(sp)
    beq     t2, x0, divide_signed_third_else
    neg     a0, a4
    sw      a4, 0(a0)
    neg     a5, a5
    sw      a5, 0(a1)
    j       divide_signed_done
divide_signed_third_else:
    sw      a4, 0(a0)
    sw      a5, 0(a1)
divide_signed_done:
    lw      ra, 28(sp)
    lw      s0, 24(sp)
    addi    sp, sp, 32
    jr      ra
    .size   divide_signed, .-divide_signed
# a0 = a, 
# a1 = b, 
# a2 = abs_a, 
# a3 = abs_b, 
# a4 = sa, 
# a5 = sb, 
# a6 = sr, 
multiply_signed:                                  # Multiply register a0 with a1, put result in a0
  addi sp, sp, -32
  sw   ra, 28(sp)
  sw   s0, 24(sp)
  addi s0, sp, 32
  bge  a0, x0, multiply_signed_if_one_else      # [l: 5]
  neg  a2, a0                                   # [l: 6]
  li   a4, 1                                    # [l: 7]
  j    multiply_signed_if_one_done             
multiply_signed_if_one_else:
  mv   a2, a0                                   # [l: 9]
  mv   a4, x0                                   # [l: 10]
multiply_signed_if_one_done:
  bge  a1, x0, multiply_signed_if_two_else      # [l: 13]
  neg  a3, a1                                   # [l: 14]
  li   a5, 1                                    # [l: 15]
  j    multiply_signed_if_two_done
multiply_signed_if_two_else:
  mv  a3, a1                                    # [l: 17]
  mv  a5, x0                                    # [l: 18]
multiply_signed_if_two_done:
# mv    a0, a2                                  # move abs_a into a
# mv    a1, a3                                  # move abs_b into b
  xor	a6, a4, a5                              # [l: 21]
  sw    a2, 20(sp)                              # move abs_a into the stack
  sw    a3, 16(sp)                              # move abs_b into the stack
  call  multiply_unsigned                       # [l: 23a]
  # lw  a2, 20(sp)                              # load from stack abs_a
  # lw  a3, 16(sp)                              # load from stack abs_b
  beq	a6, x0, multiply_signed_if_three_done   # [l: 24]
  neg	a0, a0                                  # [l: 25]
multiply_signed_if_three_done:                  # we skip last 'else'; res is in a0 already
  lw    ra, 28(sp)
  lw    s0, 24(sp)
  addi  sp, sp, 32
  jr    ra
  .size multiply_signed, .-multiply_signed

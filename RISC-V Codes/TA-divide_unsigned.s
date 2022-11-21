# a0 = *quot
# a1 = *rem
# a2 = a
# a3 = b
# t0 = i
# t1 = q
# t2 = r

divide_unsigned:
  addi 	sp, sp, -32
  sw   	ra, 28(sp)
  sw   	s0, 24(sp)
  addi 	s0, sp, 32
  bne 	a3, x0, divide_unsigned_after_first_if		# jump if b < 0
  mv  	a0, x0						# *quot = 0
  mv  	a1, a2						# *rem = a
  j   	divide_unsigned_done
divide_unsigned_after_first_if:
  mv  	t1, x0						# t1(q) = 0
  mv  	t2, x0						# t2(r) = 0
  li  	t0, 31                             		# t0(i) = (32-1)
divide_unsigned_loop_start:
  blt	t0, x0, divide_unsigned_after_loop		# jump if t0 < 0
  slli 	t2, t2, 1		                        # r = r << 1
  srl  	t3, a2, t0                        		# t3 = a2 >> i
  andi 	t3, t3, 1                         		# t3 = AND (t3, 1)
  or   	t2, t2, t3                        		# r = OR (r, t3)
  blt  	t2, a3, divide_unsigned_loop_start		# jump if r < b
  li   	t3, 1						# t3 = 1
  sll  	t3, t3, t0                        		# t3 = 1 << i
  or   	t1, t1, t3                        		# q = OR (q, t3)
  sub  	t2, t2, a3                        		# r = r - b
  addi	t0, t0, -1					# i = i - 1
  j	divide_unsigned_loop_start
divide_unsigned_after_loop:
  sw   	a0, 0(t1)                         		# quot[0] = q[0]
  sw   	a1, 0(t2)                         		# rem[0] = r[0]
  lw   	ra, 28(sp)
  lw   	s0, 24(sp)
  addi 	sp, sp, 32
  jr   	ra
  .size divide_unsigned, .-divide_unsigned

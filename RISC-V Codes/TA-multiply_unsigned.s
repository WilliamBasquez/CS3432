multiply_unsigned: 
	# a0 = 'a', a1 = 'b'
	addi  sp, sp, -32                             # Move stack pointer up (to lower addresses)
	sw    ra, 28(sp)                              # Store return_addr on stack
	sw    s0, 24(sp)                              # Store frame pointer on stack
	addi  s0, sp, 32                              # Set frame pointer to stack pointer of caller
	mv    a2, x0                                  # Set a2 to 0; a2 will be res
	# lw a4, a0	# ta will be in a4; UPDATE: There's no need to load things, we can use a and b as they are
	# lw a5, a1	# tb will be in a4 [SAME AS ABOVE LINE]
	mv    a3, x0	                                # set a3 (i) to 0
multiply_unsigned_loop_start:
	slti  r4, a3, 32                              # compare i to 32, store temp val in a4... SLTI rd,rs1,imm: (rd <- (rs1 < imm) ? 1 : 0)
	beq   a4, x0, multiply_unsigned_loop_end	    # if r4 = 0, continue; if r4 = 1, stop
	andi  a5, a0, 1								                # the new ANDed value of ta will be in a5
	beq   a5, x0, multiply_unsigned_outside_if    # compare (ta & 1 ) to zero
	add   a2, a2, a1								              # res = res + tb
multiply_unsigned_outside_if:
	srli  a0, a0, 1								                # shift right ta by 1 bit
	slli  a1, a1, 1								                # shift left tb by 1 bit
	addi  a3, a3, 1								                # increase i by 1
	j     multiply_unsigned_loop_start				    # Jump to the start of the loop
multiply_unsigned_loop_end:
	mv    a0, a2									                # move res into return value
	lw    ra, 28(sp)								              # Store return address on stack
	lw    s0, 24(sp)								              # Restore frame pointer
	addi  sp, sp, 32								              # Move stack pointer down (to higher addresses)
	jr	  ra										                  # Return from function
	.size multiply_unsigned, .-multiply_unsigned	# the size of increment is computed by the address of where i am, (minus) where i was.

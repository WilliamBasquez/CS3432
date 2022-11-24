fib_main:
	addi sp, sp, -32
	sw ra, 28(sp)
	sw s0, 24(sp)
	addi s0, sp, 32
	bne a0, x0, fib_return
	li a0, 1
	j fib_end
	li a1, 1
	bne a0, a1, fib_return
	li, a0 1
	j fib_end
fib_return:
	addi a2, a0, -1     						# n-1
	addi a3, a0, -2 							# n-2
	sw 20(sp), a2 								# load n-1 into the stack
	call fib_main
	mv a2, a0									# get return val from fib(n-1) into a2
	sw 20(sp), a3 								# load n-2 into the stack
	call fib_main
	mv a3, a0 									# get return val from fib(n-2) into a3
	add a0, a2, a3 								# ret_val = fib(n-1) + fib(n-2)
fib_end
	lw      ra,28(sp)
    lw      s0,24(sp)
    addi    sp,sp,32
    jr      ra
    .size   fib_main, .-fib_main
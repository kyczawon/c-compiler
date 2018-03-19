	.text
	.align	2
	.global	f
	.set	nomips16
	.set	nomicromips
	.type	f, @function
	.ent	f
	.type	f, @function
f:
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-4
	sw	$a0,0($fp)
	li	$s0,10
	addi	$v0,$s0,0
	j	$31
	nop
	addiu	$sp,$sp,4
	.set	macro
	.set	reorder
	.end	f
	.align	2
	.global	main
	.set	nomips16
	.set	nomicromips
	.type	main, @function
	.ent	main
	.type	main, @function
main:
	.set	noreorder
	.set	nomacro

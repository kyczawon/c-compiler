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
	addiu	$sp,$sp,-0
	lw	$s0,0($fp)
	li	$s1,1
	addu	$s2,$s0,$s1
	sw	$s2,0($fp)
	lw	$s0,0($fp)
	addi	$v0,$s0,0
	j	$31
	addiu	$sp,$sp,0
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

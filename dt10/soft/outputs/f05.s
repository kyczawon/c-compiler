	.text
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
	addiu	$sp,$sp,-4
	li	$s0,7
	sw	$s0,0($fp)
	lw	$s0,0($fp)
	addi	$v0,$s0,0
	j	$31
	addiu	$sp,$sp,4
	.set	macro
	.set	reorder
	.end	main

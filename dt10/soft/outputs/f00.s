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
	addiu	$sp,$sp,-0
	li	$s0,10
	addi	$v0,$s0,0
	j	$31
	addiu	$sp,$sp,0
	.set	macro
	.set	reorder
	.end	main

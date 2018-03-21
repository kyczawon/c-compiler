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
	li	$s0,5
	li	$s1,6
	addu	$s2,$s0,$s1
	addi	$v0,$s2,0
	j	$31
	addiu	$sp,$sp,0
	.set	macro
	.set	reorder
	.end	main

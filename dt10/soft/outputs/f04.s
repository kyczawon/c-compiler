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
	li	$s0,1
	li	$s1,2
	mul	$s2,$s0,$s1
	li	$s3,3
	li	$s4,4
	mul	$s5,$s3,$s4
	addu	$s6,$s4,$s5
	li	$s7,5
	li	$s8,6
	mul	$s9,$s7,$s8
	addu	$s10,$s8,$s9
	li	$s11,7
	li	$s12,8
	mul	$s13,$s11,$s12
	addu	$s14,$s12,$s13
	addi	$v0,$s14,0
	j	$31
	nop
	addiu	$sp,$sp,0
	.set	macro
	.set	reorder
	.end	main

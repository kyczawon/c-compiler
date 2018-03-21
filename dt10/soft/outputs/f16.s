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
	li	$s0,0
	beq	$s0,$0,$IL0
	nop
	li	$s0,5
	beq	$s0,$0,$IEL0
	nop
	li	$s0,10
	addi	$v0,$s0,0
	j	$31
	addiu	$sp,$sp,0
	beq	$0,$0,$IEL1
	nop
$IEL0:
	li	$s0,13
	addi	$v0,$s0,0
	j	$31
	addiu	$sp,$sp,0
$IEL1:
$IL0:
	li	$s1,11
	addi	$v0,$s1,0
	j	$31
	addiu	$sp,$sp,0
	.set	macro
	.set	reorder
	.end	main

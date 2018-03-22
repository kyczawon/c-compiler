	.text
	.align	2
	.global	function
	.set	nomips16
	.set	nomicromips
	.type	function, @function
	.ent	function
	.type	function, @function
function:
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$a0,0($fp)
	sw	$a1,4($fp)
	lw	$s0,0($fp)
	lw	$s1,4($fp)
	sltu	$s1,$s0,$s1
	andi	$s1,$s1,0x00ff
	beq	$s1,$0,$IL2
	nop
	lw	$s0,0($fp)
	li	$s1,1
	sub	$s2,$s0,$s1
	sw	$s2,0($fp)
	lw	$s0,0($fp)
	lw	$s1,4($fp)
	slt	$s1,$s1,$s0
	andi	$s1,$s1,0x00ff
	beq	$s1,$0,$IL1
	nop
	lw	$s0,4($fp)
	li	$s1,3
	addu	$s2,$s0,$s1
	sw	$s2,4($fp)
	lw	$s0,0($fp)
	lw	$s1,4($fp)
	xor	$s1,$s0,$s1
	sltu	$s1,$s1,1
	andi	$s1,$s1,0x00ff
	beq	$s1,$0,$IL0
	nop
	lw	$s0,0($fp)
	lw	$s1,4($fp)
	mul	$s2,$s0,$s1
	addi	$v0,$s2,0
	j	$31
	addiu	$sp,$sp,0
$IL0:
$IL1:
	lw	$s2,4($fp)
	addi	$v0,$s2,0
	j	$31
	addiu	$sp,$sp,0
$IL2:
	li	$s2,13
	addi	$v0,$s2,0
	j	$31
	addiu	$sp,$sp,8
	.set	macro
	.set	reorder
	.end	function
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

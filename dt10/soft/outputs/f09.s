	.text	
	.align	2
	.global	function
	.set	nomips16
	.set	nomicromips
	.ent	function
	.type	function, @function
function:
	.frame	$fp,76,$31
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-76
	sw	$31, 4($sp)
	sw	$30, 8($sp)
	sw	$29, 12($sp)
	sw	$28, 16($sp)
	sw	$s7, 20($sp)
	sw	$s6, 24($sp)
	sw	$s5, 28($sp)
	sw	$s4, 32($sp)
	sw	$s3, 36($sp)
	sw	$s2, 40($sp)
	sw	$s1, 44($sp)
	sw	$s0, 48($sp)
	move	$fp,$sp
	sw	$a0,52($fp)
	sw	$a1,56($fp)
	lw	$s0,52($fp)
	sw	$s0,60($fp)
	lw	$s0,56($fp)
	sw	$s0,64($fp)
	lw	$s1,60($fp)
	lw	$s0,64($fp)
	sltu	$s0,$s1,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,68($fp)
	lw	$s0,68($fp)
	beq	$s0,$0,$IL2
	nop
	lw	$s0,52($fp)
	sw	$s0,52($fp)
	li	$s0,1
	sw	$s0,56($fp)
	lw	$s1,52($fp)
	lw	$s0,56($fp)
	sub	$s2,$s1,$s0
	sw	$s2,60($fp)
	lw	$s0,60($fp)
	sw	$s0,52($fp)
	lw	$s0,52($fp)
	sw	$s0,52($fp)
	lw	$s0,56($fp)
	sw	$s0,56($fp)
	lw	$s1,52($fp)
	lw	$s0,56($fp)
	slt	$s0,$s0,$s1
	andi	$s0,$s0,0x00ff
	sw	$s0,60($fp)
	lw	$s0,60($fp)
	beq	$s0,$0,$IL1
	nop
	lw	$s0,56($fp)
	sw	$s0,52($fp)
	li	$s0,3
	sw	$s0,56($fp)
	lw	$s1,52($fp)
	lw	$s0,56($fp)
	addu	$s2,$s1,$s0
	sw	$s2,60($fp)
	lw	$s0,60($fp)
	sw	$s0,56($fp)
	lw	$s0,52($fp)
	sw	$s0,52($fp)
	lw	$s0,56($fp)
	sw	$s0,56($fp)
	lw	$s1,52($fp)
	lw	$s0,56($fp)
	xor	$s0,$s1,$s0
	sltu	$s0,$s0,1
	andi	$s0,$s0,0x00ff
	sw	$s0,60($fp)
	lw	$s0,60($fp)
	beq	$s0,$0,$IL0
	nop
	lw	$s0,52($fp)
	sw	$s0,52($fp)
	lw	$s0,56($fp)
	sw	$s0,56($fp)
	lw	$s1,52($fp)
	lw	$s0,56($fp)
	mul	$s2,$s1,$s0
	sw	$s2,60($fp)
	lw	$v0,60($fp)
	move	$sp,$fp
	lw	$31, 4($sp)
	lw	$30, 8($sp)
	lw	$29, 12($sp)
	lw	$28, 16($sp)
	lw	$s7, 20($sp)
	lw	$s6, 24($sp)
	lw	$s5, 28($sp)
	lw	$s4, 32($sp)
	lw	$s3, 36($sp)
	lw	$s2, 40($sp)
	lw	$s1, 44($sp)
	lw	$s0, 48($sp)
	j	$31
	addiu	$sp,$sp,64
$IL0:
$IL1:
	lw	$s0,56($fp)
	sw	$s0,64($fp)
	lw	$v0,64($fp)
	move	$sp,$fp
	lw	$31, 4($sp)
	lw	$30, 8($sp)
	lw	$29, 12($sp)
	lw	$28, 16($sp)
	lw	$s7, 20($sp)
	lw	$s6, 24($sp)
	lw	$s5, 28($sp)
	lw	$s4, 32($sp)
	lw	$s3, 36($sp)
	lw	$s2, 40($sp)
	lw	$s1, 44($sp)
	lw	$s0, 48($sp)
	j	$31
	addiu	$sp,$sp,68
$IL2:
	li	$s0,13
	sw	$s0,72($fp)
	lw	$v0,72($fp)
	move	$sp,$fp
	lw	$31, 4($sp)
	lw	$30, 8($sp)
	lw	$29, 12($sp)
	lw	$28, 16($sp)
	lw	$s7, 20($sp)
	lw	$s6, 24($sp)
	lw	$s5, 28($sp)
	lw	$s4, 32($sp)
	lw	$s3, 36($sp)
	lw	$s2, 40($sp)
	lw	$s1, 44($sp)
	lw	$s0, 48($sp)
	j	$31
	addiu	$sp,$sp,76
	.set	macro
	.set	reorder
	.end	function

	.align	2
	.global	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,112,$31
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-112
	sw	$31, 4($sp)
	sw	$30, 8($sp)
	sw	$29, 12($sp)
	sw	$28, 16($sp)
	sw	$s7, 20($sp)
	sw	$s6, 24($sp)
	sw	$s5, 28($sp)
	sw	$s4, 32($sp)
	sw	$s3, 36($sp)
	sw	$s2, 40($sp)
	sw	$s1, 44($sp)
	sw	$s0, 48($sp)
	move	$fp,$sp
	li	$s0,0
	sw	$s0,52($fp)
	lw	$a0,52($fp)
	li	$s0,0
	sw	$s0,56($fp)
	lw	$a1,56($fp)
	jal	function
	nop
	sw	$v0,60($fp)
	li	$s0,1
	sw	$s0,64($fp)
	lw	$a0,64($fp)
	li	$s0,2
	sw	$s0,68($fp)
	lw	$a1,68($fp)
	jal	function
	nop
	sw	$v0,72($fp)
	lw	$s1,60($fp)
	lw	$s0,72($fp)
	addu	$s2,$s1,$s0
	sw	$s2,76($fp)
	li	$s0,4
	sw	$s0,80($fp)
	lw	$a0,80($fp)
	li	$s0,3
	sw	$s0,84($fp)
	lw	$a1,84($fp)
	jal	function
	nop
	sw	$v0,88($fp)
	lw	$s1,76($fp)
	lw	$s0,88($fp)
	addu	$s2,$s1,$s0
	sw	$s2,92($fp)
	li	$s0,6
	sw	$s0,96($fp)
	lw	$a0,96($fp)
	li	$s0,7
	sw	$s0,100($fp)
	lw	$a1,100($fp)
	jal	function
	nop
	sw	$v0,104($fp)
	lw	$s1,92($fp)
	lw	$s0,104($fp)
	addu	$s2,$s1,$s0
	sw	$s2,108($fp)
	lw	$v0,108($fp)
	move	$sp,$fp
	lw	$31, 4($sp)
	lw	$30, 8($sp)
	lw	$29, 12($sp)
	lw	$28, 16($sp)
	lw	$s7, 20($sp)
	lw	$s6, 24($sp)
	lw	$s5, 28($sp)
	lw	$s4, 32($sp)
	lw	$s3, 36($sp)
	lw	$s2, 40($sp)
	lw	$s1, 44($sp)
	lw	$s0, 48($sp)
	j	$31
	addiu	$sp,$sp,112
	.set	macro
	.set	reorder
	.end	main


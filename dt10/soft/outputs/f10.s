	.text	
	.align	2
	.global	factorial
	.set	nomips16
	.set	nomicromips
	.ent	factorial
	.type	factorial, @function
factorial:
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
	lw	$s0,52($fp)
	sw	$s0,56($fp)
	li	$s0,1
	sw	$s0,60($fp)
	li	$s0,1
	sw	$s0,64($fp)
	lw	$s1,60($fp)
	lw	$s0,64($fp)
	addu	$s2,$s1,$s0
	sw	$s2,68($fp)
	lw	$s1,56($fp)
	lw	$s0,68($fp)
	sltu	$s0,$s1,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,72($fp)
	lw	$s0,72($fp)
	beq	$s0,$0,$IEL0
	nop
	li	$s0,1
	sw	$s0,52($fp)
	lw	$v0,52($fp)
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
	addiu	$sp,$sp,56
	beq	$0,$0,$IEL1
	nop
$IEL0:
	lw	$s0,52($fp)
	sw	$s0,52($fp)
	li	$s0,1
	sw	$s0,56($fp)
	lw	$s1,52($fp)
	lw	$s0,56($fp)
	sub	$s2,$s1,$s0
	sw	$s2,60($fp)
	lw	$a0,60($fp)
	jal	factorial
	nop
	sw	$v0,64($fp)
	lw	$s0,52($fp)
	sw	$s0,68($fp)
	li	$s0,2
	sw	$s0,72($fp)
	lw	$s1,68($fp)
	lw	$s0,72($fp)
	sub	$s2,$s1,$s0
	sw	$s2,76($fp)
	lw	$a0,76($fp)
	jal	factorial
	nop
	sw	$v0,80($fp)
	lw	$s1,64($fp)
	lw	$s0,80($fp)
	addu	$s2,$s1,$s0
	sw	$s2,84($fp)
	lw	$v0,84($fp)
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
	addiu	$sp,$sp,88
$IEL1:
	.set	macro
	.set	reorder
	.end	factorial

	.align	2
	.global	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,96,$31
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-96
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
	li	$s0,4
	sw	$s0,52($fp)
	lw	$a0,52($fp)
	jal	factorial
	nop
	sw	$v0,56($fp)
	li	$s0,2
	sw	$s0,60($fp)
	lw	$a0,60($fp)
	jal	factorial
	nop
	sw	$v0,64($fp)
	lw	$s1,56($fp)
	lw	$s0,64($fp)
	sub	$s2,$s1,$s0
	sw	$s2,68($fp)
	li	$s0,1
	sw	$s0,72($fp)
	lw	$a0,72($fp)
	jal	factorial
	nop
	sw	$v0,76($fp)
	lw	$s1,68($fp)
	lw	$s0,76($fp)
	sub	$s2,$s1,$s0
	sw	$s2,80($fp)
	li	$s0,0
	sw	$s0,84($fp)
	lw	$a0,84($fp)
	jal	factorial
	nop
	sw	$v0,88($fp)
	lw	$s1,80($fp)
	lw	$s0,88($fp)
	sub	$s2,$s1,$s0
	sw	$s2,92($fp)
	lw	$v0,92($fp)
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
	addiu	$sp,$sp,96
	.set	macro
	.set	reorder
	.end	main


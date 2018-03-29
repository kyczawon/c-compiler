	.text	
	.align	2
	.global	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,100,$31
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-100
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
	li	$s0,2
	sw	$s0,64($fp)
	sw	$s0,60($fp)
	li	$s0,0
	sw	$s0,68($fp)
	lw	$s5,68($fp)
	sw	$s5,52($fp)
	li	$s0,0
	sw	$s0,68($fp)
	lw	$s5,68($fp)
	sw	$s5,56($fp)
	b	$WL4
	nop
$WL3:
	li	$s0,0
	sw	$s0,68($fp)
	lw	$s5,68($fp)
	sw	$s5,56($fp)
	b	$WL1
	nop
$WL0:
	lw	$s0,60($fp)
	sw	$s0,68($fp)
	lw	$s0,56($fp)
	sw	$s0,72($fp)
	lw	$s1,68($fp)
	lw	$s0,72($fp)
	addu	$s2,$s1,$s0
	sw	$s2,76($fp)
	lw	$s5,76($fp)
	sw	$s5,60($fp)
	lw	$s0,56($fp)
	sw	$s0,68($fp)
	li	$s0,1
	sw	$s0,72($fp)
	lw	$s1,68($fp)
	lw	$s0,72($fp)
	addu	$s2,$s1,$s0
	sw	$s2,76($fp)
	lw	$s5,76($fp)
	sw	$s5,56($fp)
$WL1:
	lw	$s0,56($fp)
	sw	$s0,68($fp)
	lw	$s0,52($fp)
	sw	$s0,72($fp)
	lw	$s1,68($fp)
	lw	$s0,72($fp)
	xor	$s0,$s1,$s0
	sltu	$s0,$0,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,76($fp)
	lw	$s0,76($fp)
	bne	$s0,$0,$WL0
	nop
$WL2:
	lw	$s0,52($fp)
	sw	$s0,80($fp)
	li	$s0,2
	sw	$s0,84($fp)
	lw	$s1,80($fp)
	lw	$s0,84($fp)
	addu	$s2,$s1,$s0
	sw	$s2,88($fp)
	lw	$s5,88($fp)
	sw	$s5,52($fp)
$WL4:
	lw	$s0,52($fp)
	sw	$s0,68($fp)
	li	$s0,6
	sw	$s0,72($fp)
	lw	$s1,68($fp)
	lw	$s0,72($fp)
	sltu	$s0,$s1,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,76($fp)
	lw	$s0,76($fp)
	bne	$s0,$0,$WL3
	nop
$WL5:
	lw	$s0,60($fp)
	sw	$s0,80($fp)
	lw	$s0,52($fp)
	sw	$s0,84($fp)
	lw	$s1,80($fp)
	lw	$s0,84($fp)
	sub	$s2,$s1,$s0
	sw	$s2,88($fp)
	lw	$s0,56($fp)
	sw	$s0,92($fp)
	lw	$s1,88($fp)
	lw	$s0,92($fp)
	sub	$s2,$s1,$s0
	sw	$s2,96($fp)
	lw	$v0,96($fp)
	b	mainEND
	nop
mainEND:
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
	addiu	$sp,$sp,100
	.set	macro
	.set	reorder
	.end	main


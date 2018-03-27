	.text	
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
	li	$s0,2
	sw	$s0,64($fp)
	lw	$s0,64($fp)
	sw	$s0,60($fp)
	li	$s0,0
	sw	$s0,68($fp)
	lw	$s0,68($fp)
	sw	$s0,52($fp)
	li	$s0,0
	sw	$s0,64($fp)
	lw	$s0,64($fp)
	sw	$s0,56($fp)
	b	$WL4
	nop
$WL3:
	li	$s0,0
	sw	$s0,52($fp)
	lw	$s0,52($fp)
	sw	$s0,56($fp)
	b	$WL1
	nop
$WL0:
	lw	$s0,60($fp)
	sw	$s0,52($fp)
	lw	$s0,56($fp)
	sw	$s0,56($fp)
	lw	$s1,52($fp)
	lw	$s0,56($fp)
	addu	$s2,$s1,$s0
	sw	$s2,60($fp)
	lw	$s0,60($fp)
	sw	$s0,60($fp)
	lw	$s0,56($fp)
	sw	$s0,52($fp)
	li	$s0,1
	sw	$s0,56($fp)
	lw	$s1,52($fp)
	lw	$s0,56($fp)
	addu	$s2,$s1,$s0
	sw	$s2,60($fp)
	lw	$s0,60($fp)
	sw	$s0,56($fp)
$WL1:
	lw	$s0,56($fp)
	sw	$s0,52($fp)
	lw	$s0,52($fp)
	sw	$s0,56($fp)
	lw	$s1,52($fp)
	lw	$s0,56($fp)
	xor	$s0,$s1,$s0
	sltu	$s0,$0,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,60($fp)
	lw	$s0,60($fp)
	bne	$s0,$0,$WL0
	nop
$WL2:
	lw	$s0,52($fp)
	sw	$s0,64($fp)
	li	$s0,2
	sw	$s0,68($fp)
	lw	$s1,64($fp)
	lw	$s0,68($fp)
	addu	$s2,$s1,$s0
	sw	$s2,72($fp)
	lw	$s0,72($fp)
	sw	$s0,52($fp)
$WL4:
	lw	$s0,52($fp)
	sw	$s0,64($fp)
	li	$s0,6
	sw	$s0,68($fp)
	lw	$s1,64($fp)
	lw	$s0,68($fp)
	sltu	$s0,$s1,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,72($fp)
	lw	$s0,72($fp)
	bne	$s0,$0,$WL3
	nop
$WL5:
	lw	$s0,60($fp)
	sw	$s0,76($fp)
	lw	$s0,52($fp)
	sw	$s0,80($fp)
	lw	$s1,76($fp)
	lw	$s0,80($fp)
	sub	$s2,$s1,$s0
	sw	$s2,84($fp)
	lw	$s0,56($fp)
	sw	$s0,88($fp)
	lw	$s1,84($fp)
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


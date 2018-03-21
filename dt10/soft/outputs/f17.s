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
	addiu	$sp,$sp,-12
	li	$s0,2
	sw	$s0,8($fp)
	li	$s1,0
	sw	$s1,0($fp)
	li	$s0,0
	sw	$s0,4($fp)
	b	$WL2
	nop
$WL3:
	li	$s0,0
	sw	$s0,4($fp)
	b	$WL0
	nop
$WL1:
	lw	$s0,8($fp)
	lw	$s1,4($fp)
	addu	$s2,$s0,$s1
	sw	$s2,8($fp)
	lw	$s0,4($fp)
	li	$s1,1
	addu	$s2,$s0,$s1
	sw	$s2,4($fp)
$WL0:
	lw	$s0,4($fp)
	lw	$s1,0($fp)
	xor	$s1,$s0,$s1
	sltu	$s1,$0,$s1
	andi	$s1,$s1,0x00ff
	bne	$s1,$0,$WL1
	nop
	lw	$s2,0($fp)
	li	$s3,2
	addu	$s4,$s2,$s3
	sw	$s4,0($fp)
$WL2:
	lw	$s0,0($fp)
	li	$s1,6
	sltu	$s1,$s0,$s1
	andi	$s1,$s1,0x00ff
	bne	$s1,$0,$WL3
	nop
	lw	$s2,8($fp)
	lw	$s3,0($fp)
	sub	$s4,$s2,$s3
	lw	$s5,4($fp)
	sub	$s6,$s4,$s5
	addi	$v0,$s6,0
	j	$31
	addiu	$sp,$sp,12
	.set	macro
	.set	reorder
	.end	main

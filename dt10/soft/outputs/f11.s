	.text
	.align	2
	.global	geo
	.set	nomips16
	.set	nomicromips
	.type	geo, @function
	.ent	geo
	.type	geo, @function
geo:
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-12
	sw	$a0,0($fp)
	li	$s0,0
	sw	$s0,4($fp)
	lw	$s1,0($fp)
	sw	$s1,8($fp)
	b	$WL0
	nop
$WL1:
	lw	$s0,4($fp)
	lw	$s1,8($fp)
	addu	$s2,$s0,$s1
	sw	$s2,4($fp)
$WL0:
	lw	$s2,8($fp)
	lw	$s3,0($fp)
	sltu	$s3,$s2,$s3
	andi	$s3,$s3,0x00ff
	bne	$s3,$0,$WL1
	nop
	lw	$s4,4($fp)
	addi	$v0,$s4,0
	j	$31
	addiu	$sp,$sp,12
	.set	macro
	.set	reorder
	.end	geo
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

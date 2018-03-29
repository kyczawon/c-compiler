	.file	1 "dt10/soft/inputs/f11.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module fp=xx
	.module nooddspreg
	.abicalls

	.text	
	.align	2
	.global	geo
	.set	nomips16
	.set	nomicromips
	.ent	geo
	.type	geo, @function
geo:
	.frame	$fp,100,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-100
	sw	$31, 0($sp)
	sw	$30, 4($sp)
	sw	$29, 8($sp)
	sw	$28, 12($sp)
	sw	$s7,16($sp)
	sw	$s6,20($sp)
	sw	$s5,24($sp)
	sw	$s4,28($sp)
	sw	$s3,32($sp)
	sw	$s2,36($sp)
	sw	$s1,40($sp)
	sw	$s0,44($sp)
	move	$fp,$sp
	sw	$a0,52($fp)
	li	$s0,0
	sw	$s0,60($fp)
	sw	$s0,56($fp)
	lw	$s0,52($fp)
	sw	$s0,68($fp)
	sw	$s0,60($fp)
	b	$WL1
	nop
$WL0:
	lw	$s0,56($fp)
	sw	$s0,72($fp)
	lw	$s0,60($fp)
	sw	$s0,76($fp)
	lw	$s1,72($fp)
	lw	$s0,76($fp)
	addu	$s2,$s1,$s0
	sw	$s2,80($fp)
	lw	$s3,80($fp)
	sw	$s3,56($fp)
$WL1:
	lw	$s0,60($fp)
	sw	$s0,84($fp)
	lw	$s0,52($fp)
	sw	$s0,88($fp)
	lw	$s1,84($fp)
	lw	$s0,88($fp)
	sltu	$s0,$s1,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,92($fp)
	lw	$s0,92($fp)
	bne	$s0,$0,$WL0
	nop
$WL2:
	lw	$s0,56($fp)
	sw	$s0,96($fp)
	lw	$v0,96($fp)
	b	geoEND
	nop
geoEND:
	lw	$31, 0($sp)
	lw	$30, 4($sp)
	lw	$29, 8($sp)
	lw	$28, 12($sp)
	lw	$s7,16($sp)
	lw	$s6,20($sp)
	lw	$s5,24($sp)
	lw	$s4,28($sp)
	lw	$s3,32($sp)
	lw	$s2,36($sp)
	lw	$s1,40($sp)
	lw	$s0,44($sp)
	j	$31
	addiu	$sp,$sp,100

	.set	macro
	.set	reorder
	.end	geo
	.size	geo, .-geo
	.align	2
	.global	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,84,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-84
	sw	$31, 0($sp)
	sw	$30, 4($sp)
	sw	$29, 8($sp)
	sw	$28, 12($sp)
	sw	$s7,16($sp)
	sw	$s6,20($sp)
	sw	$s5,24($sp)
	sw	$s4,28($sp)
	sw	$s3,32($sp)
	sw	$s2,36($sp)
	sw	$s1,40($sp)
	sw	$s0,44($sp)
	move	$fp,$sp
	li	$s0,4
	sw	$s0,52($fp)
	lw	$a0,52($fp)

	.option pic0
	jal	geo
	nop

	.option pic2
	sw	$v0,56($fp)
	li	$s0,3
	sw	$s0,60($fp)
	lw	$a0,60($fp)

	.option pic0
	jal	geo
	nop

	.option pic2
	sw	$v0,64($fp)
	lw	$s1,56($fp)
	lw	$s0,64($fp)
	addu	$s2,$s1,$s0
	sw	$s2,68($fp)
	li	$s0,2
	sw	$s0,72($fp)
	lw	$a0,72($fp)

	.option pic0
	jal	geo
	nop

	.option pic2
	sw	$v0,76($fp)
	lw	$s1,68($fp)
	lw	$s0,76($fp)
	addu	$s2,$s1,$s0
	sw	$s2,80($fp)
	lw	$v0,80($fp)
	b	mainEND
	nop
mainEND:
	lw	$31, 0($sp)
	lw	$30, 4($sp)
	lw	$29, 8($sp)
	lw	$28, 12($sp)
	lw	$s7,16($sp)
	lw	$s6,20($sp)
	lw	$s5,24($sp)
	lw	$s4,28($sp)
	lw	$s3,32($sp)
	lw	$s2,36($sp)
	lw	$s1,40($sp)
	lw	$s0,44($sp)
	j	$31
	addiu	$sp,$sp,84

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

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
	.frame	$fp,148,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-148
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
	sw	$s0,108($fp)
	lw	$s0,108($fp)
	sw	$s0,56($fp)
	lw	$s0,52($fp)
	sw	$s0,116($fp)
	lw	$s0,116($fp)
	sw	$s0,60($fp)
	b	$WL1
	nop
$WL0:
	lw	$s0,56($fp)
	sw	$s0,120($fp)
	lw	$s0,60($fp)
	sw	$s0,124($fp)
	lw	$s1,120($fp)
	lw	$s0,124($fp)
	addu	$s2,$s1,$s0
	sw	$s2,128($fp)
	lw	$s3,128($fp)
	sw	$s3,56($fp)
$WL1:
	lw	$s0,60($fp)
	sw	$s0,132($fp)
	lw	$s0,52($fp)
	sw	$s0,136($fp)
	lw	$s1,132($fp)
	lw	$s0,136($fp)
	sltu	$s0,$s1,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,140($fp)
	lw	$s0,140($fp)
	bne	$s0,$0,$WL0
	nop
$WL2:
	lw	$s0,56($fp)
	sw	$s0,144($fp)
	lw	$v0,144($fp)
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
	addiu	$sp,$sp,148

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
	.frame	$fp,132,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-132
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
	sw	$s0,100($fp)
	lw	$a0,100($fp)

	.option pic0
	jal	geo
	nop

	.option pic2
	sw	$v0,104($fp)
	li	$s0,3
	sw	$s0,108($fp)
	lw	$a0,108($fp)

	.option pic0
	jal	geo
	nop

	.option pic2
	sw	$v0,112($fp)
	lw	$s1,104($fp)
	lw	$s0,112($fp)
	addu	$s2,$s1,$s0
	sw	$s2,116($fp)
	li	$s0,2
	sw	$s0,120($fp)
	lw	$a0,120($fp)

	.option pic0
	jal	geo
	nop

	.option pic2
	sw	$v0,124($fp)
	lw	$s1,116($fp)
	lw	$s0,124($fp)
	addu	$s2,$s1,$s0
	sw	$s2,128($fp)
	lw	$v0,128($fp)
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
	addiu	$sp,$sp,132

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

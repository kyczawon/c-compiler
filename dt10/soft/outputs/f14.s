	.file	1 "dt10/soft/inputs/f14.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module fp=xx
	.module nooddspreg
	.abicalls

	.text	
	.align	2
	.global	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,120,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-120
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
	li	$s0,1
	sw	$s0,100($fp)
	lw	$s0,100($fp)
	beq	$s0,$0,$IL0
	nop
	li	$s0,2
	sw	$s0,104($fp)
	lw	$s0,104($fp)
	beq	$s0,$0,$IEL0
	nop
	li	$s0,10
	sw	$s0,108($fp)
	lw	$v0,108($fp)
	b	mainEND
	nop
	beq	$0,$0,$IEL1
	nop
$IEL0:
	li	$s0,13
	sw	$s0,112($fp)
	lw	$v0,112($fp)
	b	mainEND
	nop
$IEL1:
$IL0:
	li	$s0,11
	sw	$s0,116($fp)
	lw	$v0,116($fp)
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
	addiu	$sp,$sp,120

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

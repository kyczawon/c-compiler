	.file	1 "dt10/soft/inputs/f06.c"
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
	.frame	$fp,124,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-124
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
	li	$s0,5
	sw	$s0,104($fp)
	lw	$s3,104($fp)
	sw	$s3,52($fp)
	lw	$s0,52($fp)
	sw	$s0,108($fp)
	lw	$s0,52($fp)
	sw	$s0,112($fp)
	lw	$s1,108($fp)
	lw	$s0,112($fp)
	mul	$s2,$s1,$s0
	sw	$s2,116($fp)
	lw	$s3,116($fp)
	sw	$s3,52($fp)
	lw	$s0,52($fp)
	sw	$s0,120($fp)
	lw	$v0,120($fp)
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
	addiu	$sp,$sp,124

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

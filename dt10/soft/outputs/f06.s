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
	.frame	$fp,76,$31
	.mask	0x40000000,-4
	.fmask	0x00000000,0
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
	li	$s0,5
	sw	$s0,56($fp)
	lw	$s5,56($fp)
	sw	$s5,52($fp)
	lw	$s0,52($fp)
	sw	$s0,60($fp)
	lw	$s0,52($fp)
	sw	$s0,64($fp)
	lw	$s1,60($fp)
	lw	$s0,64($fp)
	mul	$s2,$s1,$s0
	sw	$s2,68($fp)
	lw	$s5,68($fp)
	sw	$s5,52($fp)
	lw	$s0,52($fp)
	sw	$s0,72($fp)
	lw	$v0,72($fp)
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
	addiu	$sp,$sp,76

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

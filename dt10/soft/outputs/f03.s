	.text	
	.align	2
	.global	f
	.set	nomips16
	.set	nomicromips
	.ent	f
	.type	f, @function
f:
	.frame	$fp,60,$31
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-60
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
	li	$s0,10
	sw	$s0,56($fp)
	lw	$v0,56($fp)
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
	addiu	$sp,$sp,60
	.set	macro
	.set	reorder
	.end	f

	.align	2
	.global	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,68,$31
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-68
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
	li	$s0,11
	sw	$s0,52($fp)
	lw	$a0,52($fp)
	.option pic0
	jal	f
	nop
	.option pic2
	sw	$v0,56($fp)
	li	$s0,7
	sw	$s0,60($fp)
	lw	$s1,56($fp)
	lw	$s0,60($fp)
	addu	$s2,$s1,$s0
	sw	$s2,64($fp)
	lw	$v0,64($fp)
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
	addiu	$sp,$sp,68
	.set	macro
	.set	reorder
	.end	main


	.file	1 "dt10/soft/inputs/f10.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module fp=xx
	.module nooddspreg
	.abicalls

	.text	
	.align	2
	.global	factorial
	.set	nomips16
	.set	nomicromips
	.ent	factorial
	.type	factorial, @function
factorial:
	.frame	$fp,164,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-164
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
	lw	$s0,52($fp)
	sw	$s0,104($fp)
	li	$s0,1
	sw	$s0,108($fp)
	li	$s0,1
	sw	$s0,112($fp)
	lw	$s1,108($fp)
	lw	$s0,112($fp)
	addu	$s2,$s1,$s0
	sw	$s2,116($fp)
	lw	$s1,104($fp)
	lw	$s0,116($fp)
	sltu	$s0,$s1,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,120($fp)
	lw	$s0,120($fp)
	beq	$s0,$0,$IEL0
	nop
	li	$s0,1
	sw	$s0,124($fp)
	lw	$v0,124($fp)
	b	factorialEND
	nop
	beq	$0,$0,$IEL1
	nop
$IEL0:
	lw	$s0,52($fp)
	sw	$s0,128($fp)
	li	$s0,1
	sw	$s0,132($fp)
	lw	$s1,128($fp)
	lw	$s0,132($fp)
	sub	$s2,$s1,$s0
	sw	$s2,136($fp)
	lw	$a0,136($fp)

	.option pic0
	jal	factorial
	nop

	.option pic2
	sw	$v0,140($fp)
	lw	$s0,52($fp)
	sw	$s0,144($fp)
	li	$s0,2
	sw	$s0,148($fp)
	lw	$s1,144($fp)
	lw	$s0,148($fp)
	sub	$s2,$s1,$s0
	sw	$s2,152($fp)
	lw	$a0,152($fp)

	.option pic0
	jal	factorial
	nop

	.option pic2
	sw	$v0,156($fp)
	lw	$s1,140($fp)
	lw	$s0,156($fp)
	addu	$s2,$s1,$s0
	sw	$s2,160($fp)
	lw	$v0,160($fp)
	b	factorialEND
	nop
$IEL1:
factorialEND:
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
	addiu	$sp,$sp,164

	.set	macro
	.set	reorder
	.end	factorial
	.size	factorial, .-factorial
	.align	2
	.global	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,144,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-144
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
	jal	factorial
	nop

	.option pic2
	sw	$v0,104($fp)
	li	$s0,2
	sw	$s0,108($fp)
	lw	$a0,108($fp)

	.option pic0
	jal	factorial
	nop

	.option pic2
	sw	$v0,112($fp)
	lw	$s1,104($fp)
	lw	$s0,112($fp)
	sub	$s2,$s1,$s0
	sw	$s2,116($fp)
	li	$s0,1
	sw	$s0,120($fp)
	lw	$a0,120($fp)

	.option pic0
	jal	factorial
	nop

	.option pic2
	sw	$v0,124($fp)
	lw	$s1,116($fp)
	lw	$s0,124($fp)
	sub	$s2,$s1,$s0
	sw	$s2,128($fp)
	li	$s0,0
	sw	$s0,132($fp)
	lw	$a0,132($fp)

	.option pic0
	jal	factorial
	nop

	.option pic2
	sw	$v0,136($fp)
	lw	$s1,128($fp)
	lw	$s0,136($fp)
	sub	$s2,$s1,$s0
	sw	$s2,140($fp)
	lw	$v0,140($fp)
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
	addiu	$sp,$sp,144

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

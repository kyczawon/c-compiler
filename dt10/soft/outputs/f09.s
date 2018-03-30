	.file	1 "dt10/soft/inputs/f09.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module fp=xx
	.module nooddspreg
	.abicalls

	.text	
	.align	2
	.global	function
	.set	nomips16
	.set	nomicromips
	.ent	function
	.type	function, @function
function:
	.frame	$fp,188,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-188
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
	sw	$a1,56($fp)
	lw	$s0,52($fp)
	sw	$s0,108($fp)
	lw	$s0,56($fp)
	sw	$s0,112($fp)
	lw	$s1,108($fp)
	lw	$s0,112($fp)
	sltu	$s0,$s1,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,116($fp)
	lw	$s0,116($fp)
	beq	$s0,$0,$IL2
	nop
	lw	$s0,52($fp)
	sw	$s0,120($fp)
	li	$s0,1
	sw	$s0,124($fp)
	lw	$s1,120($fp)
	lw	$s0,124($fp)
	sub	$s2,$s1,$s0
	sw	$s2,128($fp)
	lw	$s3,128($fp)
	sw	$s3,52($fp)
	lw	$s0,52($fp)
	sw	$s0,132($fp)
	lw	$s0,56($fp)
	sw	$s0,136($fp)
	lw	$s1,132($fp)
	lw	$s0,136($fp)
	slt	$s0,$s0,$s1
	andi	$s0,$s0,0x00ff
	sw	$s0,140($fp)
	lw	$s0,140($fp)
	beq	$s0,$0,$IL1
	nop
	lw	$s0,56($fp)
	sw	$s0,144($fp)
	li	$s0,3
	sw	$s0,148($fp)
	lw	$s1,144($fp)
	lw	$s0,148($fp)
	addu	$s2,$s1,$s0
	sw	$s2,152($fp)
	lw	$s3,152($fp)
	sw	$s3,56($fp)
	lw	$s0,52($fp)
	sw	$s0,156($fp)
	lw	$s0,56($fp)
	sw	$s0,160($fp)
	lw	$s1,156($fp)
	lw	$s0,160($fp)
	xor	$s0,$s1,$s0
	sltu	$s0,$s0,1
	andi	$s0,$s0,0x00ff
	sw	$s0,164($fp)
	lw	$s0,164($fp)
	beq	$s0,$0,$IL0
	nop
	lw	$s0,52($fp)
	sw	$s0,168($fp)
	lw	$s0,56($fp)
	sw	$s0,172($fp)
	lw	$s1,168($fp)
	lw	$s0,172($fp)
	mul	$s2,$s1,$s0
	sw	$s2,176($fp)
	lw	$v0,176($fp)
	b	functionEND
	nop
$IL0:
$IL1:
	lw	$s0,56($fp)
	sw	$s0,180($fp)
	lw	$v0,180($fp)
	b	functionEND
	nop
$IL2:
	li	$s0,13
	sw	$s0,184($fp)
	lw	$v0,184($fp)
	b	functionEND
	nop
functionEND:
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
	addiu	$sp,$sp,188

	.set	macro
	.set	reorder
	.end	function
	.size	function, .-function
	.align	2
	.global	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,160,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-160
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
	li	$s0,0
	sw	$s0,100($fp)
	lw	$a0,100($fp)
	li	$s0,0
	sw	$s0,104($fp)
	lw	$a1,104($fp)

	.option pic0
	jal	function
	nop

	.option pic2
	sw	$v0,108($fp)
	li	$s0,1
	sw	$s0,112($fp)
	lw	$a0,112($fp)
	li	$s0,2
	sw	$s0,116($fp)
	lw	$a1,116($fp)

	.option pic0
	jal	function
	nop

	.option pic2
	sw	$v0,120($fp)
	lw	$s1,108($fp)
	lw	$s0,120($fp)
	addu	$s2,$s1,$s0
	sw	$s2,124($fp)
	li	$s0,4
	sw	$s0,128($fp)
	lw	$a0,128($fp)
	li	$s0,3
	sw	$s0,132($fp)
	lw	$a1,132($fp)

	.option pic0
	jal	function
	nop

	.option pic2
	sw	$v0,136($fp)
	lw	$s1,124($fp)
	lw	$s0,136($fp)
	addu	$s2,$s1,$s0
	sw	$s2,140($fp)
	li	$s0,6
	sw	$s0,144($fp)
	lw	$a0,144($fp)
	li	$s0,7
	sw	$s0,148($fp)
	lw	$a1,148($fp)

	.option pic0
	jal	function
	nop

	.option pic2
	sw	$v0,152($fp)
	lw	$s1,140($fp)
	lw	$s0,152($fp)
	addu	$s2,$s1,$s0
	sw	$s2,156($fp)
	lw	$v0,156($fp)
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
	addiu	$sp,$sp,160

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

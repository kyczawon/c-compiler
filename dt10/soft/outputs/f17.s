	.file	1 "dt10/soft/inputs/f17.c"
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
	.frame	$fp,208,$31
	.set	noreorder
	.set	nomacro
	addiu	$t1,$sp,0
	addiu	$sp,$sp,-208
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
	li	$s0,2
	sw	$s0,112($fp)
	lw	$s0,112($fp)
	sw	$s0,60($fp)
	li	$s0,0
	sw	$s0,116($fp)
	lw	$s3,116($fp)
	sw	$s3,52($fp)
	li	$s0,0
	sw	$s0,120($fp)
	lw	$s3,120($fp)
	sw	$s3,56($fp)
	b	$WL4
	nop
$WL3:
	li	$s0,0
	sw	$s0,124($fp)
	lw	$s3,124($fp)
	sw	$s3,56($fp)
	b	$WL1
	nop
$WL0:
	lw	$s0,60($fp)
	sw	$s0,128($fp)
	lw	$s0,56($fp)
	sw	$s0,132($fp)
	lw	$s1,128($fp)
	lw	$s0,132($fp)
	addu	$s2,$s1,$s0
	sw	$s2,136($fp)
	lw	$s3,136($fp)
	sw	$s3,60($fp)
	lw	$s0,56($fp)
	sw	$s0,140($fp)
	li	$s0,1
	sw	$s0,144($fp)
	lw	$s1,140($fp)
	lw	$s0,144($fp)
	addu	$s2,$s1,$s0
	sw	$s2,148($fp)
	lw	$s3,148($fp)
	sw	$s3,56($fp)
$WL1:
	lw	$s0,56($fp)
	sw	$s0,152($fp)
	lw	$s0,52($fp)
	sw	$s0,156($fp)
	lw	$s1,152($fp)
	lw	$s0,156($fp)
	xor	$s0,$s1,$s0
	sltu	$s0,$0,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,160($fp)
	lw	$s0,160($fp)
	bne	$s0,$0,$WL0
	nop
$WL2:
	lw	$s0,52($fp)
	sw	$s0,164($fp)
	li	$s0,2
	sw	$s0,168($fp)
	lw	$s1,164($fp)
	lw	$s0,168($fp)
	addu	$s2,$s1,$s0
	sw	$s2,172($fp)
	lw	$s3,172($fp)
	sw	$s3,52($fp)
$WL4:
	lw	$s0,52($fp)
	sw	$s0,176($fp)
	li	$s0,6
	sw	$s0,180($fp)
	lw	$s1,176($fp)
	lw	$s0,180($fp)
	sltu	$s0,$s1,$s0
	andi	$s0,$s0,0x00ff
	sw	$s0,184($fp)
	lw	$s0,184($fp)
	bne	$s0,$0,$WL3
	nop
$WL5:
	lw	$s0,60($fp)
	sw	$s0,188($fp)
	lw	$s0,52($fp)
	sw	$s0,192($fp)
	lw	$s1,188($fp)
	lw	$s0,192($fp)
	sub	$s2,$s1,$s0
	sw	$s2,196($fp)
	lw	$s0,56($fp)
	sw	$s0,200($fp)
	lw	$s1,196($fp)
	lw	$s0,200($fp)
	sub	$s2,$s1,$s0
	sw	$s2,204($fp)
	lw	$v0,204($fp)
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
	addiu	$sp,$sp,208

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main

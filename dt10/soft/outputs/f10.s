	.text
	.align	2
	.global	factorial
	.set	nomips16
	.set	nomicromips
	.ent	factorial
	.type	factorial, @function
factorial:
	.set	noreorder
	.set	nomacro

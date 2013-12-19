	.weak __vector_dispatch_99
	.section	.vector_99,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_99
__vector_dispatch_99:
	j	_DefaultInterrupt
	.end	__vector_dispatch_99
	.size	__vector_dispatch_99, .-__vector_dispatch_99


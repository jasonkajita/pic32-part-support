	.weak __vector_dispatch_12
	.section	.vector_12,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_12
__vector_dispatch_12:
	j	_DefaultInterrupt
	.end	__vector_dispatch_12
	.size	__vector_dispatch_12, .-__vector_dispatch_12


	.weak __vector_dispatch_16
	.section	.vector_16,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_16
__vector_dispatch_16:
	j	_DefaultInterrupt
	.end	__vector_dispatch_16
	.size	__vector_dispatch_16, .-__vector_dispatch_16


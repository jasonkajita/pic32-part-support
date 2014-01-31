	.weak __vector_dispatch_0
	.section	.vector_0,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_0
__vector_dispatch_0:
	j	_DefaultInterrupt
	.end	__vector_dispatch_0
	.size	__vector_dispatch_0, .-__vector_dispatch_0


	.weak __vector_dispatch_5
	.section	.vector_5,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_5
__vector_dispatch_5:
	j	_DefaultInterrupt
	.end	__vector_dispatch_5
	.size	__vector_dispatch_5, .-__vector_dispatch_5


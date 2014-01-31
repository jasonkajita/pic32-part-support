	.weak __vector_dispatch_8
	.section	.vector_8,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_8
__vector_dispatch_8:
	j	_DefaultInterrupt
	.end	__vector_dispatch_8
	.size	__vector_dispatch_8, .-__vector_dispatch_8


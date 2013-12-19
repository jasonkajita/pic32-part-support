	.weak __vector_dispatch_4
	.section	.vector_4,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_4
__vector_dispatch_4:
	j	_DefaultInterrupt
	.end	__vector_dispatch_4
	.size	__vector_dispatch_4, .-__vector_dispatch_4


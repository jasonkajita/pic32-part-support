	.weak __vector_dispatch_2
	.section	.vector_2,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_2
__vector_dispatch_2:
	j	_DefaultInterrupt
	.end	__vector_dispatch_2
	.size	__vector_dispatch_2, .-__vector_dispatch_2


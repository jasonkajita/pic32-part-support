	.weak __vector_dispatch_3
	.section	.vector_3,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_3
__vector_dispatch_3:
	j	_DefaultInterrupt
	.end	__vector_dispatch_3
	.size	__vector_dispatch_3, .-__vector_dispatch_3


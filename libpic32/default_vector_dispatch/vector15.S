	.weak __vector_dispatch_15
	.section	.vector_15,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_15
__vector_dispatch_15:
	j	_DefaultInterrupt
	.end	__vector_dispatch_15
	.size	__vector_dispatch_15, .-__vector_dispatch_15


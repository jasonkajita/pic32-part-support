	.weak __vector_dispatch_64
	.section	.vector_64,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_64
__vector_dispatch_64:
	j	_DefaultInterrupt
	.end	__vector_dispatch_64
	.size	__vector_dispatch_64, .-__vector_dispatch_64


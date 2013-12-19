	.weak __vector_dispatch_32
	.section	.vector_32,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_32
__vector_dispatch_32:
	j	_DefaultInterrupt
	.end	__vector_dispatch_32
	.size	__vector_dispatch_32, .-__vector_dispatch_32


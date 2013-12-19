	.weak __vector_dispatch_20
	.section	.vector_20,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_20
__vector_dispatch_20:
	j	_DefaultInterrupt
	.end	__vector_dispatch_20
	.size	__vector_dispatch_20, .-__vector_dispatch_20


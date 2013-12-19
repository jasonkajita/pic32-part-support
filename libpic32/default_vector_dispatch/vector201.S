	.weak __vector_dispatch_201
	.section	.vector_201,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_201
__vector_dispatch_201:
	j	_DefaultInterrupt
	.end	__vector_dispatch_201
	.size	__vector_dispatch_201, .-__vector_dispatch_201


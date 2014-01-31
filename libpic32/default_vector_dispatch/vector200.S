	.weak __vector_dispatch_200
	.section	.vector_200,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_200
__vector_dispatch_200:
	j	_DefaultInterrupt
	.end	__vector_dispatch_200
	.size	__vector_dispatch_200, .-__vector_dispatch_200


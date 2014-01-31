	.weak __vector_dispatch_100
	.section	.vector_100,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_100
__vector_dispatch_100:
	j	_DefaultInterrupt
	.end	__vector_dispatch_100
	.size	__vector_dispatch_100, .-__vector_dispatch_100


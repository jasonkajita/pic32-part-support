	.weak __vector_dispatch_50
	.section	.vector_50,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_50
__vector_dispatch_50:
	j	_DefaultInterrupt
	.end	__vector_dispatch_50
	.size	__vector_dispatch_50, .-__vector_dispatch_50


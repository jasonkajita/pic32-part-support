	.weak __vector_dispatch_90
	.section	.vector_90,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_90
__vector_dispatch_90:
	j	_DefaultInterrupt
	.end	__vector_dispatch_90
	.size	__vector_dispatch_90, .-__vector_dispatch_90


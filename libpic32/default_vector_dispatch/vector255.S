	.weak __vector_dispatch_255
	.section	.vector_255,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_255
__vector_dispatch_255:
	j	_DefaultInterrupt
	.end	__vector_dispatch_255
	.size	__vector_dispatch_255, .-__vector_dispatch_255


	.weak __vector_dispatch_180
	.section	.vector_180,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_180
__vector_dispatch_180:
	j	_DefaultInterrupt
	.end	__vector_dispatch_180
	.size	__vector_dispatch_180, .-__vector_dispatch_180


	.weak __vector_dispatch_123
	.section	.vector_123,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_123
__vector_dispatch_123:
	j	_DefaultInterrupt
	.end	__vector_dispatch_123
	.size	__vector_dispatch_123, .-__vector_dispatch_123


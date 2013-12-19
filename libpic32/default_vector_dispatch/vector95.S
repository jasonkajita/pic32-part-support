	.weak __vector_dispatch_95
	.section	.vector_95,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_95
__vector_dispatch_95:
	j	_DefaultInterrupt
	.end	__vector_dispatch_95
	.size	__vector_dispatch_95, .-__vector_dispatch_95


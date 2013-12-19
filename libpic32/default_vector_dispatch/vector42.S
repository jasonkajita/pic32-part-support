	.weak __vector_dispatch_42
	.section	.vector_42,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_42
__vector_dispatch_42:
	j	_DefaultInterrupt
	.end	__vector_dispatch_42
	.size	__vector_dispatch_42, .-__vector_dispatch_42


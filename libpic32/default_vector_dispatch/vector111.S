	.weak __vector_dispatch_111
	.section	.vector_111,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_111
__vector_dispatch_111:
	j	_DefaultInterrupt
	.end	__vector_dispatch_111
	.size	__vector_dispatch_111, .-__vector_dispatch_111


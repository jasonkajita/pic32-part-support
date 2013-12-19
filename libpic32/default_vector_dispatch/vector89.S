	.weak __vector_dispatch_89
	.section	.vector_89,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_89
__vector_dispatch_89:
	j	_DefaultInterrupt
	.end	__vector_dispatch_89
	.size	__vector_dispatch_89, .-__vector_dispatch_89


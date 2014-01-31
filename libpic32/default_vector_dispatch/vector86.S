	.weak __vector_dispatch_86
	.section	.vector_86,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_86
__vector_dispatch_86:
	j	_DefaultInterrupt
	.end	__vector_dispatch_86
	.size	__vector_dispatch_86, .-__vector_dispatch_86


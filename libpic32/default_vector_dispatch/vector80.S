	.weak __vector_dispatch_80
	.section	.vector_80,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_80
__vector_dispatch_80:
	j	_DefaultInterrupt
	.end	__vector_dispatch_80
	.size	__vector_dispatch_80, .-__vector_dispatch_80


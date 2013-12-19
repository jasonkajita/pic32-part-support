	.weak __vector_dispatch_1
	.section	.vector_1,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_1
__vector_dispatch_1:
	j	_DefaultInterrupt
	.end	__vector_dispatch_1
	.size	__vector_dispatch_1, .-__vector_dispatch_1


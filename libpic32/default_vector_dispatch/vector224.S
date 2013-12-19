	.weak __vector_dispatch_224
	.section	.vector_224,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_224
__vector_dispatch_224:
	j	_DefaultInterrupt
	.end	__vector_dispatch_224
	.size	__vector_dispatch_224, .-__vector_dispatch_224


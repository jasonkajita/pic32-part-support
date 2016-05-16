	.weak __vector_dispatch_224
	.section	.vector_224,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_224
__vector_dispatch_224:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_224
	.size	__vector_dispatch_224, .-__vector_dispatch_224


	.weak __vector_dispatch_255
	.section	.vector_255,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_255
__vector_dispatch_255:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_255
	.size	__vector_dispatch_255, .-__vector_dispatch_255


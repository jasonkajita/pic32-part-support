	.weak __vector_dispatch_194
	.section	.vector_194,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_194
__vector_dispatch_194:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_194
	.size	__vector_dispatch_194, .-__vector_dispatch_194


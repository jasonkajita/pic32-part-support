	.weak __vector_dispatch_242
	.section	.vector_242,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_242
__vector_dispatch_242:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_242
	.size	__vector_dispatch_242, .-__vector_dispatch_242


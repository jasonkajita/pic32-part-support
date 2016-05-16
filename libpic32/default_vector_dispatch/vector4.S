	.weak __vector_dispatch_4
	.section	.vector_4,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_4
__vector_dispatch_4:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_4
	.size	__vector_dispatch_4, .-__vector_dispatch_4


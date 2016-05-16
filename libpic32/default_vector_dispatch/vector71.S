	.weak __vector_dispatch_71
	.section	.vector_71,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_71
__vector_dispatch_71:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_71
	.size	__vector_dispatch_71, .-__vector_dispatch_71


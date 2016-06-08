	.weak __vector_dispatch_85
	.section	.vector_85,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_85
__vector_dispatch_85:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_85
	.size	__vector_dispatch_85, .-__vector_dispatch_85


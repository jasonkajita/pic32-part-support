	.weak __vector_dispatch_54
	.section	.vector_54,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_54
__vector_dispatch_54:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_54
	.size	__vector_dispatch_54, .-__vector_dispatch_54


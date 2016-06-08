	.weak __vector_dispatch_73
	.section	.vector_73,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_73
__vector_dispatch_73:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_73
	.size	__vector_dispatch_73, .-__vector_dispatch_73


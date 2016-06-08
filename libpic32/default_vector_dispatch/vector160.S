	.weak __vector_dispatch_160
	.section	.vector_160,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_160
__vector_dispatch_160:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_160
	.size	__vector_dispatch_160, .-__vector_dispatch_160


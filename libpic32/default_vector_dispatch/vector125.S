	.weak __vector_dispatch_125
	.section	.vector_125,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_125
__vector_dispatch_125:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_125
	.size	__vector_dispatch_125, .-__vector_dispatch_125


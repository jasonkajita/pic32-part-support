	.weak __vector_dispatch_192
	.section	.vector_192,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_192
__vector_dispatch_192:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_192
	.size	__vector_dispatch_192, .-__vector_dispatch_192


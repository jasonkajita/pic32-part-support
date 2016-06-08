	.weak __vector_dispatch_104
	.section	.vector_104,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_104
__vector_dispatch_104:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_104
	.size	__vector_dispatch_104, .-__vector_dispatch_104


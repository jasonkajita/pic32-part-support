	.weak __vector_dispatch_111
	.section	.vector_111,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_111
__vector_dispatch_111:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_111
	.size	__vector_dispatch_111, .-__vector_dispatch_111


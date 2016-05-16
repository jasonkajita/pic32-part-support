	.weak __vector_dispatch_114
	.section	.vector_114,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_114
__vector_dispatch_114:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_114
	.size	__vector_dispatch_114, .-__vector_dispatch_114


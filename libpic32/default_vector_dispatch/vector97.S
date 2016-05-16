	.weak __vector_dispatch_97
	.section	.vector_97,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_97
__vector_dispatch_97:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_97
	.size	__vector_dispatch_97, .-__vector_dispatch_97


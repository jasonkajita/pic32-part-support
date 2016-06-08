	.weak __vector_dispatch_86
	.section	.vector_86,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_86
__vector_dispatch_86:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_86
	.size	__vector_dispatch_86, .-__vector_dispatch_86


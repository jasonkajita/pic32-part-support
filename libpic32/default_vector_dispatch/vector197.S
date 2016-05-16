	.weak __vector_dispatch_197
	.section	.vector_197,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_197
__vector_dispatch_197:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_197
	.size	__vector_dispatch_197, .-__vector_dispatch_197


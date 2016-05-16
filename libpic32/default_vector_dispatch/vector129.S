	.weak __vector_dispatch_129
	.section	.vector_129,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_129
__vector_dispatch_129:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_129
	.size	__vector_dispatch_129, .-__vector_dispatch_129


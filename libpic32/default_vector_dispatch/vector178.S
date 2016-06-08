	.weak __vector_dispatch_178
	.section	.vector_178,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_178
__vector_dispatch_178:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_178
	.size	__vector_dispatch_178, .-__vector_dispatch_178


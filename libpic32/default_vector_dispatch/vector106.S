	.weak __vector_dispatch_106
	.section	.vector_106,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_106
__vector_dispatch_106:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_106
	.size	__vector_dispatch_106, .-__vector_dispatch_106


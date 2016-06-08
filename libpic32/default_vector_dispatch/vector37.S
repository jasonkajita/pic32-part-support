	.weak __vector_dispatch_37
	.section	.vector_37,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_37
__vector_dispatch_37:
#ifdef __PIC__
	lw	$25,%call16(_DefaultInterrupt)($28)
	jr	$25
	nop
#else
	j	_DefaultInterrupt
#endif
	.end	__vector_dispatch_37
	.size	__vector_dispatch_37, .-__vector_dispatch_37


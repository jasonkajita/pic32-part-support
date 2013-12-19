	.weak __vector_dispatch_96
	.section	.vector_96,code
	.align	2
	.set	nomips16
	.ent	__vector_dispatch_96
__vector_dispatch_96:
	j	_DefaultInterrupt
	.end	__vector_dispatch_96
	.size	__vector_dispatch_96, .-__vector_dispatch_96


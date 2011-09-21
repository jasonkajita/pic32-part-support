/*
 *  Provides a definition for __C32_UART
 */

int
#if defined(__mips) && (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7))
__attribute__ ((section (".sdata")))
#endif
 __C32_UART=2;

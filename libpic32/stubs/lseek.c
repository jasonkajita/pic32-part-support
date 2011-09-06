#include <stdio.h>

static char __attribute__((section(".gnu.warning.lseekstub")))
__warning_lseek[] = "Linking stub lseek(). Hint: Provide an app-specific implementation.";

long __attribute__((__weak__))
lseek(int handle, long offset, int origin) {
  return(0);
}


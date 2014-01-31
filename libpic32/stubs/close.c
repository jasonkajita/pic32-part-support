#include <stdio.h>

static char __attribute__((section(".gnu.warning.closestub")))
__warning_close[] = "Linking stub close(). Hint: Provide an app-specific implementation.";

int __attribute__((__weak__)) close(int handle) {
  return(0);
}


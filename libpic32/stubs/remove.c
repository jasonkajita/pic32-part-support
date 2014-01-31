#include <stdio.h>

static char __attribute__((section(".gnu.warning.stubremove")))
 __remove_warning[] = "Linking default stub remove(). Hint: Provide an app-specific implementation.";

int __attribute__((__weak__))
remove(const char *filename) {
  return(0);
}


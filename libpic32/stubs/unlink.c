#include <errno.h>
int
unlink (char * path)
{
  errno = EIO;
  return (-1);
}

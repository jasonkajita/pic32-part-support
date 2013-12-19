#include <errno.h>
int
rmdir (char * path)
{
  errno = EIO;
  return (-1);
}

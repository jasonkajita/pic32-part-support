#include <errno.h>

/*
 * open -- open a file descriptor. We don't have a filesystem, so
 *         we return an error.
 */
int
open (const char *buf,
       int flags,
       int mode)
{
  errno = EIO;
  return (-1);
}

/*
 * Stub version of fstat.
 */

#include <_ansi.h>
#include <_syslist.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#undef errno
extern int errno;
#include "warning.h"

int
_DEFUN (fstat, (fildes, st),
        int          fildes _AND
        struct stat *st)
{
  errno = ENOSYS;
  return -1;
}

stub_warning(fstat)

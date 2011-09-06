
extern void __attribute__((weak)) 
_mon_write (const char * s, unsigned int count);
extern void
_mon_putc (char c);

int __attribute__((__weak__))
write(int handle, void *buffer, unsigned int len) {
  int i;
  
  /* Do not try to output an empty string */
  if (!buffer || (len == 0))
    return 0;
 
  switch (handle)
  {
    case 0:
    case 1:
    case 2:
      if (_mon_write)
      {
	_mon_write(buffer, len);
      }
      else
      {
        for (i = len; i; --i)
        {
          _mon_putc (*(char*)buffer);
          buffer++;
        }
      }
      break;

    default: {
      break;
    }
  }
  return (len);
}

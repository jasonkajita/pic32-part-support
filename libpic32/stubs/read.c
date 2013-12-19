#include <stdio.h>

extern int __XC_UART;

#ifndef _U1MODE_UARTEN_POSITION
#define _U1MODE_UARTEN_POSITION                 0x0000000F
#endif

#ifndef _U1STA_UTXEN_POSITION
#define _U1STA_UTXEN_POSITION                   0x0000000A
#endif

#ifndef _U1STA_TRMT_POSITION
#define _U1STA_TRMT_POSITION                    0x00000008
#endif

#ifndef _U1STA_URXDA_POSITION
#define _U1STA_URXDA_POSITION                   0x00000000
#endif

extern volatile unsigned int U1MODE __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1STA __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1MODESET __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1STASET __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1RXREG __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1TXREG __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1BRG __attribute__((weak,section("sfrs")));

extern volatile unsigned int U2MODE __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2STA __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2MODESET __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2STASET __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2RXREG __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2TXREG __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2BRG __attribute__((weak,section("sfrs")));
extern int __attribute__((__weak__)) _mon_getc (int canblock);

int __attribute__((__weak__))
read(int handle, void *buffer, unsigned int len)
{
  int i;
  volatile unsigned int *umode = &U1MODE;
  volatile unsigned int *umodeset = &U1MODESET;
  volatile unsigned int *ustatus = &U1STA;
  volatile unsigned int *ustatusset = &U1STASET;
  volatile unsigned int *rxreg = &U1RXREG;
  volatile unsigned int *brg = &U1BRG;

  /* Do not try to read to a NULL buffer */
  if ((buffer == NULL) || (len == 0))
    return 0;

  switch (handle)
  {
    case 0:
#if 0
      if (_Files[0]->_Lockno == 0)
#else
      if (1)
#endif
      {
        if (_mon_getc)
        {
          for (i = len; i; --i)
          {
            *(char*)buffer++ = _mon_getc(1);
          }
          len -= i;
        }
        else
        {
          if ((__XC_UART == 2) && (&U2BRG)) {
            umode = &U2MODE;
            ustatus = &U2STA;
            rxreg = &U2RXREG;
            brg = &U2BRG;
          }
          if ((*umode & (1 << _U1MODE_UARTEN_POSITION)) == 0)
          {
            *umodeset = (1 << _U1MODE_UARTEN_POSITION);
          }
          for (i = len; i; --i)
          {
            int nTimeout;

            /*
            ** Timeout is 16 cycles per 10-bit char
            */
            nTimeout = 16*10;
            while (((*ustatus & (1 << _U1STA_URXDA_POSITION)) == 0) && nTimeout) --nTimeout;
            if (*ustatus & (1 << _U1STA_URXDA_POSITION)) break;
            *(char*)buffer++ = *rxreg;
          }
          len -= i;
        }
        break;
      }

    default: {
      break;
    }
  }
  return(len);
}


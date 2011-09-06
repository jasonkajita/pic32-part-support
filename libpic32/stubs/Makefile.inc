_VPATH	+=:$(ROOT)/stubs

LIBOBJ	+= default-general-exception-handler.o \
	default-bootstrap-exception-handler.o default-on-reset.o \
        default-on-bootstrap.o default-nmi-handler.o
LIBOBJ += sbrk.o
#LIBOBJ += _exit.o system.o default-gettimeofday.o isatty.o
#LIBOBJ += _mon_getc.o _mon_putc.o _mon_puts.o _mon_write.o
#LIBOBJ += read.o
#LIBOBJ += write.o
#LIBOBJ += lseek.o
#LIBOBJ += remove.o
#LIBOBJ += close.o
#LIBOBJ += assfail.o
#LIBOBJ += getenv.o
#LIBOBJ += rename.o

# LIBOBJ += stubs.o getenv.o
# LIBOBJ += raise.o signal.o localeconv.o setlocale.o isatty.o

sbrk.o: sbrk.c
	$(CC) $(CFLAGS) -c -DPAGESIZE=64 $< -o $@


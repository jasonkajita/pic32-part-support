_VPATH	+=:$(ROOT)/stubs

LIBOBJ	+= sbrk.o default-general-exception-handler.o \
	default-bootstrap-exception-handler.o default-on-reset.o \
	default-on-bootstrap.o default-nmi-handler.o \
	 _exit.o \
	system.o \
	default-gettimeofday.o isatty.o
LIBOBJ += _mon_getc.o _mon_putc.o _mon_puts.o _mon_write.o
LIBOBJ += read.o
LIBOBJ += write.o
LIBOBJ += lseek.o
LIBOBJ += remove.o
LIBOBJ += close.o
LIBOBJ += getenv.o
LIBOBJ += rename.o
LIBOBJ += open.o
LIBOBJ += unlink.o
LIBOBJ += kill.o
LIBOBJ += getpid.o
LIBOBJ += xc32_uart.o
LIBOBJ += errno.o
LIBOBJ += rmdir.o
LIBOBJ += isinf.o
LIBOBJ += pic32_init_cache.o
LIBOBJ += pic32_init_tlb_ebi_sqi.o
LIBOBJ += default-cache-err-exception-handler.o
LIBOBJ += default-simple-tlb-refill-exception-handler.o
LIBOBJ += pic32_software_reset.o

# LIBOBJ += stubs.o getenv.o 
# LIBOBJ += raise.o signal.o localeconv.o setlocale.o isatty.o

SUPOBJ  += pic32_software_reset.o pic32_software_reset-mm.o

sbrk.o: sbrk.c
	$(CC) $(CFLAGS) -c -DPAGESIZE=128 $< -o $@

pic32_software_reset.o: pic32_software_reset.S
	$(CC) -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

pic32_software_reset-mm.o: pic32_software_reset.S
	$(CC) -g -mmicromips -D__USE_MICROMIPS=1 -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@
 

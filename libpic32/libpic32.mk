include	$(ROOT)/../defines.mk

include $(ROOT)/arch/$(ARCH)/Makefile.inc
include $(ROOT)/stubs/Makefile.inc
include $(ROOT)/startup/Makefile.inc
include $(ROOT)/default_vector_dispatch/Makefile.inc

vpath	%.c		$(_VPATH)
vpath	%.cc		$(_VPATH)
vpath	%.s		$(_VPATH)
vpath	%.sx		$(_VPATH)
vpath	%.S		$(_VPATH)
vpath	%.h		$(_VPATH)
vpath	Makefile	$(_VPATH)

# Force optimisation, but no inlining/unrolling
OPTIM	=-O2 -fno-inline-functions -fno-unroll-loops \
	 -foptimize-sibling-calls -ffunction-sections \
	 -fno-common -fno-builtin-exit -fno-builtin-abort -minterlink-mips16 \
	 -fno-jump-tables

CPPFLAGS += $(GPOPT) -DNDEBUG=1 -I$(ROOT)/include -I$(ROOT)/../include
CFLAGS += $(OPTIM) $(VAR) $(GPOPT) -DNDEBUG=1 -D__LIBBUILD__ -I$(ROOT)/include -I$(ROOT)/../include -g1 -msmart-io=0 -Wcast-align -Wall
ASFLAGS += $(VAR) -DNDEBUG=1 -D__LIBBUILD__

all: libpic32.a startup_modules

libpic32.a: Makefile $(LIBOBJ)
	$(STRIP) $(STRIPFLAGS) $(LIBOBJ)
	$(AR) rcs $@ $(LIBOBJ)

startup_modules:  Makefile $(SUPOBJ)

install: libpic32.a startup_modules
	mkdir -p $(LIBDESTDIR)/$(SUBDIR)
	rm -f $(LIBDESTDIR)/$(SUBDIR)/libpic32.a
	cp -p libpic32.a $(LIBDESTDIR)/$(SUBDIR)/libpic32.a
	@rm -f $(addprefix $(LIBDESTDIR)/$(SUBDIR)/,$(SUPOBJ))
	cp -p $(SUPOBJ) $(LIBDESTDIR)/$(SUBDIR)

clean:
	rm -f libpic32.a *.o core* *~


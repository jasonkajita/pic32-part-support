# 
# Makefile for libpic32.a
#
# This makefile will only work with GNU make
#

ROOT := $(shell pwd)

include $(ROOT)/../defines.mk

MAKEFILE = -f $(ROOT)/libpic32.mk

SRCINSTALLDIRS=startup stubs

all install:
	@$(MAKE) doall T=$@

install-baseline:
	@$(MAKE) doall T=install

install-proc:

install-src:

clean:
	@$(MAKE) doall T=$@
	[ ! -d OBJ ] || rm -r OBJ
	rm -f *[~#]

doall: dodir
	$(foreach ML,$(shell $(CC) --print-multi-lib), \
		set -e; \
		rdir=`echo "$(ML)" | sed -e 's/;.*$$//'`; \
		dir=OBJ/$$rdir; \
		[ -d $$dir ] || mkdir -p $$dir; \
		flags=`echo "$(ML)" | sed -e 's/^[^;]*;//' -e 's/@/ -/g'`; \
		if echo "$$flags" | egrep -v '$(SKIPARCHS)' >/dev/null; then \
			if echo "$$flags" | grep 'mips16' >/dev/null; then \
				makevar="CODESIZEOPT=1"; \
			else \
				makevar=""; \
			fi; \
			echo $(MAKE) -C $$dir $(MAKEFILE) $$makevar VAR="$$flags" SUBDIR=$$rdir $F $T; \
			$(MAKE) -C $$dir $(MAKEFILE) $$makevar VAR="$$flags" SUBDIR=$$rdir $F $T; \
		fi; ) \

doone: dodir
	set -e; \
	rdir=`$(CC) --print-multi-dir $(VAR)`; \
	dir=OBJ/$$rdir; \
	[ -d $$dir ] || mkdir -p $$dir; \
	$(MAKE) -C $$dir $(MAKEFILE) VAR="$(VAR)" SUBDIR=$$rdir $F $T

dodir: Makefile $(ROOT)/libpic32.mk
	mkdir -p OBJ

.PHONY: all install clean doall doone dodir install-baseline install-proc

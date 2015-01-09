ROOT := $(shell pwd)
include $(ROOT)/../defines.mk

SUBDIRS=$(shell find . -mindepth 1 -type d  | grep -v .svn)

all: $(SUBDIRS)

install-proc: install

install-src:

install-baseline:

install: $(SUBDIRS)
	$(foreach dir,$(SUBDIRS), \
		rm -rf ${LIBDESTDIR}/proc/$(dir); \
		mkdir -p ${LIBDESTDIR}/proc/$(dir); \
		cp $(dir)/* ${LIBDESTDIR}/proc/$(dir) 2>>/dev/null; \
		rm ${LIBDESTDIR}/proc/$(dir)/[p32,pmec]*.S; \
		rm ${LIBDESTDIR}/proc/$(dir)/Makefile; )

clean: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all install install-baseline install-proc clean $(SUBDIRS)

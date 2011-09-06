ROOT := $(shell pwd)
include $(ROOT)/../../defines.mk

OUTPUTFILE=processor.o

all: $(OUTPUTFILE)

install: $(OUTPUTFILE)

install-proc: $(OUTPUTFILE)

install-baseline:

install-src:

clean:
	rm -rf $(OUTPUTFILE)

$(OUTPUTFILE): p32mx534f064h.S
	$(CC) -c -o $@ $(SIZE_OPTION) $?

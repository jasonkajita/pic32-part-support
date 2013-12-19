ROOT := $(shell pwd)
include $(ROOT)/../../defines.mk

OUTPUTFILE=processor.o

DIVFILE=default_isr_vectors.o

all: $(OUTPUTFILE) $(DIVFILE)

install: $(OUTPUTFILE) $(DIVFILE)

install-proc: $(OUTPUTFILE) $(DIVFILE)

install-baseline:

install-src:

clean:
	rm -rf $(OUTPUTFILE) $(DIVFILE)

$(OUTPUTFILE): p32mxgeneric.S
	$(CC) -c -o $@ $(SIZE_OPTION) $?

$(DIVFILE): p32mxgeneric_div.S
	$(CC) -c -o $@ $(SIZE_OPTION) $?

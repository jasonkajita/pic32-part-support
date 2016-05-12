ROOT := $(shell pwd)
include $(ROOT)/../../defines.mk

OUTPUTFILE=processor.o

ISRFILE=default_isr_vectors.o

ISRFILE_PIC=default_isr_vectors_pic.o

STARTUP_OPTIONS = -D__LIBBUILD__
STARTUP_OPTIONS += -DPIC32MX
STARTUP_OPTIONS += -D__PIC32_HAS_MIPS32R2
STARTUP_OPTIONS += -DINIT_DATA
STARTUP_OPTIONS += -DPIC32_SRS_SET_COUNT=2

STARTUPOBJ += crt0_mips32r2.o mcrt0_mips32r2.o crti_mips32r2.o crtn_mips32r2.o cpprt0_mips32r2.o crt0_mips32r2_pic.o cpprt0_mips32r2_pic.o

all: $(OUTPUTFILE) $(ISRFILE) $(ISRFILE_PIC) $(STARTUPOBJ)

install: $(OUTPUTFILE) $(ISRFILE) $(ISRFILE_PIC) $(STARTUPOBJ)

install-proc: $(OUTPUTFILE) $(ISRFILE) $(ISRFILE_PIC) $(STARTUPOBJ)

install-baseline:

install-src:

clean:
	rm -rf $(OUTPUTFILE) $(ISRFILE) $(ISRFILE_PIC) $(STARTUPOBJ)

$(OUTPUTFILE): p32mx330f064h.S
	$(CC) -c -o $@ $(SIZE_OPTION) $?

$(ISRFILE): p32mx330f064h_div.S
	$(CC) -c -o $@ $(SIZE_OPTION) $?

$(ISRFILE_PIC): p32mx330f064h_div.S
	$(CC) -fPIC -G0 -c -o $@ $(SIZE_OPTION) $?

mcrt0_mips32r2.o: ../../libpic32/startup/crt0.S
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MX330F064H__ -c -DMCRT0 -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crt0_mips32r2.o: ../../libpic32/startup/crt0.S
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MX330F064H__ -c -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

cpprt0_mips32r2.o: ../../libpic32/startup/crt0.S
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MX330F064H__ -c -DCPP_INIT -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crti_mips32r2.o: ../../libpic32/startup/crti.s
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MX330F064H__ -c -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crtn_mips32r2.o: ../../libpic32/startup/crtn.s
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MX330F064H__ -c -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crt0_mips32r2_pic.o: ../../libpic32/startup/crt0_pic.S
	$(CC)  -fPIC -G0 $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MX330F064H__ -c -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

cpprt0_mips32r2_pic.o: ../../libpic32/startup/crt0_pic.S
	$(CC)  -fPIC -G0 $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MX330F064H__ -c -DCPP_INIT -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@


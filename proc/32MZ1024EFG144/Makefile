ROOT := $(shell pwd)
include $(ROOT)/../../defines.mk

OUTPUTFILE=processor.o

ISROFFSETFILE=vector_offset_init.o

ISROFFSETFILE_PIC=vector_offset_init_pic.o

ISRFILE=default_isr_vectors.o

ISRFILE_PIC=default_isr_vectors_pic.o

STARTUP_OPTIONS = -D__LIBBUILD__
STARTUP_OPTIONS += -DINIT_SSX
STARTUP_OPTIONS += -DPIC32MZ
STARTUP_OPTIONS += -DINIT_MMU_MZ_FIXED
STARTUP_OPTIONS += -DINIT_L1_CACHE
STARTUP_OPTIONS += -DINIT_DSPR2
STARTUP_OPTIONS += -mhard-float -mfp64 -DINIT_FPU64
STARTUP_OPTIONS += -D__PIC32_HAS_MICROMIPS
STARTUP_OPTIONS += -D__PIC32_HAS_MIPS32R2
STARTUP_OPTIONS += -DINIT_DATA
STARTUP_OPTIONS += -DPIC32_SRS_SET_COUNT=8

STARTUPOBJ += crt0_mips32r2.o mcrt0_mips32r2.o crti_mips32r2.o crtn_mips32r2.o cpprt0_mips32r2.o crt0_mips32r2_pic.o cpprt0_mips32r2_pic.o

STARTUPOBJ += crt0_micromips.o mcrt0_micromips.o crti_micromips.o crtn_micromips.o cpprt0_micromips.o crt0_micromips_pic.o cpprt0_micromips_pic.o

all: $(OUTPUTFILE) $(ISRFILE) $(ISROFFSETFILE) $(ISRFILE_PIC) $(ISROFFSETFILE_PIC) $(STARTUPOBJ)

install: $(OUTPUTFILE) $(ISRFILE) $(ISRFILE_PIC) $(ISROFFSETFILE) $(ISROFFSETFILE_PIC) $(STARTUPOBJ)

install-proc: $(OUTPUTFILE) $(ISRFILE) $(ISRFILE_PIC) $(ISROFFSETFILE) $(ISROFFSETFILE_PIC) $(STARTUPOBJ)

install-baseline:

install-src:

clean:
	rm -rf $(OUTPUTFILE) $(ISRFILE) $(ISRFILE_PIC) $(STARTUPOBJ) $(ISROFFSETFILE) $(ISROFFSETFILE_PIC)

$(ISROFFSETFILE): p32mz1024efg144_voff_init.S
	$(CC) -c -o $@ $(SIZE_OPTION) $?

$(ISROFFSETFILE_PIC): p32mz1024efg144_voff_init.S
	$(CC) -fPIC -G0 -c -o $@ $(SIZE_OPTION) $?

$(OUTPUTFILE): p32mz1024efg144.S
	$(CC) -c -o $@ $(SIZE_OPTION) $?

$(ISRFILE): p32mz1024efg144_div.S
	$(CC) -c -o $@ $(SIZE_OPTION) $?

$(ISRFILE_PIC): p32mz1024efg144_div.S
	$(CC) -fPIC -G0 -c -o $@ $(SIZE_OPTION) $?

mcrt0_mips32r2.o: ../../libpic32/startup/crt0.S
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MZ1024EFG144__ -c -DMCRT0 -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crt0_mips32r2.o: ../../libpic32/startup/crt0.S
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MZ1024EFG144__ -c -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

cpprt0_mips32r2.o: ../../libpic32/startup/crt0.S
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MZ1024EFG144__ -c -DCPP_INIT -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crti_mips32r2.o: ../../libpic32/startup/crti.s
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MZ1024EFG144__ -c -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crtn_mips32r2.o: ../../libpic32/startup/crtn.s
	$(CC) $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MZ1024EFG144__ -c -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crt0_mips32r2_pic.o: ../../libpic32/startup/crt0_pic.S
	$(CC)  -fPIC -G0 $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MZ1024EFG144__ -c -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

cpprt0_mips32r2_pic.o: ../../libpic32/startup/crt0_pic.S
	$(CC)  -fPIC -G0 $(ASFLAGS) -mips32r2 -mno-mips16 -mno-micromips -D__32MZ1024EFG144__ -c -DCPP_INIT -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

mcrt0_micromips.o: ../../libpic32/startup/crt0.S
	$(CC) $(ASFLAGS) -D__32MZ1024EFG144__ -c -DMCRT0 -mno-mips16 -mmicromips -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crt0_micromips.o: ../../libpic32/startup/crt0.S
	$(CC) $(ASFLAGS) -D__32MZ1024EFG144__ -c -mno-mips16 -mmicromips -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

cpprt0_micromips.o: ../../libpic32/startup/crt0.S
	$(CC) $(ASFLAGS) -D__32MZ1024EFG144__ -c -DCPP_INIT -mno-mips16 -mmicromips -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crti_micromips.o: ../../libpic32/startup/crti.s
	$(CC) $(ASFLAGS) -D__32MZ1024EFG144__ -c -mno-mips16 -mmicromips -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crtn_micromips.o: ../../libpic32/startup/crtn.s
	$(CC) $(ASFLAGS) -D__32MZ1024EFG144__ -c -mno-mips16 -mmicromips -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crt0_micromips_pic.o: ../../libpic32/startup/crt0_pic.S
	$(CC)  -fPIC -G0 $(ASFLAGS) -D__32MZ1024EFG144__ -c -mno-mips16 -mmicromips -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

cpprt0_micromips_pic.o: ../../libpic32/startup/crt0_pic.S
	$(CC)  -fPIC -G0 $(ASFLAGS) -D__32MZ1024EFG144__ -c -DCPP_INIT -mno-mips16 -mmicromips -I$(ROOT)/../../include $(STARTUP_OPTIONS) $< -o $@
	$(STRIP) $(STRIPFLAGS) $@


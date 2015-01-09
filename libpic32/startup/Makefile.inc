_VPATH	+=:$(ROOT)/startup

LIBOBJ  += general-exception.o
LIBOBJ  += cache-err-exception.o
LIBOBJ  += simple-tlb-refill-exception.o

SUPOBJ	+= crt0.o mcrt0.o crti.o crtn.o cpprt0.o
SUPOBJ  += software-debug-break.o
SUPOBJ  += debug-exception-return.o debug-exception-return-mm.o

# Starting in MPLAB XC32 v1.30, we now build device-specific startup modules.
# See the device-specific Makefile (proc/<device>/Makefile)

# PIC32MX

mcrt0.o: crt0.S
	$(CC) $(ASFLAGS) -c -DMCRT0 -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crt0.o: crt0.S
	$(CC) $(ASFLAGS) -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@
	
cpprt0.o: crt0.S
	$(CC) $(ASFLAGS) -c -D__LIBBUILD__ -DCPP_INIT $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crti.o: crti.s
	$(CC) $(ASFLAGS) -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crtn.o: crtn.s
	$(CC) $(ASFLAGS) -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

# PIC32 all

software-debug-break.o: software-debug-break.c
	$(CC) $(CFLAGS) -Os -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

debug-exception-return.o: debug-exception-return.S
	$(CC) -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

debug-exception-return-mm.o: debug-exception-return.S
	$(CC) -g -mmicromips -D__USE_MICROMIPS=1 -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@
 

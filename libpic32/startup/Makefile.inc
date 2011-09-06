_VPATH	+=:$(ROOT)/startup

LIBOBJ  += general-exception.o
SUPOBJ	+= crt0.o mcrt0.o cpp-startup.o crti.o crtn.o

mcrt0.o: crt0.S
	$(CC) $(ASFLAGS) -c -DMCRT0 -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crt0.o: crt0.S
	$(CC) $(ASFLAGS) -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

cpp-startup.o: cpp-startup.S
	$(CC) $(ASFLAGS) -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crti.o: crti.s
	$(CC) $(ASFLAGS) -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

crtn.o: crtn.s
	$(CC) $(ASFLAGS) -c -D__LIBBUILD__ $< -o $@
	$(STRIP) $(STRIPFLAGS) $@

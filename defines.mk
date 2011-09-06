PREFIX=pic32
TARGET=pic32mx
AR	=$(PREFIX)-ar
CC	=$(PREFIX)-gcc
STRIP =$(PREFIX)-strip

ifndef SDE_MAJOR
# Guess major SDE version based on compiler version
SDE_MAJOR := $(shell \
	if $(CC) -v 2>&1 | fgrep 'gcc version 3.' >/dev/null; then \
	  echo "6"; \
	else \
	  echo "5"; \
	fi)
endif

# Export to sub-makes
export SDE_MAJOR

SKIPARCHS=none

#EXCEPT	=-fexceptions

# Default to optimisation for size
OPTIM	=-Os -fno-optimize-sibling-calls

# Don't generate gp-relative addresses
ifneq (,$(strip $(filter 6,$(SDE_MAJOR))))
GPOPT	=-G0
else
GPOPT	=-mno-gpopt
endif

# Minimal backtrace debug info, no assertion checking
DEBUG	= -g1
ASSERT	=-DNDEBUG=1
CFLAGS	=$(OPTIM) $(VAR) $(GPOPT) $(DEBUG) $(ASSERT) $(EXCEPT) -ffreestanding -ffunction-sections -fdata-sections
ASFLAGS	=$(OPTIM) $(VAR) $(GPOPT) $(ASSERT) $(EXCEPT) -ffreestanding -ffunction-sections -fdata-sections
STRIPFLAGS =-X -g
ARCH	=mips

DESTROOT        =$(HOME)/daytona/install-image
TGTDESTDIR	=$(DESTROOT)/$(TARGET)
TGTLIBSRC	=$(DESTROOT)/pic32-libs
LIBDESTDIR	=$(TGTDESTDIR)/lib
INCDESTDIR	=$(TGTDESTDIR)/include

# To enable multi-byte character support, uncomment the next line
#CFLAGS += -DMB_SUPPORT

# flags to pass to recursive makes
F		=ROOT=$(ROOT)

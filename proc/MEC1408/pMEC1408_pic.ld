/*--------------------------------------------------------------------------
 * MPLAB XC Compiler -  MEC1408 linker script
 * Build date : Feb 18 2016
 * 
 * Copyright (c) 2016, Microchip Technology Inc. and its subsidiaries ("Microchip")
 * All rights reserved.
 * 
 * This software is developed by Microchip Technology Inc. and its
 * subsidiaries ("Microchip").
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are 
 * met:
 * 
 * 1.      Redistributions of source code must retain the above copyright
 *         notice, this list of conditions and the following disclaimer.
 * 2.      Redistributions in binary form must reproduce the above 
 *         copyright notice, this list of conditions and the following 
 *         disclaimer in the documentation and/or other materials provided 
 *         with the distribution.
 * 3.      Microchip's name may not be used to endorse or promote products
 *         derived from this software without specific prior written 
 *         permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWSOEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

/* Default linker script, for position independent executables */

OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH(pic32mx)
ENTRY(_reset)
/*************************************************************************
 * Processor-specific object file.  Contains SFR definitions.
 *************************************************************************/
INPUT("processor.o")


SECTIONS
{
  /* Read-only sections, merged into text segment: */
  . = SEGMENT_START("text-segment", 0) + SIZEOF_HEADERS;
  .reginfo        : { *(.reginfo) }
  .note.gnu.build-id : { *(.note.gnu.build-id) }
  .dynamic        : { *(.dynamic) }
  .hash           : { *(.hash) }
  .gnu.hash       : { *(.gnu.hash) }
  .dynsym         : { *(.dynsym) }
  .dynstr         : { *(.dynstr) }
  .gnu.version    : { *(.gnu.version) }
  .gnu.version_d  : { *(.gnu.version_d) }
  .gnu.version_r  : { *(.gnu.version_r) }
  .rel.dyn        :
  {
    *(.rel.init)
    *(.rel.text .rel.text.* .rel.gnu.linkonce.t.*)
    *(.rel.fini)
    *(.rel.rodata .rel.rodata.* .rel.gnu.linkonce.r.*)
    *(.rel.data.rel.ro .rel.data.rel.ro.* .rel.gnu.linkonce.d.rel.ro.*)
    *(.rel.data .rel.data.* .rel.gnu.linkonce.d.*)
    *(.rel.tdata .rel.tdata.* .rel.gnu.linkonce.td.*)
    *(.rel.tbss .rel.tbss.* .rel.gnu.linkonce.tb.*)
    *(.rel.ctors)
    *(.rel.dtors)
    *(.rel.got)
    *(.rel.dyn)
    *(.rel.sdata .rel.sdata.* .rel.gnu.linkonce.s.*)
    *(.rel.sbss .rel.sbss.* .rel.gnu.linkonce.sb.*)
    *(.rel.sdata2 .rel.sdata2.* .rel.gnu.linkonce.s2.*)
    *(.rel.sbss2 .rel.sbss2.* .rel.gnu.linkonce.sb2.*)
    *(.rel.bss .rel.bss.* .rel.gnu.linkonce.b.*)
    *(.rel.iplt)
  }
  .rela.dyn       :
  {
    *(.rela.init)
    *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*)
    *(.rela.fini)
    *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*)
    *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*)
    *(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*)
    *(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*)
    *(.rela.ctors)
    *(.rela.dtors)
    *(.rela.got)
    *(.rela.sdata .rela.sdata.* .rela.gnu.linkonce.s.*)
    *(.rela.sbss .rela.sbss.* .rela.gnu.linkonce.sb.*)
    *(.rela.sdata2 .rela.sdata2.* .rela.gnu.linkonce.s2.*)
    *(.rela.sbss2 .rela.sbss2.* .rela.gnu.linkonce.sb2.*)
    *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*)
    *(.rela.iplt)
  }
  .rel.plt        :
  {
    *(.rel.plt)
  }
  .rela.plt       :
  {
    *(.rela.plt)
  }
}

SECTIONS
{
  .reset :
  {
    KEEP(*(.reset))
  }

  .app_excpt :
  {
    KEEP(*(.gen_handler))
  }

.plt            : { *(.plt) }
.iplt           : { *(.iplt) }

/*************************************************************************
 * Symbols used for interrupt-vector table generation
 * To override the defaults, define the _vector_spacing & _ebase_address
 * symbols using the --defsym linker opt as shown in these examples:
 *   xc32-gcc src.c -Wl,--defsym=_vector_spacing=2
 *   xc32-gcc src.c -Wl,--defsym=_ebase_address=0x9D001000
 *************************************************************************/
PROVIDE(_vector_spacing = 0x0001);
PROVIDE(_ebase_address = ABSOLUTE(.));


  /* MEC14x4 JTVIC has 19 aggregated interrupt sources in its 
   * power-on-reset configuration. MEC14xx data sheet uses nomenclature 
   * GIRQ00 - GIRQ18.
   * MEC14x4 M14K core was built to support EIC Mode 2 only. The JTVIC 
   * supplies a 17-bit offset to the M14K core. The M14K combines this 
   * 17-bit offset with EBASE to produce the final vector location.
   * Similar to the PIC32MZ EVIC, the JTVIC has a register for each 
   * GIRQx containing the 17-bit value supplied to the M14K core.
   * This means ISR's can be located anywhere above EBASE except for 
   * the fixed location of the General Exception at EBASE + 0x180.
   * All JTVIC ISR's should be put into a named sections .vector_0, 
   * .vector_1, ..., .vector_18
   */
  .vectors _ebase_address + 0x200 :
  {
    KEEP (*(.vector_0))
    KEEP (*(.vector_1))
    KEEP (*(.vector_2))
    KEEP (*(.vector_3))
    KEEP (*(.vector_4))
    KEEP (*(.vector_5))
    KEEP (*(.vector_6))
    KEEP (*(.vector_7))
    KEEP (*(.vector_8))
    KEEP (*(.vector_9))
    KEEP (*(.vector_10))
    KEEP (*(.vector_11))
    KEEP (*(.vector_12))
    KEEP (*(.vector_13))
    KEEP (*(.vector_14))
    KEEP (*(.vector_15))
    KEEP (*(.vector_16))
    KEEP (*(.vector_17))
    KEEP (*(.vector_18))
    KEEP (*(.vec_default))
  }

  /*  The startup code is in the .reset.startup section.
  *  SRAM Application startup code does NOT need to be 
  *  located at the beginning of CODE SRAM. A processor/chip
  *  reset will go to the BootROM reset/startup code and 
  *  begin the BootROM SPI application load sequence.
  *  Upon a successful SPI load and verification, BootROM 
  *  will jump into the Application. We expect the jump address 
  *  to be .startup(reset handler) of the application because 
  *  .startup runs the XC32 startup code and calls C main.
  *  Since application .startup is never entered on a real HW 
  *  reset/nmi/soft-reset it can be located anywhere in SRAM 
  *  CODE space.
  */
  .startup :
  {
    KEEP(*(.startup))
    KEEP(*(.reset.startup))
  }
  .text :
  {
    *(.text.unlikely .text.*_unlikely .text.unlikely.*)
    *(.text.exit .text.exit.*)
    *(.text.hot .text.hot.*)
    *(.text .stub .text.* .gnu.linkonce.t.*)
    KEEP (*(.text.*personality*))
    *(.mips16.fn.*)
    *(.mips16.call.*)
    *(.gnu.warning)
    . = ALIGN(4) ;
  }
  /* Global-namespace object initialization */
  .init   :
  {
    KEEP (*crti.o(.init))
    KEEP (*crtbegin.o(.init))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o *crtn.o ).init))
    KEEP (*crtend.o(.init))
    KEEP (*crtn.o(.init))
    . = ALIGN(4) ;
  }
  .fini   :
  {
    KEEP (*(.fini))
    . = ALIGN(4) ;
  }
  .preinit_array   :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4) ;
  }
  .init_array   :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4) ;
  }
  .fini_array   :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4) ;
  }
  .ctors   :
  {
    /* XC32 uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    . = ALIGN(4) ;
  }
  .dtors   :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    . = ALIGN(4) ;
  }
  /* Read-only sections */
  .rodata   :
  {
    *( .gnu.linkonce.r.*)
    *(.rodata1)
    . = ALIGN(4) ;
  }
  /*
   * Small initialized constant global and static data can be placed in the
   * .sdata2 section.  This is different from .sdata, which contains small
   * initialized non-constant global and static data.
   */
  .sdata2 ALIGN(4) :
  {
    *(.sdata2 .sdata2.* .gnu.linkonce.s2.*)
    . = ALIGN(4) ;
  }
  /*
   * Uninitialized constant global and static data (i.e., variables which will
   * always be zero).  Again, this is different from .sbss, which contains
   * small non-initialized, non-constant global and static data.
   */
  .sbss2 ALIGN(4) :
  {
    *(.sbss2 .sbss2.* .gnu.linkonce.sb2.*)
    . = ALIGN(4) ;
  }
  .eh_frame_hdr   :
  {
    *(.eh_frame_hdr)
  }
    . = ALIGN(4) ;
  .eh_frame   : ONLY_IF_RO
  {
    KEEP (*(.eh_frame))
  }
    . = ALIGN(4) ;
  .gcc_except_table   : ONLY_IF_RO
  {
    *(.gcc_except_table .gcc_except_table.*)
  }
    . = ALIGN(4) ;
  .gnu_extab   : ONLY_IF_RO
  {
    *(.gnu_extab*)
  }
    . = ALIGN(4) ;
  .jcr   :
  {
    KEEP (*(.jcr))
    . = ALIGN(4) ;
  }
  .eh_frame    : ONLY_IF_RW
  {
    KEEP (*(.eh_frame))
    KEEP (*(.eh_frame.*))
  }
    . = ALIGN(4) ;
  .gcc_except_table    : ONLY_IF_RW
  {
    *(.gcc_except_table .gcc_except_table.*)
  }
    . = ALIGN(4) ;
  .gnu_extab      : ONLY_IF_RW { *(.gnu_extab) }
    . = ALIGN(4) ;
  .exception_ranges   : ONLY_IF_RW { *(.exception_ranges .exception_ranges*) }
    . = ALIGN(4) ;
  /* Persistent data - Use the new C 'persistent' attribute instead. */
  .persist   :
  {
    _persist_begin = .;
    *(.persist .persist.*)
    *(.pbss .pbss.*)
    . = ALIGN(4) ;
    _persist_end = .;
  }
  .data.rel.ro : { *(.data.rel.ro.local* .gnu.linkonce.d.rel.ro.local.*) *(.data.rel.ro .data.rel.ro.* .gnu.linkonce.d.rel.ro.*) }
  .got.plt        : { *(.got.plt) }
  .data   :
  {
    *(.data .data.* .gnu.linkonce.d.*)
    SORT(CONSTRUCTORS)
    . = ALIGN(4) ;
  }
  .data1          : { *(.data1) }
  . = .;
  _gp = ALIGN(16);
  .got ALIGN(4) :
  {
    *(.got)
    . = ALIGN(4) ;
  }
  /*
   * Note that 'small' data sections are still mapped in the linker
   * script. This ensures that they are grouped together for
   * gp-relative addressing. Absolute sections are allocated after
   * the 'small' data sections so small data cannot flow around them.
   */
  /*
   * We want the small data sections together, so single-instruction offsets
   * can access them all, and initialized data all before uninitialized, so
   * we can shorten the on-disk segment size.
   */
  .sdata ALIGN(4) :
  {
    _sdata_begin = . ;
    *(.sdata .sdata.* .gnu.linkonce.s.*)
    . = ALIGN(4) ;
    _sdata_end = . ;
  }
  .lit8           :
  {
    *(.lit8)
  }
  .lit4           :
  {
    *(.lit4)
  }
  . = ALIGN (4) ;
  _data_end = . ;
  _bss_begin = . ;
  .sbss ALIGN(4) :
  {
    _sbss_begin = . ;
    *(.dynsbss)
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
    _sbss_end = . ;
    . = ALIGN(4) ;
  }
  /*
   *  Align here to ensure that the .bss section occupies space up to
   *  _end.  Align after .bss to ensure correct alignment even if the
   *  .bss section disappears because there are no input sections.
   *
   *  Note that input sections named .bss* are no longer mapped here.
   *  The best-fit allocator locates them, so that they may flow
   *  around absolute sections as needed.
   *
   */
  .bss     :
  {
    *(.dynbss)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
   /* Align here to ensure that the .bss section occupies space up to
      _end.  Align after .bss to ensure correct alignment even if the
      .bss section disappears because there are no input sections. */
   . = ALIGN(. != 0 ? 4 : 1);
  }
  . = ALIGN(4) ;
  _end = . ;
  _bss_end = . ;
    /* The .pdr section belongs in the absolute section */
    /DISCARD/ : { *(.pdr) }
  .gptab.sdata : { *(.gptab.data) *(.gptab.sdata) }
  .gptab.sbss : { *(.gptab.bss) *(.gptab.sbss) }
  .mdebug.abi32 : { KEEP(*(.mdebug.abi32)) }
  .mdebug.abiN32 : { KEEP(*(.mdebug.abiN32)) }
  .mdebug.abi64 : { KEEP(*(.mdebug.abi64)) }
  .mdebug.abiO64 : { KEEP(*(.mdebug.abiO64)) }
  .mdebug.eabi32 : { KEEP(*(.mdebug.eabi32)) }
  .mdebug.eabi64 : { KEEP(*(.mdebug.eabi64)) }
  .gcc_compiled_long32 : { KEEP(*(.gcc_compiled_long32)) }
  .gcc_compiled_long64 : { KEEP(*(.gcc_compiled_long64)) }
  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections used by MPLAB X for source-level debugging. 
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  /DISCARD/ : { *(.note.GNU-stack) }
  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.discard) }
}


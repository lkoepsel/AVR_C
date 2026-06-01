DEPTH = ../../
# Pull the assembly soft-serial primitives (init_soft_serial, soft_char_write,
# soft_char_read) into the build. ASM_LIBS is appended to ASM_SOURCES in the
# root Makefile; deferred expansion means $(LIBDIR) is resolved at use time.
ASM_LIBS = $(LIBDIR)/serial_asm.S $(LIBDIR)/registers.S
include $(DEPTH)Makefile


EXTHDRS =
PKGFLAG =

include ../src.makefile

BINDIR = ../../bin
TARGET = $(BINDIR)/$(EXEC)

target: $(TARGET)

$(TARGET): $(COBJS) $(LIBCHECKPOINT)
	@$(ECHO) "> building: $(EXEC) ..."
	@$(CXX) $(CFLAGS) $(WFLAGS) $(FFLAGS) $(DPNIFLAG) $(DPNLFLAG) $(COBJS) -o $@ $(INCLIB)

CPPSRC += $(wildcard engine/*.cpp)
#CPPSRC += $(wildcard opengltest/*.cpp)


include ../src.makefile

BINDIR = ../../bin
TARGET = $(BINDIR)/engine #\
		 $(BINDIR)/opengltest

target: $(TARGET)

$(BINDIR)/engine: $(COBJS) $(LIBCHECKPOINT)
	@$(ECHO) "> building: $@ ..."
	@$(CXX) $(CFLAGS) $(WFLAGS) $(FFLAGS) $(PKGFLAG) $(DPNIFLAG) $(DPNLFLAG) $(COBJS) -o $@ $(INCLIB)
	@cd ../../; ln -fs bin/engine .

$(BINDIR)/opengltest: $(COBJS) $(LIBCHECKPOINT)
	@$(ECHO) "> building: $@ ..."
	@$(CXX) $(CFLAGS) $(WFLAGS) $(FFLAGS) $(PKGFLAG) $(DPNIFLAG) $(DPNLFLAG) $(COBJS) -o $@ $(INCLIB)
	@cd ../../; ln -fs bin/opengltest .

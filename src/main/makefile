CPPSRC += $(wildcard engine/*.cpp)
CPPSRC += $(wildcard engineEditor/*.cpp)
#CPPSRC += $(wildcard opengltest/*.cpp)


include ../src.makefile

BINDIR = ../../bin
TARGET = $(BINDIR)/engine \
		 $(BINDIR)/engineEditor #\
		 $(BINDIR)/opengltest

target: $(TARGET)

$(BINDIR)/engine: $(COBJS) $(LIBCHECKPOINT)
	@$(ECHO) "> building: $@ ..."
	@$(CXX) $(CFLAGS) $(WFLAGS) $(FFLAGS) $(PKGFLAG) $(DPNIFLAG) $(DPNLFLAG) engine/main.o -o $@ $(INCLIB)
	@cd ../../; ln -fs bin/engine .

$(BINDIR)/engineEditor: $(COBJS) $(LIBCHECKPOINT)
	@$(ECHO) "> building: $@ ..."
	@$(CXX) $(CFLAGS) $(WFLAGS) $(FFLAGS) $(PKGFLAG) $(DPNIFLAG) $(DPNLFLAG) engineEditor/main.o -o $@ $(INCLIB)
	@cd ../../; ln -fs bin/engineEditor .

$(BINDIR)/opengltest: $(COBJS) $(LIBCHECKPOINT)
	@$(ECHO) "> building: $@ ..."
	@$(CXX) $(CFLAGS) $(WFLAGS) $(FFLAGS) $(PKGFLAG) $(DPNIFLAG) $(DPNLFLAG) $(COBJS) -o $@ $(INCLIB)
	@cd ../../; ln -fs bin/opengltest .

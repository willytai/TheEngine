CPPSRC += $(wildcard engine/*.cpp)
CPPSRC += $(wildcard opengltest/*.cpp)


include ../src.makefile

BINDIR = ../../bin
TARGET = $(BINDIR)/engine #\
		 $(BINDIR)/opengltest

target: $(TARGET)

$(BINDIR)/engine: engine/main.o $(LIBCHECKPOINT)
	@$(ECHO) "> building: $@ ..."
	@$(CXX) $(CFLAGS) $(WFLAGS) $(FFLAGS) $(PKGFLAG) $(DPNIFLAG) $(DPNLFLAG) $< -o $@ $(INCLIB)
	@cd ../../; ln -fs bin/engine .

$(BINDIR)/opengltest: opengltest/main.o $(LIBCHECKPOINT)
	@$(ECHO) "> building: $@ ..."
	@$(CXX) $(CFLAGS) $(WFLAGS) $(FFLAGS) $(PKGFLAG) $(DPNIFLAG) $(DPNLFLAG) $< -o $@ $(INCLIB)
	@cd ../../; ln -fs bin/opengltest .

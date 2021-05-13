CHDRS  += $(wildcard *.h)
CPPSRC += $(wildcard *.cpp)
CPPSRC += $(wildcard *.mm)
CCCSRC += $(wildcard *.c)
CSRCS  = $(CPPSRC) $(CCCSRC)
COBJS  = $(addsuffix .o, $(basename $(CSRCS)))

EXTDIR = ../../src
INCDIR = . $(EXTDIR) /usr/local/Cellar/glfw/3.3.2/include \
		 ../../vendor/spdlog/include \
		 ../../vendor/glad/include \
		 ../../vendor/stb/include \
		 ../../vendor/imgui \
		 ../../vendor/glm \
		 ../../vendor
DPNIFLAG = $(addprefix -I, $(INCDIR))

LIBDIR = ../../lib /usr/local/Cellar/glfw/3.3.2/lib
DPNLFLAG = $(addprefix -L, $(LIBDIR))

LIBCHECKPOINT = ../../lib/.lib.check

CXX  = clang++
CCC  = cc
AR   = ar cr
ECHO = /bin/echo

# optimized
COMMONFLAGS = -DENGINE_BACKEND_OPENGL \
			  -DNDEBUG
# debug
COMMONFLAGS = -DENGINE_BACKEND_OPENGL \
			  -DENGINE_DEBUG

CPPFLAGS = -O3 -std=c++17 $(COMMONFLAGS)
CPPFLAGS = -g  -std=c++17 $(COMMONFLAGS)

CFLAGS = -O3 $(COMMONFLAGS)
CFLAGS = -g  $(COMMONFLAGS)

WFLAGS = -Wall -Wno-nullability-completeness -Wextra -pedantic-errors -Wconversion -Wno-gnu-anonymous-struct -Wno-nested-anon-types -Wformat
FFLAGS = -framework Metal -framework MetalKit -framework Cocoa -framework IOKit -framework CoreVideo -framework QuartzCore

top: target

%.o: %.cpp
	@$(ECHO) "> compiling $< ..."
	@$(CXX) $(CPPFLAGS) $(WFLAGS) $(DPNIFLAG) -ObjC++ -fobjc-weak -fobjc-arc -c -o $@ $<

%.o: %.c
	@$(ECHO) "> compiling $< ..."
	@$(CCC) $(CFLAGS) $(WFLAGS) $(DPNIFLAG) -c -o $@ $<

%.o: %.mm
	@$(ECHO) "> compiling $< ..."
	@$(CXX) $(CPPFLAGS) $(WFLAGS) $(DPNIFLAG) -ObjC++ -fobjc-weak -fobjc-arc -c -o $@ $<

.PHONY: depend
depend: .depend.mak
.depend.mak: $(CHDRS) $(CSRCS)
	@$(ECHO) Making dependencies ...
	@$(CXX) -MM $(DPNIFLAG) $(COMMONFLAGS) $(CSRCS) > $@

.PHONY: clean
clean:
	@rm -f $(COBJS)

.PHONY: cleanall
cleanall: clean
	@$(ECHO) Removing dependencies ...
	@rm .depend.mak

include .depend.mak

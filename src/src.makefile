CHDRS  += $(wildcard *.h)
CPPSRC += $(wildcard *.cpp)
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

CXX  = c++
CCC  = cc
AR   = ar cr
ECHO = /bin/echo

COMMONFLAGS = -DENGINE_BACKEND_OPENGL \
			  -DBUILD_TEST

CPPFLAGS = -O3 -std=c++17 $(COMMONFLAGS) -DNDEBUG
CPPFLAGS = -g  -std=c++17 $(COMMONFLAGS) -DENGINE_DEBUG

CFLAGS = -O3 -DNDEBUG
CFLAGS = -g  -DENGINE_DEBUG

WFLAGS = -Wall -Wextra -pedantic-errors -Wconversion
FFLAGS =

top: target

%.o: %.cpp
	@$(ECHO) "> compiling $< ..."
	@$(CXX) $(CPPFLAGS) $(WFLAGS) $(FFLAGS) $(DPNIFLAG) -c -o $@ $<

%.o: %.c
	@$(ECHO) "> compiling $< ..."
	@$(CCC) $(CFLAGS) $(WFLAGS) $(FFLAGS) $(DPNIFLAG) -c -o $@ $<

.PHONY: depend
depend: .depend.mak
.depend.mak: $(CHDRS) $(CSRCS)
	@$(ECHO) Making dependencies ...
	@$(CXX) -MM $(DPNIFLAG) $(CSRCS) > $@

.PHONY: clean
clean:
	@rm -f $(COBJS)

.PHONY: cleanall
cleanall: clean
	@$(ECHO) Removing dependencies ...
	@rm .depend.mak

include .depend.mak

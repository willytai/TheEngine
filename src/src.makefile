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
		 ../../vendor/glm
DPNIFLAG = $(addprefix -I, $(INCDIR))

LIBDIR = ../../lib /usr/local/Cellar/glfw/3.3.2/lib
DPNLFLAG = $(addprefix -L, $(LIBDIR))

LIBCHECKPOINT = ../../lib/.lib.check

CXX  = c++
CCC  = cc
AR   = ar cr
ECHO = /bin/echo

CPPFLAGS = -O3 -std=c++17 -DNDEBUG -DENGINE_DEBUG
CPPFLAGS = -g  -std=c++17

CFLAGS = -O3 -DNDEBUG -DENGINE_DEBUG
CFLAGS = -g

WFLAGS = -Wall -Wextra -pedantic-errors -Wconversion
FFLAGS = -DBUILD_TEST

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

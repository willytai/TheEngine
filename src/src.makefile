CHDRS  = $(wildcard *.h)
CPPSRC = $(wildcard *.cpp)
CCCSRC = $(wildcard *.c)
CSRCS  = $(CPPSRC) $(CCCSRC)
COBJS  = $(addsuffix .o, $(basename $(CSRCS)))

EXTDIR = ../../include
INCDIR = . $(EXTDIR) /usr/local/Cellar/glfw/3.3.2/include \
		 ../../vendor/spdlog/include \
		 ../../vendor/glad/include \
		 ../../vendor/stb/include
DPNIFLAG = $(addprefix -I, $(INCDIR))

LIBDIR = ../../lib /usr/local/Cellar/glfw/3.3.2/lib
DPNLFLAG = $(addprefix -L, $(LIBDIR))

EXTLINK = $(PKGNAME)LNK
LIBCHECKPOINT = ../../lib/.lib.check

CXX  = c++
CCC  = cc
AR   = ar cr
ECHO = /bin/echo

CPPFLAGS = -O3 -std=c++17 $(PKGFLAG) -DNDEBUG
CPPFLAGS = -g  -std=c++17 $(PKGFLAG)

CFLAGS = -O3 $(PKGFLAG) -DNDEBUG
CFLAGS = -g  $(PKGFLAG)

WFLAGS = -Wall -Wextra -pedantic-errors -Wconversion
FFLAGS =

top: $(EXTLINK) target

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

.PHONY: extheader
extheader: .extheader.mak
.extheader.mak: $(EXTHDRS)
	@$(ECHO) Linking external header files ...
	@rm -f $@
	@$(ECHO) -n "$(EXTLINK):" > $@
	@for hdr in $(EXTHDRS); \
	do \
		$(ECHO) -n " $(EXTDIR)/$$hdr" >> $@; \
		rm -f $(EXTDIR)/$$hdr; \
	done
	@$(ECHO) >> $@
	@for hdr in $(EXTHDRS); \
	do \
		$(ECHO) "$(EXTDIR)/$$hdr: $$hdr" >> $@; \
		$(ECHO) "	@cd $(EXTDIR); ln -fs ../src/$(PKGNAME)/$$hdr ./" >> $@; \
	done

.PHONY: clean
clean:
	@rm -f $(COBJS)

.PHONY: cleanall
cleanall: clean
	@$(ECHO) Removing dependencies ...
	@rm .depend.mak .extheader.mak

include .depend.mak
include .extheader.mak

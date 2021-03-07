ECHO      = /bin/echo
ifneq ($(shell uname -s), Darwin)
	ECHO += -e
endif
SRCLIBDIR = lib
DIRS      = bin $(SRCLIBDIR)

# third party packages
VENDOR = ../vendor/spdlog/include/ \
		 ../vendor/glad/include \
		 ../vendor/stb/include \
		 ../vendor/glm

PKGS    = util glad backend platform core imgui tests
GLFW    = glfw
EXTPKG  = $(GLFW)
ALLPKGS = $(PKGS) $(EXTPKG)
INCLIB  = $(addprefix -l, $(ALLPKGS))

SRCLIBS = $(addsuffix .a, $(addprefix lib, $(PKGS)))
GLFWLIB = $(addsuffix .a, $(addprefix lib, $(GLFW)))

all: dir main

.PHONY: dir libs main

dir:
	@for dir in $(DIRS); \
	do \
		if [ ! -d $$dir ]; then \
			mkdir $$dir; \
			$(ECHO) "Creating directory \"$$dir\" ..."; \
		fi; \
	done


main: libs
	@$(ECHO) "Checking main ..."
	@$(MAKE) -C src/main -f makefile --no-print-directory INCLIB="$(INCLIB)"

libs:
	@for pkg in $(PKGS); \
	do \
		$(ECHO) "Checking $$pkg ..."; \
		$(MAKE) -C src/$$pkg -f makefile --no-print-directory PKGNAME=$$pkg; \
	done

.PHONY: cppcheck
cppcheck:
	@cppcheck . --enable=all --std=c++14 2> check.txt
	@$(ECHO) "\033[33mcppcheck finished, see results in ./check.txt\033[30m"

cleanall:
	@for pkg in $(PKGS); \
	do \
		$(ECHO) "Cleaning $$pkg ..."; \
		$(MAKE) -C src/$$pkg -f makefile --no-print-directory PKGNAME=$$pkg cleanall; \
	done
	@$(ECHO) "Cleaning main ..."
	@$(MAKE) -C src/main -f makefile --no-print-directory cleanall;
	@for slib in $(SRCLIBS); \
	do \
		$(ECHO) "Removing $$slib ..."; \
		rm -rf $(SRCLIBDIR)/$$slib; \
	done
	@for exec in $(wildcard bin/*)
	do \
		@$(ECHO) "Removing $$exec ..."; \
		@rm -f $$exec $(notdir $$exec); \
	done

clean:
	@for pkg in $(PKGS); \
	do \
		$(ECHO) "Cleaning $$pkg ..."; \
		$(MAKE) -C src/$$pkg -f makefile --no-print-directory PKGNAME=$$pkg clean; \
	done
	@$(ECHO) "Cleaning main ..."
	@$(MAKE) -C src/main -f makefile --no-print-directory clean;
	@for slib in $(SRCLIBS); \
	do \
		$(ECHO) "Removing $$slib ..."; \
		rm -rf $(SRCLIBDIR)/$$slib; \
	done
	@for exec in $(notdir $(wildcard bin/*)); \
	do \
		rm -f $$exec; \
	done
	@for exec in $(wildcard bin/*); \
	do \
		$(ECHO) "Removing $$exec ..."; \
		rm -f $$exec; \
	done

.PHONY: tags
tags: ctags
ctags:
	@rm -f src/tags
	@for pkg in $(PKGS); \
	do \
		$(ECHO) "Tagging $$pkg ... "; \
		cd src; \
		ctags -aR --languages=C,C++ $$pkg/*; \
		cd ..; \
	done
	@for pkg in $(VENDOR); \
	do \
		$(ECHO) "Tagging $$pkg ... "; \
		cd src; \
		ctags -a --languages=C,C++ $$pkg/*; \
		cd ..; \
	done
	@$(ECHO) "Tagging main ... "
	@cd src; ctags -aR  --languages=C,C++ main/*;

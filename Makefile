ECHO      = /bin/echo
ifneq ($(shell uname -s), Darwin)
	ECHO += -e
endif
EXEC      = opengltest
SRCLIBDIR = lib
DIRS      = bin include $(SRCLIBDIR)

# third party packages
VENDOR = ../vendor/spdlog/include/ \
		 ../vendor/glad/include \
		 ../vendor/stb/include \
		 ../vendor/glm

PKGS    = util glad core imgui tests
GLFW    = glfw
EXTPKG  = $(GLFW)
ALLPKGS = $(PKGS) $(EXTPKG)
INCLIB  = $(addprefix -l, $(ALLPKGS))

SRCLIBS = $(addsuffix .a, $(addprefix lib, $(PKGS)))
GLFWLIB = $(addsuffix .a, $(addprefix lib, $(GLFW)))

all: dir main

.PHONY: dir libs main

glfw: $(SRCLIBDIR)/$(GLFWLIB)
$(SRCLIBDIR)/$(GLFWLIB):
	@echo "Compiling glfw3 as static library ..."
	@mkdir -p glfw-build;
	@cd glfw-build; cmake ../vendor/glfw/ -DCMAKE_INSTALL_PREFIX=./install\
		-DBUILD_SHARED_LIBS=OFF \
		-DGLFW_BUILD_EXAMPLES=FALSE \
		-DGLFW_BUILD_TESTS=FALSE \
		-DGLFW_BUILD_DOCS=OFF \
		-DGLFW_INSTALL=ON; make -j4
	#@mv glfw-build/src/$(GLFWLIB) $@

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
	@$(MAKE) -C src/main -f makefile --no-print-directory INCLIB="$(INCLIB)" EXEC=$(EXEC)
	@ln -fs bin/$(EXEC) .


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
	@$(ECHO) "Removing $(EXEC) ..."
	@rm -f $(EXEC) bin/$(EXEC)

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
	@$(ECHO) "Removing $(EXEC) ..."
	@rm -f $(EXEC) bin/$(EXEC)

.PHONY: tags
tags: ctags
ctags:
	@rm -f src/tags
	@for pkg in $(PKGS); \
	do \
		$(ECHO) "Tagging $$pkg ... "; \
		cd src; \
		ctags -a --languages=C,C++ $$pkg/*; \
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
	@cd src; ctags -a  --languages=C,C++ main/*;

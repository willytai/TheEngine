LIBNAME = lib$(PKGNAME).a
TARGET  = ../../lib/$(LIBNAME)

target: $(TARGET)

$(TARGET): $(COBJS)
	@$(ECHO) "Building $(LIBNAME) ..."
	@$(AR) $@ $(COBJS)
	@touch $(LIBCHECKPOINT)

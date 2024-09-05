# Compiler and options
GCC := gcc
OPT := -static -g -Wall -Wextra -finput-charset=UTF-8 -Wno-unused-parameter -Wno-format-extra-args -Wformat=0
LDFLAGS :=
TARGET := crm

SRCDIR := src
INCDIR := $(SRCDIR)/../Include
BUILDDIR := build
SRC_FILES := $(wildcard $(SRCDIR)/*.c)
OBJ_FILES := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC_FILES))
GCCFLAGS := $(OPT) -I$(INCDIR) -I$(SRCDIR)/../Environment -I..
TESTBUILDDIR := $(BUILDDIR)/test
TESTDIR := test
TEST_SUBDIRS := $(wildcard $(TESTDIR)/*)
TEST_FILES := $(wildcard $(TESTDIR)/*.c)
TEST_OBJ_FILES := $(patsubst $(TESTDIR)/%/%.c,$(TESTBUILDDIR)/%.o,$(TEST_FILES))

ifeq ($(OS),Windows_NT)
    DEL := del /Q
    MKDIR := if not exist
    RM := rmdir /s /q
    EXE := .exe
    SEPARATOR := \
else
    DEL := rm -f
    MKDIR := mkdir -p
    RM := rm -rf
    EXE :=
    SEPARATOR := /
endif

# Targets
$(BUILDDIR)/$(TARGET): $(OBJ_FILES)
	$(GCC) $(GCCFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

define test-dir-rule
SUBDIR_OBJ := $$(patsubst $(1)/%.c,$(TESTBUILDDIR)/$(notdir $(1))/%.o,$$(wildcard $(1)/*.c))

$(TESTBUILDDIR)/$(notdir $(1))$(EXE): $$(SUBDIR_OBJ)
	$(GCC) $(GCCFLAGS) $$^ -o $$@

$$(SUBDIR_OBJ): $(TESTBUILDDIR)/$(notdir $(1))/%.o: $(1)/%.c
	$(MKDIR) "$(TESTBUILDDIR)$(SEPARATOR)$(notdir $(1))"
	$(GCC) $(GCCFLAGS) -c $$< -o $$@
endef

$(foreach subdir,$(TEST_SUBDIRS),$(eval $(call test-dir-rule,$(subdir))))
test: $(patsubst $(TESTDIR)/%,$(TESTBUILDDIR)/%.exe,$(TEST_SUBDIRS))
	$(foreach dir,$(TEST_SUBDIRS),$(RM) $(BUILDDIR)$(SEPARATOR)test$(SEPARATOR)$(notdir $(dir)))

clean:
  ifeq ($(OS),Windows_NT)
		del /Q build/*.o
  else
		rm -f build/*.o
  endif

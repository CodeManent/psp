## Build flags for all targets
#
CXX ?= g++
CXXFLAGS += -g -march=native -pedantic -Wall -Werror -Wextra -std=c++17 -fPIC -fpic # -flto -fwhole-program 
LDFLAGS  += -fuse-linker-plugin
LF_ALL   +=
LL_ALL   +=

BIN    = psp
BINDIR = bin
SRCDIR = src

TARGET_BIN=$(BINDIR)/$(BIN)
# custom rules

#compilation rules
$(BINDIR)/%.cpp.o: $(SRCDIR)/%.cpp $(BINDIR)/%.cpp.d
	$(CXX) $(CXXFLAGS) -c -o $@ $<

#Makefile driver creation rules
$(BINDIR)/%.cpp.d: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -MM -MF $@ -MT '$(TARGET_BIN) $(@:%.cpp.d=%.cpp.o)'

# Standard things
.PHONY: all

all: targets

# Collect all the sources
dir=$(SRCDIR)
include $(SRCDIR)/Rules.mk

#Generate object and dependency filenames from the sources
OBJS  := $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.cpp.o,$(SRC))
DEPS  := $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.cpp.d,$(SRC))
-include $(DEPS)

CLEAN := $(CLEAN) $(OBJS) $(DEPS)

#Depend on everything
$(TARGET_BIN): $(SRC) $(OBJS) $(DEPS)
	@echo "Building (linking) target bin: " $@
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# The variables TARGET_*, CLEAN and CMD_INST* may be added to by the Makefile
# fragments in the various subdirectories

.PHONY: targets
targets: $(TARGET_BIN)

.PHONY: clean
clean:
	@$(RM) $(CLEAN) $(TARGET_BIN)

.PHONY: run
run: $(TARGET_BIN)
	./$(TARGET_BIN)

.PHONY: test
test: $(TARGET_BIN)
	./$(TARGET_BIN) --test

# Check the code using cppcheck.
.PHONY: check
check:
	cppcheck --enable=all -q .

.PHONY: echo
echo:
	@echo TARGET_BIN : $(TARGET_BIN)
	@echo BIN        : $(BIN)
	@echo BINDIR     : $(BINDIR)
	@echo SRCDIR     : $(SRCDIR)
	@echo SRC        : $(SRC)
#	@echo OBJS       : $(OBJS)
#	@echo DEPS       : $(DEPS)
	@echo CLEAN      : $(CLEAN)

# Prevent make from removing any build targets, including intermediate ones
.SECONDARY: $(CLEAN)

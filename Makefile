## Build flags for all targets
#
CXX ?= g++
CXXFLAGS += -g -pedantic -Wall -Werror -Wextra -std=c++11 -fPIC -flto
CC       ?= $(CXX)
CFLAGS   = $(CXXFLAGS)
LDFLAGS +=
LF_ALL   +=
LL_ALL   +=

BINDIR=../bin
# custom rules

#compilation rules
$(BINDIR)/%.o: %.cpp $(BINDIR)/%.d
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BINDIR)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(BINDIR)/%.o: %.c
	$(CC) $(CXXFLAGS)  -c -o $@ $<

#Makefile driver creation rules
# don't show the d file creation command
$(BINDIR)/%.d: %.c
	@$(CC) $(CXXFLAGS) $< -MM -MF $@ 

$(BINDIR)/%.d: %.cpp
	@$(CXX) $(CXXFLAGS) $< -MM -MF $@ -MT '$(@:%.d=%.o)'

$(BINDIR)/%.d: %.cc
	@$(CXX) $(CXXFLAGS) $< -MM -MF $@ -MT '$(@:%.d=%.o)'

# Standard things
.PHONY: all

all: targets

dir:=.
include Rules.mk


# The variables TARGET_*, CLEAN and CMD_INST* may be added to by the Makefile
# fragments in the various subdirectories

.PHONY: targets
targets: $(TARGET_BIN) $(TARGET_SBIN) $(TARGET_ETC) $(TARGET_LIB)

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

# Prevent make from removing any build targets, including intermediate ones
.SECONDARY: $(CLEAN)


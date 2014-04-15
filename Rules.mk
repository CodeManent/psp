# Standard things
#increase stack pointer
sp				:= $(sp).x

# save previous d (dir) in stack 
dirstack_$(sp)	:= $(d)

# set d to the new dir
d				:= $(dir)

# Subdirectories, in random order
dir := $(d)/Allegrex
include $(dir)/Rules.mk


OBJS_$(d)	:= $(BINDIR)/$(d)/main.o \
			$(BINDIR)/$(d)/AVCDecoder.o \
			$(BINDIR)/$(d)/BusDevice.o \
			$(BINDIR)/$(d)/DMAC.o \
			$(BINDIR)/$(d)/MainMemory.o \
			$(BINDIR)/$(d)/MediaEngine.o \
			$(BINDIR)/$(d)/PSP.o \
			$(BINDIR)/$(d)/SubMemory.o \
			$(BINDIR)/$(d)/Tests.o \
			$(BINDIR)/$(d)/VME.o

DEPS_$(d)	:= $(OBJS_$(d):%.o=%.d)

CLEAN		:= $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d))


TARGET_BIN := $(BINDIR)/$(d)/psp
TARGET_OBJS := $(TARGET_OBJS) $(OBJS_$(d))


$(TARGET_BIN): $(TARGET_OBJS)
	@echo "Building (linking) target bin: " $(TARGET_BIN)
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)



# Incude dependency descriptors
-include $(DEPS_$(d))

# Retrieve previous directory from dirstack
d		:= $(dirstack_$(sp))

# Decrease the stack pointer.
# With the use of the basename we trim the extention (.x) that was appended at the start
# of the rules. So mentally decrease the stack pointer
sp		:= $(basename $(sp))

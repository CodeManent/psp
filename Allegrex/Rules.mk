# Standard things
#increase stack pointer
sp				:= $(sp).x

# save previous d (dir) in stack 
dirstack_$(sp)	:= $(d)

# set d to the new dir
d				:= $(dir)

# Subdirectories, in random order
dir := $(d)/Basic
include $(dir)/Rules.mk

dir := $(d)/Special
include $(dir)/Rules.mk

dir := $(d)/COP0_INST
include $(dir)/Rules.mk

OBJS_$(d)	:= $(BINDIR)/$(d)/Allegrex.o \
			$(BINDIR)/$(d)/COP0.o \
			$(BINDIR)/$(d)/FPU.o \
			$(BINDIR)/$(d)/Cache.o \
			$(BINDIR)/$(d)/Instruction.o \
			$(BINDIR)/$(d)/UnimplementedOp.o

DEPS_$(d)	:= $(OBJS_$(d):%.o=%.d)

CLEAN		:= $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d))


TARGET_BIN := $(BINDIR)/$(d)/psp
TARGET_OBJS := $(TARGET_OBJS) $(OBJS_$(d))


$(TARGET_BIN): $(TARGET_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)



# Incude dependency descriptors
-include $(DEPS_$(d))

# Retrieve previous directory from dirstack
d		:= $(dirstack_$(sp))

# Decrease the stack pointer.
# With the use of the basename we trim the extention (.x) that was appended at the start
# of the rules. So mentally decrease the stack pointer
sp		:= $(basename $(sp))

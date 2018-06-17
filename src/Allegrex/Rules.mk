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

SRC := $(SRC)                \
	$(d)/Allegrex.cpp        \
	$(d)/COP0.cpp            \
	$(d)/FPU.cpp             \
	$(d)/VFPU.cpp            \
	$(d)/Cache.cpp           \
	$(d)/Instruction.cpp     \
	$(d)/UnimplementedOp.cpp

# Retrieve previous directory from dirstack
d		:= $(dirstack_$(sp))

# Decrease the stack pointer.
# With the use of the basename we trim the extention (.x) that was appended at the start
# of the rules. So mentally decrease the stack pointer
sp		:= $(basename $(sp))

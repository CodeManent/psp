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


SRC := $(SRC)            \
	$(d)/main.cpp        \
	$(d)/AVCDecoder.cpp  \
	$(d)/BusDevice.cpp   \
	$(d)/DMAC.cpp        \
	$(d)/MainMemory.cpp  \
	$(d)/MediaEngine.cpp \
	$(d)/PSP.cpp         \
	$(d)/SubMemory.cpp   \
	$(d)/Tests.cpp       \
	$(d)/VME.cpp

# Retrieve previous directory from dirstack
d		:= $(dirstack_$(sp))

# Decrease the stack pointer.
# With the use of the basename we trim the extention (.x) that was appended at the start
# of the rules. So mentally decrease the stack pointer
sp		:= $(basename $(sp))

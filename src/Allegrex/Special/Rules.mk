# Standard things
#increase stack pointer
sp				:= $(sp).x

# save previous d (dir) in stack 
dirstack_$(sp)	:= $(d)

# set d to the new dir
d				:= $(dir)

SRC := $(SRC)     \
	$(d)/ADDU.cpp \
	$(d)/AND.cpp  \
	$(d)/JALR.cpp \
	$(d)/JR.cpp   \
	$(d)/MAX.cpp  \
	$(d)/MIN.cpp  \
	$(d)/NOP.cpp  \
	$(d)/NOR.cpp  \
	$(d)/OR.cpp   \
	$(d)/SLL.cpp  \
	$(d)/SLLV.cpp \
	$(d)/SLT.cpp  \
	$(d)/SLTU.cpp \
	$(d)/SRA.cpp  \
	$(d)/SUBU.cpp \
	$(d)/XOR.cpp

# Retrieve previous directory from dirstack
d		:= $(dirstack_$(sp))

# Decrease the stack pointer.
# With the use of the basename we trim the extention (.x) that was appended at the start
# of the rules. So mentally decrease the stack pointer
sp		:= $(basename $(sp))

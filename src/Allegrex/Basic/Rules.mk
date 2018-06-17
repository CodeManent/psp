# Standard things
#increase stack pointer
sp				:= $(sp).x

# save previous d (dir) in stack 
dirstack_$(sp)	:= $(d)

# set d to the new dir
d				:= $(dir)

SRC := $(SRC)      \
	$(d)/ADDI.cpp  \
	$(d)/ADDIU.cpp \
	$(d)/ANDI.cpp  \
	$(d)/BEQ.cpp   \
	$(d)/BGTZ.cpp  \
	$(d)/BLEZ.cpp  \
	$(d)/BNE.cpp   \
	$(d)/J.cpp     \
	$(d)/JAL.cpp   \
	$(d)/LB.cpp    \
	$(d)/LBU.cpp   \
	$(d)/LH.cpp    \
	$(d)/LHU.cpp   \
	$(d)/LUI.cpp   \
	$(d)/LW.cpp    \
	$(d)/LWC1.cpp  \
	$(d)/LWL.cpp   \
	$(d)/LWR.cpp   \
	$(d)/ORI.cpp   \
	$(d)/SLTI.cpp  \
	$(d)/SB.cpp    \
	$(d)/SH.cpp    \
	$(d)/SW.cpp    \
	$(d)/SWL.cpp   \
	$(d)/SWR.cpp   \
	$(d)/SLTIU.cpp \
	$(d)/XORI.cpp

# Retrieve previous directory from dirstack
d		:= $(dirstack_$(sp))

# Decrease the stack pointer.
# With the use of the basename we trim the extention (.x) that was appended at the start
# of the rules. So mentally decrease the stack pointer
sp		:= $(basename $(sp))

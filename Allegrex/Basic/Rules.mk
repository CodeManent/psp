# Standard things
#increase stack pointer
sp				:= $(sp).x

# save previous d (dir) in stack 
dirstack_$(sp)	:= $(d)

# set d to the new dir
d				:= $(dir)

OBJS_$(d)	:= $(BINDIR)/$(d)/ADDI.o \
			$(BINDIR)/$(d)/ADDIU.o \
			$(BINDIR)/$(d)/ANDI.o \
			$(BINDIR)/$(d)/BEQ.o \
			$(BINDIR)/$(d)/BGTZ.o \
			$(BINDIR)/$(d)/BLEZ.o \
			$(BINDIR)/$(d)/BNE.o \
			$(BINDIR)/$(d)/J.o \
			$(BINDIR)/$(d)/JAL.o \
			$(BINDIR)/$(d)/LB.o \
			$(BINDIR)/$(d)/LBU.o \
			$(BINDIR)/$(d)/LH.o \
			$(BINDIR)/$(d)/LHU.o \
			$(BINDIR)/$(d)/LUI.o \
			$(BINDIR)/$(d)/LW.o \
			$(BINDIR)/$(d)/LWC1.o \
			$(BINDIR)/$(d)/LWL.o \
			$(BINDIR)/$(d)/LWR.o \
			$(BINDIR)/$(d)/ORI.o \
			$(BINDIR)/$(d)/SLTI.o \
			$(BINDIR)/$(d)/SB.o\
			$(BINDIR)/$(d)/SH.o\
			$(BINDIR)/$(d)/SW.o \
			$(BINDIR)/$(d)/SLTIU.o \
			$(BINDIR)/$(d)/XORI.o

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

# Standard things
#increase stack pointer
sp				:= $(sp).x

# save previous d (dir) in stack 
dirstack_$(sp)	:= $(d)

# set d to the new dir
d				:= $(dir)

OBJS_$(d)	:= $(BINDIR)/$(d)/ADDU.o \
			$(BINDIR)/$(d)/AND.o \
			$(BINDIR)/$(d)/JALR.o \
			$(BINDIR)/$(d)/JR.o \
			$(BINDIR)/$(d)/MAX.o \
			$(BINDIR)/$(d)/MIN.o \
			$(BINDIR)/$(d)/NOP.o \
			$(BINDIR)/$(d)/NOR.o \
			$(BINDIR)/$(d)/OR.o \
			$(BINDIR)/$(d)/SLL.o \
			$(BINDIR)/$(d)/SLLV.o \
			$(BINDIR)/$(d)/SLT.o \
			$(BINDIR)/$(d)/SLTU.o \
			$(BINDIR)/$(d)/SRA.o \
			$(BINDIR)/$(d)/SUBU.o \
			$(BINDIR)/$(d)/XOR.o

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

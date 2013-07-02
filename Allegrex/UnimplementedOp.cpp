#include "UnimplementedOp.h"
#include "Allegrex.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

UnimplementedOp::UnimplementedOp():Instruction(0)
{
}


UnimplementedOp::UnimplementedOp(const uint32 inst): Instruction(inst)
{
}

UnimplementedOp::~UnimplementedOp(void)
{
}

std::string UnimplementedOp::disassemble() const{
	return "_unop_";
}

void UnimplementedOp::execute(Allegrex &/*cpu*/) const{
	std::stringstream ss;

	ss << "Unimplemented instruction 0x" << std::hex << std::setw(8) << std::setfill('0') << inst;

	throw(std::logic_error(ss.str()));
}

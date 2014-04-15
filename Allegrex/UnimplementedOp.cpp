#include "UnimplementedOp.h"
#include "Allegrex.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <bitset>

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

void UnimplementedOp::execute(Allegrex & cpu) const{
	// throw a copy of the object(because the original will be 
	// deleted during the stack unwinding) for debugging and emulator
	// implmentation purposes.
	throw *this;

	// A reserved instruction is the appropriate response
	cpu.systemCoprocessor.raiseException(COP0::RI);
}

std::string UnimplementedOp::dump(const Allegrex &cpu) const{
	using namespace std;
	stringstream ss;


	ss << hex << setfill('0')
	<< "inst:     " << bitset<32>(inst)
	<< " 0x" << setw(8) << inst
	<< "\ntarget:         "
	<< bitset<26>(inst) << " " << strTarget()
	<< "\nimmedite:                 "
	<< bitset<16>(inst) << " " << strHexImmediate()
	<< "\noffset:                   "
	<< bitset<16>(inst) << " " << strOffset()

	<< "\nsa:                            "
	<< bitset<5>(inst >>6) << "       " << strSa()
	<< " = 0x" << setw(8) << cpu.GPR[u.r.sa]

	<< "\nrd:                       "
	<< bitset<5>(inst>>11) << "            " << strRd()
	<< " = 0x" << setw(8) << cpu.GPR[u.r.rd]

	<< "\nrt:                  "
	<< bitset<5>(inst>>16) << "                 " << strRt()
	<< " = 0x" << setw(8) << cpu.GPR[u.r.rt]

	<< "\nrs:             "
	<< bitset<5>(inst >> 21) << "                      " << strRs()
	<< " = 0x" << setw(8) << cpu.GPR[u.r.rd]

	<< "\nop:       "
	<< bitset<6>(inst >> 26) << "                           "
	<< "0x" << u.i.op;

	return ss.str();
}


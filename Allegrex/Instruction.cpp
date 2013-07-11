#include "Instruction.h"
#include "Allegrex.h"
#include <sstream>
#include <iomanip>

const char *Instruction::reg[] = {
	"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
	"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
	"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
	"t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
};

Instruction::Instruction(const uint32 instruction): inst(instruction), u(reinterpret_cast<const UNPACKER&>(inst))
{
}

Instruction::~Instruction(void)
{
}

/*
 * Disassembles an instruction.
 *
 * Returns a string representation of the instruction passed as parameter.
 * Uses the Allegrex decoder to get an object representing the current instruction
 * and then using the virtual method disassemble gets the actual string.
 */
std::string Instruction::disassemble(const unsigned int &inst) {
	std::unique_ptr<Instruction> i  = Allegrex::decode(inst);
	return i->disassemble();
}

/*
 * Disassembles an array of instructions.
 *
 * The output consists of two columns:
 *     - The hex representation of the current instruction.
 *     - The disassembled instruction.
 */
std::string Instruction::disassemble(const uint32 base[], size_t size) {
	using namespace std;
	std::ostringstream oss;

	for(size_t i = 0; i < size; ++i){
		oss << "0x" << hex << setw(8) << setfill('0')
		    << base[i] << "\t"
			<< disassemble(base[i]) << endl;
	}
	return oss.str();
}

/*
 * Disassembles an array of instructions.
 *
 * The output consists of three columns:
 *     - The address of the instruction (relative to the base address).
 *     - The hex representation of the instruction.
 *     - The disassembled instruction.
 */
std::string Instruction::disassemble(const uint32 base[], size_t size, const uint32 baseAddress) {
	using namespace std;
	ostringstream oss;

	for(size_t i = 0; i < size; ++i){
		oss 
			<< "0x" << hex << setw(8) << setfill('0') << (baseAddress + 4*i)
			<< "\t0x" << hex << setw(8) << setfill('0') << base[i] 
			<< "\t" <<  disassemble(base[i]) << endl;
	}
	return oss.str();
}



std::string Instruction::strRs() const{
	return reg[u.r.rs];
}

std::string Instruction::strRt() const{
	return reg[u.r.rt];
}

std::string Instruction::strRd() const{
	return reg[u.r.rd];
}

std::string Instruction::strSa() const{
	return reg[u.r.sa];
}

std::string Instruction::strTarget() const{
	std::stringstream ss;

	ss << "0x" << std::hex << std::setw(2) << u.j.target;

	return ss.str();
}

std::string Instruction::strOffset() const{
	std::stringstream ss;

    ss << static_cast<const int32>(static_cast<const int16>(u.i.immediate));

	return ss.str();
}

std::string Instruction::strSignedImmediate() const{
	return strOffset();
}

std::string Instruction::strUnsignedImmediate() const{
	std::stringstream ss;

	ss << static_cast<const uint32>(static_cast<const int32>(static_cast<int16>(u.i.immediate)));

	return ss.str();
}

std::string Instruction::strHexImmediate() const{
	std::stringstream ss;

	ss << "0x" << std::hex << std::setw(4) << std::setfill('0') << static_cast<const uint32>(u.i.immediate);

	return ss.str();
}


bool Instruction::additionOverflows(int32 lhs, int32 rhs){
//http://ptgmedia.pearsoncmg.com/images/0321335724/samplechapter/seacord_ch05.pdf
	static const int32 maxInt = 0x7FFFFFFF;
	static const int32 minInt = 0x80000000;

	if(lhs > 0 && rhs > 0){
		if(maxInt - lhs < rhs){
			return true;
		}
	}
	else if(lhs < 0 && rhs < 0){
		if(lhs < minInt  - rhs){
			return true;
		}
	}

	return false;
}

void Instruction::changePC(Allegrex& cpu, const uint32 target, const bool likely){
	if(likely)
		cpu.PC = target;
	else{
		TODO("handle the delay slot")
	}
}

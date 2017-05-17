//opcodes.java: line 315

#include "Allegrex.h"
#include "Instruction.h"
#include "Basic/Basic.h"
#include "Special/Special.h"
#include "REGIMM/REGIMM.h"
#include "COP0_INST/COP0.h"

#include "UnimplementedOp.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <memory>

using namespace std;

Allegrex::Allegrex(PSP *bus):
		BusDevice(bus),
        SGPR(reinterpret_cast<int32 *>(GPR)),
		PC(0xBFC00000),
		HI(0),
		LO(0),
		systemCoprocessor(*this, bus),
		floatingPointUnit(*this),
		vectorFloatingPointUnit(*this)
{
	GPR[sp] = 0x09F70000;
	GPR[s8] = 0x08000000;
	GPR[ra] = 0x08000000;
}

Allegrex::~Allegrex(void)
{
}

std::unique_ptr<Instruction> Allegrex::decode(const uint32 &inst) {
	std::unique_ptr<Instruction> retval;
	retval.reset(new UnimplementedOp(inst));

	//first (non static) member of union is initialized
	Instruction::UNPACKER unpacker = {inst};

	switch(unpacker.i.op){
	case opSPECIAL:
		switch(unpacker.r.func){
		case opNOP:
			if(unpacker.src == 0){
				retval.reset(new NOP());
			}
			else{
				retval.reset(new SLL(inst));
			}
			break;
		/*  0x1 reserved or unsupported */
		// TODO: Complete Special instructions
		case opSRLROR:
			switch(unpacker.r.rs){
			case 0x00: retval.reset(new SRL(inst));		break;
			case 0x01: retval.reset(new ROTR(inst));	break;
			default: /* return unimplemented op */		break;
			}
			break;
		case opSRA:		retval.reset(new SRA(inst));	break;
		case opSLLV:	retval.reset(new SLLV(inst));	break;
		/*  0x5 reserved or unsupported */
		case opSRLVROTRV:
			switch(unpacker.r.sa){
			case 0x00:	retval.reset(new SRLV(inst));	break;
			case 0x01:	retval.reset(new ROTRV(inst));	break;
			default: /* return unimplemneted op */		break;
			}
			break;
		case opSRAV:	retval.reset(new SRAV(inst));	break;
		case opJR:		retval.reset(new JR(inst));		break;
        case opJALR:	retval.reset(new JALR(inst));	break;
		case opMOVZ:	retval.reset(new MOVZ(inst));	break;
		case opMOVN:	retval.reset(new MOVN(inst));	break;
		case opSYSCALL:	retval.reset(new SYSCALL(inst));break;
		case opBREAK:	retval.reset(new BREAK(inst));	break;
		/*  0xe reserved or unsupported */
		case opSYNC: break;
		case opMFHI:	retval.reset(new MFHI(inst));	break;
		case opMTHI:	retval.reset(new MTHI(inst));	break;
		case opMFLO:	retval.reset(new MFLO(inst));	break;
		case opMTLO:	retval.reset(new MTLO(inst));	break;
		/*  0x14 reserved or unsupported */
		/*  0x15 reserved or unsupported */
		case opCLZ:		retval.reset(new CLZ(inst));	break;
		case opCLO:		retval.reset(new CLO(inst));	break;
		case opMULT:	retval.reset(new MULT(inst));	break;
		case opMULTU:	retval.reset(new MULTU(inst));	break;
		case opDIV:		retval.reset(new DIV(inst));	break;
		case opDIVU:	retval.reset(new DIVU(inst));	break;
		case opMADD:	retval.reset(new MADD(inst));	break;
		case opMADDU:	retval.reset(new MADDU(inst));	break;
		/*  0x1e reserved or unsupported */
		/*  0x1f reserved or unsupported */
		case opADD:		retval.reset(new ADD(inst));	break;
		case opADDU:	retval.reset(new ADDU(inst));	break;
		case opSUB:		retval.reset(new SUB(inst));	break;
		case opSUBU:	retval.reset(new SUBU(inst));	break;
		case opAND:		retval.reset(new AND(inst));	break;
		case opOR:		retval.reset(new OR(inst));		break;
		case opXOR:		retval.reset(new XOR(inst));	break;
		case opNOR:		retval.reset(new NOR(inst));	break;
		/*  0x28 reserved or unsupported */
		/*  0x29 reserved or unsupported */
		case opSLT:		retval.reset(new SLT(inst));	break;
		case opSLTU:	retval.reset(new SLTU(inst));	break;
		case opMAX:		retval.reset(new MAX(inst));	break;
		case opMIN:		retval.reset(new MIN(inst));	break;
		case opMSUB:	retval.reset(new MSUB(inst));	break;
		case opMSUBU:	retval.reset(new MSUBU(inst));	break;
		}
		break;
	case opREGIMM:
		switch(unpacker.r.rt){
		case opBLTZ:	retval.reset(new BLTZ(inst));	break;
		case opBGEZ:	retval.reset(new BGEZ(inst));	break;
		case opBLTZL:	retval.reset(new BLTZL(inst));	break;
		case opBGEZL:	retval.reset(new BGEZL(inst));	break;
		/* 0x05 - 0x10 reserved */
		case opBLTZAL:	retval.reset(new BLTZAL(inst));	break;
		case opBGEZAL:	retval.reset(new BGEZAL(inst));	break;
		case opBLTZALL:	retval.reset(new BLTZALL(inst));break;
		case opBGEZALL:	retval.reset(new BGEZALL(inst));break;
		default: /* return unimplemented op */		break;
		}
		break;
	case opJ:		retval.reset(new J(inst));		break;
	case opJAL:		retval.reset(new JAL(inst));	break;
	case opBEQ:		retval.reset(new BEQ(inst));	break;
	case opBNE:		retval.reset(new BNE(inst));	break;
	case opBLEZ:	retval.reset(new BLEZ(inst));	break;
	case opBGTZ:	retval.reset(new BGTZ(inst));	break;
	case opADDI:	retval.reset(new ADDI(inst));	break;
	case opADDIU:	retval.reset(new ADDIU(inst));	break;
	case opSLTI:	retval.reset(new SLTI(inst));	break;
	case opSLTIU:	retval.reset(new SLTIU(inst));	break;
	case opANDI:	retval.reset(new ANDI(inst));	break;
	case opORI:		retval.reset(new ORI(inst));	break;
	case opXORI:	retval.reset(new XORI(inst));	break;
	case opLUI:		retval.reset(new LUI(inst));	break;
	// TODO: Complete regular instructions
	case opCOP0:
		switch(unpacker.r.rs){
		case opERET:
			if(unpacker.r.func == 0x18){
				retval.reset(new ERET(inst));
			}
			break;
		default: break;
		}
		break;
	case opCOP1:
	case opVFPU2:break;
	case opBEQL:	retval.reset(new BEQL(inst));	break;
	case opBNEL:	retval.reset(new BNEL(inst));	break;
	case opBLEZL:	retval.reset(new BLEZL(inst));	break;
	case opBGTZL:	retval.reset(new BGTZL(inst));	break;
	case opVFPU0:
	case opVFPU1:
	/*  0x1a reserved or unsupported */
	case opVFPU3:
	case opSPECIAL2:
	/*  0x1d reserved or unsupported */
	/*  0x1e reserved or unsupported */
	case opSPECIAL3: break;
	case opLB:		retval.reset(new LB(inst));		break;
	case opLH:		retval.reset(new LH(inst));		break;
	case opLWL:		retval.reset(new LWL(inst));	break;
	case opLW:		retval.reset(new LW(inst));		break;
	case opLBU:		retval.reset(new LBU(inst));	break;
    case opLHU:		retval.reset(new LHU(inst));	break;
	case opLWR:		retval.reset(new LWR(inst));	break;
	/*  0x27 reserved or unsupported */
	case opSB:		retval.reset(new SB(inst));		break;
	case opSH:		retval.reset(new SH(inst));		break;
	case opSWL:		retval.reset(new SWL(inst));	break; 
	case opSW:		retval.reset(new SW(inst));		break;
	/*  0x2c reserved or unsupported */
	/*  0x2d reserved or unsupported */
	case opSWR:		retval.reset(new SWR(inst));	break;
	case opCACHE:	retval.reset(new CACHE(inst));	break;
	case opLL: break;
	case opLWC1:	retval.reset(new LWC1(inst));	break;
	case opLVS:
	/*  0x32 reserved or unsupported */
	/*  0x33 reserved or unsupported */
	case opVFPU4:
	case opULVQ:
	case opLVQ:
	case opVFPU5:
	case opSC:
	case opSWC1:
	case opSVS:
	/*  0x3b reserved or unsupported */
	case opVFPU6:
	case opUSVQ:
	case opSVQ:
	case opVFPU7:
	//default:
		break; //return retval
	}

	return retval;
}


/*
 * The execution begins from the system coprocessor.
 *
 * It is supposed to return the time took to execute what is executed.
 */
long Allegrex::step(){
	return systemCoprocessor.step();
}

void Allegrex::execute(const uint32 &inst){
	std::unique_ptr<Instruction> i = decode(inst);
	i->execute(*this);
}

/*
Allegrex::INSTRUCTION Allegrex::unpack(const uint32 inst) const
{
	INSTRUCTION result;

	result.source = inst;
	result.target = inst & 0x3FFFFFF;	// ------XXXXXXXXXXXXXXXXXXXXXXXXXX
	result.imm = inst & 0xFFFF;			// ----------------XXXXXXXXXXXXXXXX
	result.off = result.imm;			// ----------------XXXXXXXXXXXXXXXX
	result.func = inst & 0x3f;			// --------------------------XXXXXX
	result.sa = (inst >> 6) & 0x1F;		// ---------------------XXXXX------
	result.rd = (inst >> 11) & 0x1F;	// ---------------------XXXXX------
	result.rt = (inst >> 16) & 0x1F;	// -----------XXXXX----------------
	result.rs = (inst >> 21) & 0x1F;	// ------XXXXX---------------------
	result.op = (inst >> 26) & 0x3F;	// XXXXXX--------------------------
	return result;
}
*/

/*
 * Actually the system coprocessor is connected to the bus. Allegrex is just
 * the interface. So we forward every request to the system coprosessor.
 */
void Allegrex::serviceRequest(const struct Request &req){
	systemCoprocessor.serviceRequest(req);
}

Coprocessor& Allegrex::getCoprocessor(unsigned int COPnum){
	systemCoprocessor.verifyCoprocessorUsability(COPnum);
	if(COPnum > 0){
		throw std::runtime_error("Allegrex: Coprocessor not implemented yet");
	}
	return systemCoprocessor;
}

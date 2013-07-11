//opcodes.java: line 315

#include "Allegrex.h"
#include "Instruction.h"
#include "Basic/Basic.h"
#include "Special/Special.h"

#include "UnimplementedOp.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <memory>

using namespace std;

Allegrex::Allegrex(PSP *bus):
		BusDevice(bus),
        SGPR(reinterpret_cast<int32 *>(GPR)),
		PC(0xBFC00000),
		HI(0),
		LO(0),
		systemCoprocessor(*this)
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

	Instruction::UNPACKER const &unpacker = reinterpret_cast<const Instruction::UNPACKER &>(inst);

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
		TODO("complete special instructions")
		case opSRLROR:	return retval;
		case opSRA:	retval.reset(new SRA(inst));	break;
		case opSLLV:retval.reset(new SLLV(inst));	break;
		/*  0x5 reserved or unsupported */
		case opSRLRORV:
		case opSRAV:	return retval;
		case opJR:	retval.reset(new JR(inst));		break;
        case opJALR: retval.reset(new JALR(inst));  break;
		case opMOVZ:
		case opMOVN:
		case opSYSCALL:
		case opBREAK:
		/*  0xe reserved or unsupported */
		case opSYNC: break;
		case opMFHI: retval.reset(new MFHI(inst));	break;
		case opMTHI: retval.reset(new MTHI(inst));	break;
		case opMFLO: retval.reset(new MFLO(inst));	break;
		case opMTLO: retval.reset(new MTLO(inst));	break;
		/*  0x14 reserved or unsupported */
		/*  0x15 reserved or unsupported */
		case opCLZ: retval.reset(new CLZ(inst));	break;
		case opCLO: retval.reset(new CLO(inst));	break;
		case opMULT:retval.reset(new MULT(inst));	break;
		case opMULTU:
		case opDIV:
		case opDIVU:
		case opMADD:
		case opMADDU:
		/*  0x1e reserved or unsupported */
		/*  0x1f reserved or unsupported */
		case opADD:		retval.reset(new ADD(inst));	break;
		case opADDU:	retval.reset(new ADDU(inst));	break;
		case opSUB:		retval.reset(new SUB(inst));	break;
		case opSUBU:	retval.reset(new SUBU(inst));	break;
		case opAND:		retval.reset(new AND(inst));	break;
		case opOR:		retval.reset(new OR(inst));	break;
		case opXOR:		retval.reset(new XOR(inst));	break;
		case opNOR:		retval.reset(new NOR(inst));	break;
		/*  0x28 reserved or unsupported */
		/*  0x29 reserved or unsupported */
		case opSLT:		retval.reset(new SLT(inst));	break;
		case opSLTU:	retval.reset(new SLTU(inst));	break;
		case opMAX:
		case opMIN:
		case opMSUB:
		case opMSUBU:
			return retval;//unimplemented
			break;
		}
		break;
	case opREGIMM: return retval;//unimplemented
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
	TODO("complete regular instructions")
	case opCOP0:
	case opCOP1:
	case opVFPU2:
	case opBEQL:
	case opBNEL: break;
	case opBLEZL:	retval.reset(new BLEZL(inst));	break;
	case opBGTZL:
	case opVFPU0:
	case opVFPU1:
	/*  0x1a reserved or unsupported */
	case opVFPU3:
	case opSPECIAL2:
	/*  0x1d reserved or unsupported */
	/*  0x1e reserved or unsupported */
	case opSPECIAL3:
	case opLB:
	case opLH:
	case opLWL:	return retval;
	case opLW:		retval.reset(new LW(inst));		break;
	case opLBU:
    case opLHU:
	case opLWR:
	/*  0x27 reserved or unsupported */
	case opSB:
	case opSH:
	case opSWL:
	case opSW:
	/*  0x2c reserved or unsupported */
	/*  0x2d reserved or unsupported */
	case opSWR:
	case opCACHE:
	case opLL:
	case opLWC1:
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
	default:
		break; //return retval
	}

	return retval;
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

void Allegrex::serviceRequest(const struct Request &req){
	switch(req.function){
		case BusDevice::Reset:
			systemCoprocessor.reset();
			break;

		case BusDevice::Reply:
			systemCoprocessor.receiveData(req.param1);
			break;
			//systemCoprocessor.

		case BusDevice::Read:
		case BusDevice::Write:
		default:
			throw std::logic_error("Allegrex: function not recognised");
	}
}

#ifndef CACHE_H_
#define CACHE_H_
#pragma once

#include "../Instruction.h"
#include "../Allegrex.h"
#include "../COP0.h"

/***********************************************************************p. A-42
 * The 16-bit offset is sign extended and added to the contents of general
 * register base(rs) to form a virtual address. The virtual address is
 * translated to a physical address using the TLB, and the 5-bit
 * sub-opcode(rt) specifies the cache operation for that address.
 *
 * If CP0 is not usable (User of Supervisor mode) the CP0 enable bit is clear,
 * and the coprocessor unusable exception is taken. The operation of this
 * instruction on any operation/cache combination not listed below, or on a
 * secondary cache when none is present, is undefined. The operaion of this
 * instruction on uncached address is also undefined.
 */
class CACHE :
	public Instruction
{
public:
	CACHE(const uint32 inst)
	:Instruction(inst){
	}

	virtual ~CACHE(void) = default;

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "cache\t" <<  u.i.rt << ", " << strOffset() << '(' << strRs() << ')';
		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		//unpack the instruction and get the parameters
		uint32 op = u.i.rt;
		uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];

		// try to get the handle to the system coprocessor. If unusable, a
		// coprocessor unusable exception it being thrown.
		auto systemCoprocessor = dynamic_cast<COP0&>(cpu.getCoprocessor(0));
		
		// find the corresponding physical address
		bool cachable = true;
		auto pAddr = systemCoprocessor.addressTranslation(vAddr, cachable);

		if(!cachable){
			// undefined behaviour on uncached address.
			throw std::runtime_error("CACHE: cache operation on a non cachable address");
		}

		// and perform the cache operation
		cpu.systemCoprocessor.cache.CacheOp(op, vAddr, pAddr);
	}
	
};

#endif

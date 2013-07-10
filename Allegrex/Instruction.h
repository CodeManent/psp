#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#pragma once

#include "../TODO.h"
#include "../IntTypes.h"

#include <string>


class Allegrex;

class Instruction
{
	// instruction types

	// op			6-bit opperation code
	// rs			5-bit source register specifier
	// rt			5-bit target (source/destination) register or branch condition
	// immediate	16-bit immediate value, branch displacement or address dissplacement
	// target		26-bit jump target address
	// rd			5-bit destination register specifier
	// sa			5-bit shift amount
	// func			6-bit function field
/*	struct INSTRUCTION{
		union{
			unsigned int target    : 26;			// ------XXXXXXXXXXXXXXXXXXXXXXXXXX
			struct {
				union{
					unsigned int immediate : 16;	// ----------------XXXXXXXXXXXXXXXX
					unsigned int offset    : 16;	// ----------------XXXXXXXXXXXXXXXX
					struct{
						unsigned int func      : 6;	// --------------------------XXXXXX
						unsigned int sa        : 5;	// ---------------------XXXXX------
						unsigned int rd        : 5;	// ----------------XXXXX-----------
					};
				};
				unsigned int rt        : 5;			// -----------XXXXX----------------
				unsigned int rs        : 5;			// ------XXXXX---------------------
			};
		};

		unsigned int op        : 6;					// XXXXXX--------------------------
	} ;


	struct INSTRUCTION{
        uint32 source;
        uint32 target;          // ------XXXXXXXXXXXXXXXXXXXXXXXXXX
        uint16 imm;             // ----------------XXXXXXXXXXXXXXXX
        uint16 off;         	// ----------------XXXXXXXXXXXXXXXX
        uint8 func;         	// --------------------------XXXXXX
        uint8 sa;				// ---------------------XXXXX------
        uint8 rd;				// ----------------XXXXX-----------
        uint8 rt;				// -----------XXXXX----------------
        uint8 rs;				// ------XXXXX---------------------
        uint8 op;				// XXXXXX--------------------------
	};
*/
										// |------------32 bit------------|
										// 32-----------------------------0
	// immediate type
	struct I_TYPE_INSTRUCTION {			// op     rs    rt   immediate
		unsigned int immediate : 16;	// ----------------XXXXXXXXXXXXXXXX
		unsigned int rt        : 5;		// -----------XXXXX----------------
		unsigned int rs        : 5;		// ------XXXXX---------------------
		unsigned int op        : 6;		// XXXXXX--------------------------
	};

	// jump type
	struct J_TYPE_INSTRUCTION {			// op    target
		unsigned int target    : 26;	// ------XXXXXXXXXXXXXXXXXXXXXXXXXX
		unsigned int op        : 6;		// XXXXXX--------------------------
	};

	// register type
	struct R_TYPE_INSTRUCTION {			// op    rs   rt   rd   sa   func
		unsigned int func      : 6;		// --------------------------XXXXXX
		unsigned int sa        : 5;		// ---------------------XXXXX------
		unsigned int rd        : 5;		// ----------------XXXXX-----------
		unsigned int rt        : 5;		// -----------XXXXX----------------
		unsigned int rs        : 5;		// ------XXXXX---------------------
		unsigned int op        : 6;		// XXXXXX--------------------------
	};

	// instruction types used in COP1 (floating point)

										// |------------32 bit------------|
										// 32-----------------------------0
	// immediate type
	struct FI_TYPE_INSTRUCTION {		// op     rs    rt   offset
		unsigned int offset		: 16;	// ----------------XXXXXXXXXXXXXXXX
		unsigned int ft			: 5;	// -----------XXXXX----------------
		unsigned int base		: 5;	// ------XXXXX---------------------
		unsigned int op			: 6;	// XXXXXX--------------------------
	};

	// register type
	struct FR_TYPE_INSTRUCTION {		// op    fmt  ft   fs   fd   func
		unsigned int func		: 6;	// --------------------------XXXXXX
		unsigned int fd			: 5;	// ---------------------XXXXX------
		unsigned int fs			: 5;	// ----------------XXXXX-----------
		unsigned int ft			: 5;	// -----------XXXXX----------------
		unsigned int fmt		: 5;	// ------XXXXX---------------------
		unsigned int COP1		: 6;	// XXXXXX--------------------------
	};
	

public:
	union UNPACKER{
		uint32 src;
		I_TYPE_INSTRUCTION i;
		J_TYPE_INSTRUCTION j;
		R_TYPE_INSTRUCTION r;
	};

protected:
	static const char *reg[];

	const uint32 inst;
    const UNPACKER &u;
public:
	Instruction(const uint32 instruction);
	virtual ~Instruction(void);

	virtual std::string disassemble() const = 0;
	static std::string disassemble(const uint32 &inst);
	static std::string disassemble(const uint32 base[], size_t count);
	static std::string disassemble(const uint32 base[], size_t count, const uint32 baseAddress);


	virtual void execute(Allegrex &cpu) const = 0;

	std::string strRs() const;
	std::string strRt()const;
	std::string strRd() const;
	std::string strSa() const;
	std::string strTarget() const;
	std::string strOffset() const;
	std::string strSignedImmediate() const;
	std::string strUnsignedImmediate() const;
	std::string strHexImmediate() const;
	static bool additionOverflows(int32 a, int32 b);

	/*
	 * Returns the 32bit value after sign-extending the 16-bit immediate.
	 * Should be equivalent to:
	 * (immediate_15)^16 || immediate15...0
	 */
	static inline uint32 signExtend(const unsigned int immediate){
		return static_cast<const int32>(static_cast<const int16>(immediate));
	}
};

#endif

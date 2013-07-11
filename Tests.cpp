#include "Tests.h"

#include "Allegrex/Allegrex.h"
#include "Allegrex/Instruction.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

vector<char> readFile(const char*const path){
	ifstream infile;
	infile.open(path, ios::binary);

	if(!infile.is_open()){
		throw("Couldn't open file");
	}

	//get filesize
	infile.seekg(0, ios::end);
    int length = infile.tellg();
	infile.seekg(0, ios::beg);

    //char *buffer = new char[length];

    vector<char> buffer(length);

    infile.read(&buffer[0], length);
	
	infile.close();

	return buffer;
}

/*
 * Loads te IPL from the corresponding file, disassembles it and dumps it to 
 * the console.
 */
bool testDisassemble(){
    vector<char> ipl(readFile("../Data/msipl.bin"));
	cout << Instruction::disassemble((const uint32 *)(&ipl[0]), ipl.size()*sizeof(char)/sizeof(uint32), 0xBFD00000) << endl;
	return true;
}

bool testUnpacker(){
	uint32 inst = 0xdeadface;
	size_t unpackerSize = sizeof(Instruction::UNPACKER);
	//std::cout << "sizeof(Instruction::UNPACKER) = " << unpackerSize << endl;
	if(unpackerSize != sizeof(uint32)){
		return false;
	}

	Instruction::UNPACKER &inst2= reinterpret_cast<Instruction::UNPACKER &>(inst);

	if(inst2.i.op != inst2.j.op){
		return false;
	}

	return true;
}

bool testAdditionOverflow(){
	int32 a = 0x80000000;
	int32 b = -1;

	bool overflow = Instruction::additionOverflows(a, b);

	return overflow;
}

#include "Allegrex/Basic/LW.h"
#include "PSP.h"
#include "MainMemory.h"

/*
 * Tests if we can load a value from the main memory;
 *
 * We put a value in the main memory, construct a load instruction and after
 * executing it, we check the register for the test value
 */
bool testLoadMemory()
{
	//The test value 
	uint32 testVal = 0x51DEB00B;
	uint32 testAddr = 0x000000A0;
	PSP testPsp;

	//put the test value in the main memory
	MainMemory* memory = testPsp.getMainMemory();
	memory->write(testAddr, testVal);

	// Setup an "LW a0, at" instruction
	Instruction::UNPACKER inst;
	inst.i.op = Allegrex::opLW;
	inst.i.immediate = 0;
	inst.i.rs = Allegrex::a0;
	inst.i.rt = Allegrex::at;

	//get a reference to the cpu
	Allegrex *cpu = testPsp.getCPU();
	//set the address to the appropriate register
	cpu->GPR[Allegrex::a0] = testAddr;

	//execute teh load instruction
	cpu->execute(inst.src);
	
	//get the value shd print it
	//uint32 regVal = cpu->GPR[Allegrex::at];
	//std::cout << std::hex <<  "regVal = 0x" << regVal << "\ttestVal = 0x" << testVal << endl;

	//and check and return if we loaded the value successfully

	return (cpu->GPR[Allegrex::at] == testVal);
}

bool runTests(){
	bool testResults = true;

#define addTest(x) std::make_pair(#x, x)
	std::vector<std::pair<std::string, bool (*)()>> tests = {
		addTest(testAdditionOverflow),
		addTest(testUnpacker),
//		addTest(testDisassemble),
		addTest(testLoadMemory)
	};

	try{
		for(auto t : tests)
		{
			std::cout << "Running " << t.first;
			bool result =  (t.second)();
			std::cout << "\t\t" << (result? "Succeded" : "Failed") << std::endl;
			testResults &= result;
		}

	}
	catch(const char *msg){
		cerr << msg << endl;
		return false;
	}

	return testResults;
}

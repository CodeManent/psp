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

bool testDisassemble(){
/*
	//Allegrex cpu;


    vector<char> ipl(readFile("../Data/msipl.bin"));
	//cout << Allegrex::disassemble((const uint32*)(&ipl[0]), ipl.size()*sizeof(char)/sizeof(uint32), 0xBFD00000) << endl;

	cout << cpu.disassemble((const uint32 *)(&ipl[0]), ipl.size()*sizeof(char)/sizeof(uint32), 0xBFD00000) << endl;
//*/
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


bool runTests(){
	bool testResults = true;

	try{
		testResults &= testAdditionOverflow();
		testResults &= testUnpacker();
		testResults &= testDisassemble();
	}
	catch(const char *msg){
		cerr << msg << endl;
		return false;
	}

	return testResults;
}

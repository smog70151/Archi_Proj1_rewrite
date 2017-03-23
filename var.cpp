#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//output file
fstream snapshot;    // snapshot.rpt
fstream error_dump;  // error_dump.rpt

//input file
fstream iimage;      // read iimage
fstream dimage;      // read dimage

//reg part
Register reg[32];
Register HI, LO, PC;

//Instruction and Data memory storage
unsigned int inst_mem[256]; //iimage max 1KB
unsigned int data_mem[1024]; //dimage max 1KB

//cyc
int cyc;

//Decode var
unsigned int address; //26 bits
unsigned int immediate; //16 bits
unsigned int opcode, funct; //6 bits
unsigned int rt, rs, rd, shamt; //5 bits

//Reg var
//data1 = rs, data2 = rt
unsigned int read_data1, read_data2; //to calculate
int simmediate; //signed immediate 16 -> 32

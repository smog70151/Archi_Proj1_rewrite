#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//output file
extern fstream snapshot;    // snapshot.rpt
extern fstream error_dump;  // error_dump.rpt

//input file
extern fstream iimage;      // read iimage
extern fstream dimage;      // read dimage

//reg part
typedef struct REG {
    int pre;
    int cur;
} Register;

extern Register reg[32];
extern Register HI, LO, PC;

//Instruction and Data memory storage
extern unsigned int inst_mem[1024]; //iimage max 1KB
extern unsigned int data_mem[1024]; //dimage max 1KB

//cyc
extern int cyc;

//Decode var
extern unsigned int address; //26 bits
extern unsigned int immediate; //16 bits
extern unsigned int opcode, funct; //6 bits
extern unsigned int rt, rs, rd, shamt; //5 bits

//Reg var
//data1 = rs, data2 = rt
extern int read_data1, read_data2; //to calculate
extern int simmediate; //signed immediate 16 -> 32
beq

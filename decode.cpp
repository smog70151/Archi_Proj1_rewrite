#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
// to include the var
#include "var.h"

using namespace std;

void Decode(unsigned int inst)
{
    /* Decode instruction */

    address = inst%(1<<26); //address : 26-bits
    immediate = inst%(1<<16); //immediate : 16-bits
    opcode = inst>>26; //opcode : 6-bits
    funct = inst%(1<<6); //funct : 6-bits
    rt = (inst>>16)%(1<<5); //rt : 5-bits
    rs = (inst>>21)%(1<<5); //rs : 5-bits
    rd = (inst>>11)%(1<<5); //rd : 5-bits
    shamt = (inst>>6)%(1<<5); //shamt : 5-bits

}

void PC_ALU()
{
    PC.cur = PC.cur + 4;
}

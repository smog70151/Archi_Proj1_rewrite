#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
// to include the var
#include "var.h"

using namespace std;

void Signed();

// Read the data from register
void Read_Reg()
{
    /* Read the register */

    read_data1 = reg[rs].cur;
    read_data2 = reg[rt].cur;

    /* immediate 16 -> 32 signed*/
    Signed();

}

void Signed()
{
    if(immediate&0x00008000)
        simmediate = immediate | 0xffff0000;
    else
        simmediate = immediate & 0x0000ffff;
}

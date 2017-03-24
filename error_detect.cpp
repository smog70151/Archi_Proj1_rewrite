#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
// to include the var
#include "var.h"

using namespace std;

//detect Register[0]
void Error_R0()
{
    reg[0].cur = 0; // reset the Register[0]
    switch(opcode)
    {
    case 0x00 :
        if( rd==0 )
            error_dump <<  "In cycle " << dec << cyc << ": Write $0 Error" << endl;
    break;
    default :
        if( rd==0 )
            error_dump <<  "In cycle " << dec << cyc << ": Write $0 Error" << endl;
    break;
    }
}

//detect addition OVF
void Error_OVF()
{
    switch( opcode )
    {
    /*R-type Instruction OVF detect*/
    case 0x00 :
        switch( funct )
        {
        case 0x20 : //add
            if( read_data1 >= 0 && read_data2 >= 0 && (read_data1+read_data2) < 0 )
                error_dump << "In cycle " << dec << cyc << ": Number Overflow" << endl;
            if( read_data1 < 0 && read_data2 < 0 && (read_data1+read_data2) >= 0 )
                error_dump << "In cycle " << dec << cyc << ": Number Overflow" << endl;
        break;
        case 0x22 : //sub
            if( read_data1 >=0 && (~read_data2+1) >= 0 && (read_data1-read_data2) < 0 )
                error_dump << "In cycle " << dec << cyc << ": Number Overflow" << endl;
            if( read_data1 < 0 && (~read_data2+1) < 0 && (read_data1-read_data2) >= 0)
                error_dump << "In cycle " << dec << cyc << ": Number Overflow" << endl;
        break;
        default :
        break;
        }
    break;

    /*I-type Instruction OVF detect*/
    case 0x08 : //addi
	case 0x23 : //lw
	case 0x21 : //lh
	case 0x25 : //lhu
	case 0x20 : //lb
	case 0x24 : //lbu
	case 0x2b : //sw
	case 0x29 : //sh
	case 0x28 : //sb
	    if( read_data1 >= 0 && simmediate >= 0 && (read_data1+simmediate) < 0 )
            error_dump << "In cycle " << dec << cyc << ": Number Overflow" << endl;
        if( read_data1 < 0 && simmediate < 0 && (read_data1+simmediate) >= 0 )
            error_dump << "In cycle " << dec << cyc << ": Number Overflow" << endl;
    break;

    /*I-type Instruction OVF detect (PC+4+4*simmediate)*/
    case 0x04 : //beq
	case 0x05 : //bne
	case 0x07 : //bgtz
    break;

    /*Default part*/
    default :
    break;
    }
}

//detect HI, LO OVW
void Error_OVW()
{
    if( flag_OVW == false )
        error_dump << "In cycle " << dec << cyc << ": Overwrite HI-LO registers" << endl;
    flag_OVW = false;
}

//detect D-memory boundary
void Error_Dmem(int addr)
{
    switch(opcode)
    {

    /* word */
    case 0x23 : //lw
    case 0x2b : //sw
        if( 0 > addr || addr > 1020 )
        {
            error_dump <<  "In cycle " << dec << cyc << ": Address Overflow" << endl;
            error_halt = 1 ; //Switch the Error Flag
        }
    break;

    /* half word */
	case 0x21 : //lh
	case 0x25 : //lhu
    case 0x29 : //sh
        if( 0 > addr || addr > 1022 )
        {
            error_dump <<  "In cycle " << dec << cyc << ": Address Overflow" << endl;
            error_halt = 1 ; //Switch the Error Flag
        }
    break;

    /* byte */
	case 0x20 : //lb
	case 0x24 : //lbu
	case 0x28 : //sb
	    if( 0 > addr || addr > 1023 )
        {
            error_dump <<  "In cycle " << dec << cyc << ": Address Overflow" << endl;
            error_halt = 1 ; //Switch the Error Flag
        }
    break;
    }
}

//detect D-memory misaligned
void Error_Misaligned(int addr)
{
    switch(opcode)
    {

    /* word */
    case 0x23 : //lw
    case 0x2b : //sw
        if( addr % 4 != 0 )
        {
            error_dump <<  "In cycle " << dec << cyc << ": Misalignment Error" << endl;
            error_halt = 1 ; //Switch the Error Flag
        }
    break;

    /* half word */
	case 0x21 : //lh
	case 0x25 : //lhu
    case 0x29 : //sh
        if( addr % 2 != 0 )
        {
            error_dump <<  "In cycle " << dec << cyc << ": Misalignment Error" << endl;
            error_halt = 1 ; //Switch the Error Flag
        }
    break;

    /* byte */
	case 0x20 : //lb
	case 0x24 : //lbu
	case 0x28 : //sb
    break;
    }
}

//detect instructions ( mfhi and mflo )
void Flag_OVW()
{
    flag_OVW = true;
}

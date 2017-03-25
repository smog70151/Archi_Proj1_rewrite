#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
// to include the var
#include "var.h"
// to decode the instruction
#include "decode.h"
// to load the register data
#include "register.h"
// to implement the instruction
#include "alu.h"
// to detect the error
#include "error_detect.h"

using namespace std;

//Init in the beginning
void init();
//trans bytes to word
unsigned int c2i_inst_data(unsigned int inst, int pow,unsigned char value);
//read data
void read_iimage();
void read_dimage();
//Snapshot
void Snapshot();


int main()
{
    unsigned int addr;
    //Init var
    init();
    //read *.bin
    read_iimage();
    read_dimage();

    //simulation part
    while(1)
    {
        if(error_halt==1) break; //error detect 1.halt 2.error
        Snapshot();
        if(cyc==500001 || PC.cur > 1023) break; //cyc > 500,000
        cyc++; //cycle ++;
        addr = PC.cur/4 ; //load instruction memory
        PC_ALU(); //PC = PC+4 -> next instruction
        Decode(inst_mem[addr]); //Decode current instruction
        Read_Reg(); //Read the red data and signed immediate( simmediate )
        ALU(); //Implement the instruction meaning
    }

    //close *.rpt
    snapshot.close();
    error_dump.close();
    return 0;
}

void init()
{
    //Init i-part and d-part mem
    for(int i=0; i<256; i++)
        data_mem[i] = 0;
    for(int i=0; i<1024; i++)
        data_mem[i] = 0;
    //Init HI, LO, PC ;
    HI.pre = LO.pre = PC.pre = 0;
    HI.cur = LO.cur = PC.cur = 0;
    //Init Register
    for(int i=0; i<32; i++)
        reg[i].cur = reg[i].pre = 0;
    //Init cyc
    cyc = 0;
    //Init Error halt detect
    error_halt = 0;
    flag_OVW = true; // true -> correct

    snapshot.open("snapshot.rpt",ios::out);
    error_dump.open("error_dump.rpt",ios::out);
}

void read_iimage()
{
    iimage.open("iimage.bin",ios::in|ios::binary);
    unsigned char c;
    unsigned int inst, count, temp;

    //Init PC addr (iimage_0)
    for(int i=0; i<4; i++)
    {
        if(i==0) inst = 0;
        iimage.read((char*)&c,sizeof(char));
        inst=c2i_inst_data(inst,4-i,c);
    }
    PC.cur = inst; // write into pc

    // numbers of instruction
    for(int i=0; i<4; i++)
    {
        if(i==0) inst = 0;
        iimage.read((char*)&c,sizeof(char));
        inst=c2i_inst_data(inst,4-i,c);
    }
    temp = count = inst; // following steps

    // instruction part
    while(temp)
    {
        //read the instruction part of the iimage file
        for(int i=0; i<4; i++)
        {
            if(i==0) inst = 0;
            iimage.read((char*)&c,sizeof(char));
            inst=c2i_inst_data(inst,4-i,c);
        }

        //store inst
        unsigned int addr = PC.cur/4 + count - temp ;
        if(addr>255)
        {
            cout << "illegal testcase" << endl;
            error_halt = 1;
            break;
        }
        inst_mem[addr]=inst;

        temp--;
    }
    iimage.clear();

}

void read_dimage()
{
    dimage.open("dimage.bin",ios::in|ios::binary);
    unsigned char c;
    unsigned int data, count, temp;

    //read $sp in the file (dimage_0)
    for(int i=0; i<4; i++)
    {
        if(i==0) data = 0;
        dimage.read((char*)&c,sizeof(char));
        data=c2i_inst_data(data,4-i,c);
    }
    //store the reg[29]($sp) data
    reg[29].cur=data;

    // numbers of data
    for(int i=0; i<4; i++)
    {
        if(i==0) data = 0;
        dimage.read((char*)&c,sizeof(char));
        data=c2i_inst_data(data,4-i,c);
    }
    temp = count = data; // following data

    while(temp)
    {
        //read the rest part of the dimage file
		for(int i=0; i<4; i++)
		{
			if(i==0) data = 0;
			dimage.read((char*)&c,sizeof(char));
			data=c2i_inst_data(data,4-i,c);
		}

		//store mem
		unsigned int addr = 4*(count - temp);
		if(addr+3>1023)
        {
            cout << "illegal testcase" << endl;
            error_halt = 1;
            break;
        }
		data_mem[addr]   = (data&0xff000000)>>24;
		data_mem[addr+1] = (data&0x00ff0000)>>16;
		data_mem[addr+2] = (data&0x0000ff00)>>8 ;
		data_mem[addr+3] = (data&0x000000ff)    ;

		temp--;
    }
    dimage.close();

}
unsigned int c2i_inst_data(unsigned int inst, int pow,unsigned char value)
{
    if(pow==4)
        inst=(value>>4<<28)+((value%16)<<24);
    else if(pow==3)
        inst+=(value>>4<<20)+((value%16)<<16);
    else if(pow==2)
        inst+=(value>>4<<12)+((value%16)<<8);
    else if(pow==1)
        inst+=(value>>4<<4)+value%16;
    return inst;
}

void Snapshot()
{
    snapshot << "cycle " << dec << cyc << endl;
    //cout << "cyc : " << dec << cyc << endl;
    if(cyc==0)
    {
        //1st cyc snapshot  reg -> HI -> LO -> PC
        for(int i = 0; i<32 ; i++)
            snapshot << "$" << setw(2) << setfill('0') << dec << i << ": 0x" << setw(8) << setfill('0') << hex << uppercase << reg[i].cur << endl;
        snapshot << "$HI: 0x" << setw(8) << setfill('0') << hex << uppercase << HI.cur << endl;
        snapshot << "$LO: 0x" << setw(8) << setfill('0') << hex << uppercase << LO.cur << endl;
        snapshot << "PC: 0x" << setw(8) << setfill('0') << hex << uppercase << PC.cur << endl;
    }
    else
    {
        //snapshot the altered reg
        for(int i = 0; i<32; i++)
            if(reg[i].pre != reg[i].cur)
                snapshot << "$" << setw(2) << setfill('0') << dec << i << ": 0x" << setw(8) << setfill('0') << hex << uppercase << reg[i].cur << endl;
        if(HI.pre!=HI.cur)
            snapshot << "$HI: 0x" << setw(8) << setfill('0') << hex << uppercase << HI.cur << endl;
        if(LO.pre!=LO.cur)
            snapshot << "$LO: 0x" << setw(8) << setfill('0') << hex << uppercase << LO.cur << endl;
        if(PC.pre!=PC.cur)
            snapshot << "PC: 0x" << setw(8) << setfill('0') << hex << uppercase << PC.cur << endl;
    }
    snapshot << endl << endl;
    for(int i = 0; i<32 ; i++)
        reg[i].pre = reg[i].cur;
    HI.pre = HI.cur;
    LO.pre = LO.cur;
    PC.pre = PC.cur;
}

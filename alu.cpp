#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
// to include the var
#include "var.h"
// to detect the error
#include "error_detect.h"

using namespace std;

/* R-Type Instructions */ //17
//No shamt
void R_add();
void R_addu();
void R_sub();
void R_and();
void R_or();
void R_xor();
void R_nor();
void R_nand();
void R_slt();
//No rs
void R_sll();
void R_srl();
void R_sra();
//Only rs
void R_jr();
//rs and rt
void R_mult();
void R_multu();
//Only rd
void R_mfhi();
void R_mflo();
/* R-Type Instructions */

/* I-Type Instructions */ //18
void I_addi();
void I_addiu();
void I_lw();
void I_lh();
void I_lhu();
void I_lb();
void I_lbu();
void I_sw();
void I_sh();
void I_sb();
void I_lui();
void I_andi();
void I_ori();
void I_nori();
void I_slti();
void I_beq();
void I_bne();
void I_bgtz();
/* I-Type Instructions */

/* J-Type Instructions */
void J_j();
void J_jal();
/* J-Type Instructions */

/* S-Type Instructions */
void halt();
/* S-Type Instructions */

//implement the meaning of the instruction
void ALU()
{
    switch(opcode)
    {
    case 0x00 :
        switch(funct)
        {
        case 0x20 : //add $d,$s,$t
            R_add();
        break;
        case 0x21 : //addu $d,$s,$t
            R_addu();
        break;
        case 0x22 : //sub $d,$s,$t
            R_sub();
        break;
        case 0x24 : //and $d,$s,$t
            R_and();
        break;
        case 0x25 : //or $d,$s,$t
            R_or();
        break;
        case 0x26 : //xor $d,$s,$t
            R_xor();
        break;
        case 0x27 : //nor $d,$s,$t
            R_nor();
        break;
        case 0x28 : //nand $d,$s,$t
            R_nand();
        break;
        case 0x2a : //slt $d,$s,$t
            R_slt();
        break;
        case 0x00 : //sll $d,$t,C
            R_sll();
        break;
        case 0x02 : //srl $d,$t,C
            R_srl();
        break;
        case 0x03 : //sra $d,$t,C
            R_sra();
        break;
        case 0x08 : //jr $s
            R_jr();
        break;
        case 0x18 : //mult $s $t
            R_mult();
        break;
        case 0x19 : //multu $s $t
            R_multu();
        break;
        case 0x10 : //mfhi $d
            R_mfhi();
        break;
        case 0x12 : //mflo $d
            R_mflo();
        break;
        default :
            cout << "illegal instruction found at 0xaddress" ;
            system("pause");
        break;
        }
    break;
    case 0x08 : //addi $t,$s,C
        I_addi();
    break;
    case 0x09 : //addiu $t,$s,C
        I_addiu();
    break;
    case 0x23 : //lw $t,C($s)
        I_lw();
    break;
    case 0x21 : //lh $t,C($s)
        I_lh();
    break;
    case 0x25 : //lhu $t,C($s)
        I_lhu();
    break;
    case 0x20 : //lb $t,C($s)
        I_lb();
    break;
    case 0x24 : //lbu $t,C($s)
        I_lbu();
    break;
    case 0x2b : //sw $t,C($s)
        I_sw();
    break;
    case 0x29 : //sh $t,C($s)
        I_sh();
    break;
    case 0x28 : //sb $t,C($s)
        I_sb();
    break;
    case 0x0f : //lui $t,C
        I_lui();
    break;
    case 0x0c : //andi $t,C
        I_andi();
    break;
    case 0x0d : //ori $t,C
        I_ori();
    break;
    case 0x0e : //nori $t,C
        I_nori();
    break;
    case 0x0a : //slti $t,C
        I_slti();
    break;
    case 0x04 : //beq $s,$t,C
        I_beq();
    break;
    case 0x05 : //bne $s,$t,C
        I_bne();
    break;
    case 0x07 : //bgtz $s,$t,C
        I_bgtz();
    break;
    case 0x02 : //j C
        J_j();
    break;
    case 0x03 : //jal C
        J_jal();
    break;
    case 0x3f : //halt
    break;
    default :
        cout << "illegal instruction found at 0xaddress" ;
        system("pause");
    break;
    }
}

/* R-Type instructions */
/* No shamt */
void R_add()
{
    //$d = $s + $t
    reg[rd].cur = read_data1 + read_data2;
    Error_R0(); //detect Write Register[0]
    Error_OVF(); //detect Adder OVF
}
void R_addu()
{
    //$d = $s + $t(unsigned, no overflow exception)
    reg[rd].cur = read_data1 + read_data2;
    Error_R0(); //detect Write Register[0]
}
void R_sub()
{
    //$d = $s - $t
    reg[rd].cur = read_data1 - read_data2;
    Error_R0(); //detect Write Register[0]
    Error_OVF(); //detect Adder OVF
}
void R_and()
{
    //$d = $s & $t
    reg[rd].cur = read_data1 & read_data2;
    Error_R0(); //detect Write Register[0]
}
void R_or()
{
    //$d = $s | $t
    reg[rd].cur = read_data1 | read_data2;
    Error_R0(); //detect Write Register[0]
}
void R_xor()
{
    //$d = $s ^ $t
    reg[rd].cur = read_data1 ^ read_data2;
    Error_R0(); //detect Write Register[0]
}
void R_nor()
{
    //$d = ~ ($s | $t)
    reg[rd].cur = ~(read_data1 | read_data2);
    Error_R0(); //detect Write Register[0]
}
void R_nand()
{
    //$d = ~($s & $t)
    reg[rd].cur = ~(read_data1 & read_data2);
    Error_R0(); //detect Write Register[0]
}
void R_slt()
{
    //$d = ($s < $t), signed comparison
    reg[rd].cur = read_data1 < read_data2;
    Error_R0(); //detect Write Register[0]
}

/* No rs */
void R_sll()
{
    //$d = $t << C
    reg[rd].cur = read_data2 << shamt;
    if( rt != 0 || rd !=0 || shamt !=0 )
        Error_R0(); //detect Write Register[0]
}
void R_srl()
{
    //$d = $t >> C
    reg[rd].cur = read_data2 >> shamt;
    Error_R0(); //detect Write Register[0]
}
void R_sra()
{
    //$d = $t >> C, with sign bit shifted in
    if(read_data2 & 0x80000000)
        reg[rd].cur = (0xffffffff00000000 | (unsigned long long ) read_data2) >> shamt;
    else
        reg[rd].cur = read_data2 >> shamt;
    Error_R0(); //detect Write Register[0]
}

/* Only rs */
void R_jr()
{
    //PC=$s
    PC.cur = read_data1;
}

/* rs and rt */
void R_mult()
{
    //{Hi || Lo} = $s * $t
    unsigned long long temp_rs, temp_rt;
    /* Extension signed rs, rt */
    if(read_data1 &0x80000000)
        temp_rs = read_data1 | 0xffffffff00000000;
    else
        temp_rs = read_data1 & 0x00000000ffffffff;
    if(read_data2 &0x80000000)
        temp_rt = read_data2 | 0xffffffff00000000;
    else
        temp_rt = read_data2 & 0x00000000ffffffff;
    HI.cur = (temp_rs*temp_rt) >> 32;
    LO.cur = (temp_rs*temp_rt) & 0x00000000ffffffff;
    Error_OVW(); //detect OVW HI, LO
}
void R_multu()
{
    //{Hi || Lo} = $s * $t (unsigned, no overflow exception)
    unsigned long long temp_rs, temp_rt;
    /* Extension rs, rt */
    temp_rs = read_data1 & 0x00000000ffffffff;
    temp_rt = read_data2 & 0x00000000ffffffff;

    HI.cur = (temp_rs*temp_rt) >> 32;
    LO.cur = (temp_rs*temp_rt) & 0x00000000ffffffff;
    Error_OVW(); //detect OVW HI, LO
}

/* Only rd */
void R_mfhi()
{
    //$d = Hi
    reg[rd].cur = HI.cur;
    Error_R0(); //detect Write Register[0]
    Flag_OVW(); //Flag to detect OVW
}
void R_mflo()
{
    //$d = Lo
    reg[rd].cur = LO.cur;
    Error_R0(); //detect Write Register[0]
    Flag_OVW(); //Flag to detect OVW
}

/* R-Type instructions */

/* I-Type Instructions */ //18
void I_addi()
{
    //$t = $s + C(signed)
    reg[rt].cur = read_data1 + simmediate;
    Error_R0(); //detect Write Register[0]
    Error_OVF(); //detect Adder OVF
}
void I_addiu()
{
    //$t = $s + C(unsigned, no overflow exception)
    reg[rt].cur = read_data1 + simmediate;
    Error_R0(); //detect Write Register[0]
}
void I_lw()
{
    //$t = 4 bytes from Memory[$s + C(signed)]
    int addr;
    addr = read_data1 + simmediate;
    if(0<=addr&&addr<=1020)
        reg[rt].cur = (data_mem[addr  ] << 24)
                    + (data_mem[addr+1] << 16)
                    + (data_mem[addr+2] <<  8)
                    + (data_mem[addr+3]      );
    Error_R0(); //detect Write Register[0]
    Error_OVF(); //detect Adder OVF
    Error_Dmem(addr); //detect D Memory OVF
    Error_Misaligned(addr); //detect S/L Wrong Memory

}
void I_lh()
{
    //$t = 2 bytes from Memory[$s + C(signed)], signed
    int addr;
    addr = read_data1 + simmediate;
    if(0<=addr&&addr<=1022)
    {
        reg[rt].cur = (data_mem[addr  ] << 8)
                    + (data_mem[addr+1]     );
        if( reg[rt].cur & 0x00008000 )
            reg[rt].cur = reg[rt].cur | 0xffff8000;
    }
    Error_R0(); //detect Write Register[0]
    Error_OVF(); //detect Adder OVF
    Error_Dmem(addr); //detect D Memory OVF
    Error_Misaligned(addr); //detect S/L Wrong Memory
}
void I_lhu()
{
    //$t = 2 bytes from Memory[$s + C(signed)], unsigned
    int addr;
    addr = read_data1 + simmediate;
    if(0<=addr&&addr<=1022)
        reg[rt].cur = (data_mem[addr  ] << 8)
                    + (data_mem[addr+1]     );
    Error_R0(); //detect Write Register[0]
    Error_OVF(); //detect Adder OVF
    Error_Dmem(addr); //detect D Memory OVF
    Error_Misaligned(addr); //detect S/L Wrong Memory
}
void I_lb()
{
    //$t = Memory[$s + C(signed)], signed
    int addr;
    addr = read_data1 + simmediate;
    if(0<=addr&&addr<=1023)
    {
        reg[rt].cur = data_mem[addr];
        if( reg[rt].cur & 0x00000080 )
            reg[rt].cur = reg[rt].cur | 0xffffff00;
    }
    Error_R0(); //detect Write Register[0]
    Error_OVF(); //detect Adder OVF
    Error_Dmem(addr); //detect D Memory OVF
    Error_Misaligned(addr); //detect S/L Wrong Memory
}
void I_lbu()
{
    //$t = Memory[$s + C(signed)], unsigned
    int addr;
    addr = read_data1 + simmediate;
    if(0<=addr&&addr<=1023)
        reg[rt].cur = data_mem[addr];
    Error_R0(); //detect Write Register[0]
    Error_OVF(); //detect Adder OVF
    Error_Dmem(addr); //detect D Memory OVF
    Error_Misaligned(addr); //detect S/L Wrong Memory
}
void I_sw()
{
    //4 bytes from Memory[$s + C(signed)] = $t
    int addr;
    addr = read_data1 + simmediate;
    if(0<=addr&&addr<=1020)
    {
        data_mem[addr  ] = (reg[rt].cur >> 24) && 0x000000ff;
        data_mem[addr+1] = (reg[rt].cur >> 16) && 0x000000ff;
        data_mem[addr+2] = (reg[rt].cur >>  8) && 0x000000ff;
        data_mem[addr+3] = (reg[rt].cur      ) && 0x000000ff;
    }
    Error_OVF(); //detect Adder OVF
    Error_Dmem(addr); //detect D Memory OVF
    Error_Misaligned(addr); //detect S/L Wrong Memory
}
void I_sh()
{
    //2 bytes from Memory[$s + C(signed)] = $t & 0x0000FFFF
    int addr;
    addr = read_data1 + simmediate;
    if(0<=addr&&addr<=1022)
    {
        data_mem[addr  ] = (reg[rt].cur >>  8) && 0x000000ff;
        data_mem[addr+1] = (reg[rt].cur      ) && 0x000000ff;
    }
    Error_OVF(); //detect Adder OVF
    Error_Dmem(addr); //detect D Memory OVF
    Error_Misaligned(addr); //detect S/L Wrong Memory
}
void I_sb()
{
    //Memory[$s + C(signed)] = $t & 0x000000FF
    int addr;
    addr = read_data1 + simmediate;
    if(0<=addr&&addr<=1023)
        data_mem[addr  ] = (reg[rt].cur      ) && 0x000000ff;
    Error_OVF(); //detect Adder OVF
    Error_Dmem(addr); //detect D Memory OVF
    Error_Misaligned(addr); //detect S/L Wrong Memory
}
void I_lui()
{
    //$t = C << 16
    reg[rt].cur = immediate << 16;
    Error_R0(); //detect Write Register[0]
}
void I_andi()
{
    //$t = $s & C(unsigned)
    reg[rt].cur = read_data1 & immediate;
    Error_R0(); //detect Write Register[0]
}
void I_ori()
{
    //$t = $s | C(unsigned)
    reg[rt].cur = read_data1 | immediate;
    Error_R0(); //detect Write Register[0]
}
void I_nori()
{
    //$t = ~($s | C(unsigned))
    reg[rt].cur = ~(read_data1 | immediate);
    Error_R0(); //detect Write Register[0]
}
void I_slti()
{
    //$t = ($s < C(signed) ), signed comparison
    reg[rt].cur = read_data1 < simmediate;
    Error_R0(); //detect Write Register[0]
}
void I_beq()
{
    //if ($s == $t) go to PC+4+4*C(signed)
    if( read_data1 == read_data2 )
    {
        PC.cur = PC.cur + ( simmediate << 2 );
    }
    Error_OVF(); //detect Adder OVF
}
void I_bne()
{
    //if ($s != $t) go to PC+4+4*C(signed)
    if( read_data1 != read_data2 )
    {
        PC.cur = PC.cur + ( simmediate << 2 );
    }
    Error_OVF(); //detect Adder OVF
}
void I_bgtz()
{
    //if ($s > 0) go to PC+4+4*C(signed)
    if( read_data1 > 0)
    {
        PC.cur = PC.cur + ( simmediate << 2 );
    }
    Error_OVF(); //detect Adder OVF
}
/* I-Type Instructions */

/* J-Type Instructions */
void J_j()
{
    PC.cur = ( PC.cur >> 27 ) | ( immediate << 2 );
}
void J_jal()
{
    reg[31].cur = PC.cur;
    PC.cur = ( PC.cur >> 27 ) | ( immediate << 2 );
}
/* J-Type Instructions */

/* S-Type Instructions */
void halt()
{
    system("pause");
}
/* S-Type Instructions */



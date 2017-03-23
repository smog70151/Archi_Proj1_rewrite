#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
// to include the var
#include "var.h"

using namespace std;

//implement the meaning of the instruction
void ALU();

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


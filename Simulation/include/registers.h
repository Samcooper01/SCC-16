#ifndef REGISTERS_H
#define REGISTERS_H

//General Purpose Registers
#define GPR_0   0x00
#define GPR_1   0x01
#define GPR_2   0x02
#define GPR_3   0x03
#define GPR_4   0x04
#define GPR_5   0x05
#define GPR_6   0x06
#define GPR_7   0x07
//CPU only registers
#define IPR 0x0C
#define IR  0x0A
#define DR  0x09
#define ZF  0x08

int set_reg(int regx, int value);
int get_reg(int regx);

void clear_ZF();
void display_all_reg();

#endif /* REGISTERS_H */
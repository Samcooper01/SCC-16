#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#define FIRST_INSTRUCTION_INDEX     0x0000
#define CLOCK_DELAY_SECONDS         1

//Instructions with opcode
#define ADD         0x0
#define SUB         0x1
#define LSHF        0x2
#define MUL         0x3
#define DIV         0x4
#define GET         0x5
#define PUT         0x6
#define JZ          0x7

//Instruction masks
#define OPCODE_MASK         0xF000
#define OPERAND_1_MASK      0x0F00
#define OPERAND_2_MASK      0x00F0
#define DATA_MASK           0x00FF

int power_on();
void init();
void inc_IPR();
void run_cycles(int instruction_manual_mode);
void main_loop();

#endif /* CONTROL_UNIT_H */
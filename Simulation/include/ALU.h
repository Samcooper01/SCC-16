#ifndef ALU_H
#define ALU_H

//Math Operations
int add(int regx, int regy);
int sub(int regx, int regy);
int lshf(int regx, int regy);
int mul(int regx, int regy);
int div(int regx, int regy);

static int countBits(int num);

#endif /* ALU_H */
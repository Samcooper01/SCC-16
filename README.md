# SCC-16 CPU

## Overview
The SK-16 CPU is designed to execute a small set of simple instructions quickly. This document provides a comprehensive guide to the SK-16 CPU's instructions, registers, and operational cycle.

## Instructions
The SK-16 CPU uses a straightforward instruction set, where each instruction follows the format: Opcode - [Operand 1] - [Operand 2].

### Arithmetic Instructions
```
add [regx] [regy]
```
Description: Adds the value of regy to regx.
Opcode: 0000
Operation: regx = regx + regy
```
sub [regx] [regy]
```
Description: Subtracts the value of regy from regx. If regy is greater than regx, the result is 0.
Opcode: 0001
Operation: regx = regx - regy
```
lshf [regx] data
```
Description: Performs a left shift operation on regx by data bits.
Opcode: 0010
Operation: regx << data
```
mul [regx] [regy]
```

Description: Multiplies the value of regx by regy.
Opcode: 0011
Operation: regx = regx * regy
```
div [regx] [regy]
```
Description: Divides regx by regy. If dividing by zero, stores 0 in regx.
Opcode: 0100
Operation: regx = regx / regy
### Data Movement Instructions
```
get [regx], [regy]
```
Description: Loads the address of regy into regx.
Opcode: 0101
Operation: [regx] = &regy
```
put [regx], [regy]
```
Description: Stores the value of regx into the address of regy.
Opcode: 0110
Operation: &regy = [regx]
### Program Flow Instructions
```
jz [regx]
```
Description: Jumps to the address in regx if the Zero Flag (ZF) is set.
Opcode: 1000
Operation: If ZF == 1, then IR = [regx]; otherwise, do nothing.
### Condition Codes
```ZF``` (Zero Flag): Set if the result of the last arithmetic operation (add, sub, mul, div, lshf) was 0. This flag is cleared by the next instruction.
### Registers
#### General Purpose Registers
Name: machine-address
```
reg0: 0000
reg1: 0001
reg2: 0010
reg3: 0011
reg4: 0100
reg5: 0101
reg6: 0110
reg7: 0111
```
#### CPU Registers
```
IPR (Instruction Pointer Register): 1100
```
Holds the address of the next instruction to execute.
```
IR (Instruction Register): 1010
```
Contains the current instruction.
```
DR (Data Register): 1001
```
Used to temporarily store data between execution and write-back stages.
```
ZF (Zero Flag): 1000
```
Set (active high) by arithmetic operations if the result is 0.
## CPU Cycle
The CPU operates in a four-stage cycle:

### Fetch

- Retrieve the instruction from the address in IPR.
- Place the instruction into IR.
- Increment the IPR.

### Decode

- The Control Unit breaks down the instruction into components: opcode, operand 1, operand 2, and data.
- The Control Unit sets control signals for the next step.
### Execute

#### Arithmetic Operations: The ALU performs the operation specified by the opcode on the provided operands (registers). Results are moved to DR.
- add: Move result from adder block to DR.
- sub: Move result from subtractor block to DR.
- mul: Move result from multiplier block to DR.
- div: Move result from divider block to DR.
#### Data Movement and Flow: The Memory Manager performs the operation based on the instruction.
- get: Place the memory address from the instruction on the data memory bus and set the memory read signal.
- put: Place the memory address from the instruction on the data memory bus.
### Write Back

#### Arithmetic Operations: Move the value from DR to the specified operand register.
- add: Move value from DR to the first operand register.
- sub: Move value from DR to the first operand register.
- mul: Move value from DR to the first operand register.
- div: Move value from DR to the first operand register.
#### Data Movement and Flow:
- get: Move the value from DR to the specific operand register.
- put: Place the value from the operand register into DR and set the memory write signal.

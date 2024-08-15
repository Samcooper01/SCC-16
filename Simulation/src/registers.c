/*
 * File name: registers.c
 * Description: Simulated Register Map
 *
 * Notes:
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/registers.h"
#include "../include/config.h"

//Register Map
int gpReg_0 = 0x0000;
int gpReg_1 = 0x0000;
int gpReg_2 = 0x0000;
int gpReg_3 = 0x0000;
int gpReg_4 = 0x0000;
int gpReg_5 = 0x0000;
int gpReg_6 = 0x0000;
int gpReg_7 = 0x0000;
int IPReg = 0x0000;
int IReg = 0x0000;
int DReg = 0x0000;
int ZFReg = 0x0000;

static void
fatal_error(char * message)
{
    printf("ERROR: %s\n", message);
    exit(1);
}

int
set_reg(int regx, int value)
{
    debug_printf(DEBUG_LEVEL_1, "Setting reg: 0x%x with value: 0x%x\n", regx, value);
    switch(regx)
    {
        case GPR_0:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR0\n");
            gpReg_0 = value;
            break;
        case GPR_1:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR1\n");
            gpReg_1 = value;
            break;
        case GPR_2:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR2\n");
            gpReg_2 = value;
            break;
        case GPR_3:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR3\n");
            gpReg_3 = value;
            break;
        case GPR_4:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR4\n");
            gpReg_4 = value;
            break;
        case GPR_5:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR5\n");
            gpReg_5 = value;
            break;
        case GPR_6:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR6\n");
            gpReg_6 = value;
            break;
        case GPR_7:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR7\n");
            gpReg_7 = value;
            break;
        case IPR:
            debug_printf(DEBUG_LEVEL_1, "Accessing IPR\n");
            IPReg = value;
            break;
        case IR:
            debug_printf(DEBUG_LEVEL_1, "Accessing IR\n");
            IReg = value;
            break;
        case DR:
            debug_printf(DEBUG_LEVEL_1, "Accessing DR\n");
            DReg = value;
            break;
        case ZF:
            debug_printf(DEBUG_LEVEL_1, "Accessing ZF\n");
            ZFReg = value;
            break;
        default:
            fatal_error("Reg not found");
    }
    return 0;
}

void
clear_ZF()
{
    ZFReg = 0x0000;
}

int
get_reg(int regx)
{
    switch(regx)
    {
        case GPR_0:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR0\n");
            return gpReg_0;
        case GPR_1:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR1\n");
            return gpReg_1;
        case GPR_2:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR2\n");
            return gpReg_2;
        case GPR_3:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR3\n");
            return gpReg_3;
        case GPR_4:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR4\n");
            return gpReg_4;
        case GPR_5:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR5\n");
            return gpReg_5;
        case GPR_6:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR6\n");
            return gpReg_6;
        case GPR_7:
            debug_printf(DEBUG_LEVEL_1, "Accessing GPR7\n");
            return gpReg_7;
        case IPR:
            debug_printf(DEBUG_LEVEL_1, "Accessing IPR\n");
            return IPReg;
        case IR:
            debug_printf(DEBUG_LEVEL_1, "Accessing IR\n");
            return IReg;
        case DR:
            debug_printf(DEBUG_LEVEL_1, "Accessing DR\n");
            return DReg;
        case ZF:
            debug_printf(DEBUG_LEVEL_1, "Accessing ZF\n");
            return ZFReg;
        default:
            fatal_error("Reg not found");
    }
}

void
display_all_reg()
{
    printf("GPR_0: 0x%x\nGPR_1: 0x%x\nGPR_2: 0x%x\nGPR_3: 0x%x\n",
    gpReg_0, gpReg_1, gpReg_2, gpReg_3);

    printf("GPR_4: 0x%x\nGPR_5: 0x%x\nGPR_6: 0x%x\nGPR_7: 0x%x\n",
    gpReg_4, gpReg_5, gpReg_6, gpReg_7);

    printf("IPR: 0x%x\nIR: 0x%x\nDR: 0x%x\nZF: 0x%x\n",
    IPReg, IReg, DReg, ZFReg);
}

/* End of file: registers.c */
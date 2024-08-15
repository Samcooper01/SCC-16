/*
 * File name: control_unit.c
 * Description: Simulated Control Unit
 *
 * Notes:
 *
 */

#include <stdio.h>
#include <unistd.h>

#include "../include/control_unit.h"
#include "../include/ALU.h"
#include "../include/MMU.h"
#include "../include/registers.h"
#include "../include/config.h"

int power_on_cpu = 0;

int
power_on()
{
    power_on_cpu = 1;
    init();
}

void
init()
{
    set_reg(IPR, FIRST_INSTRUCTION_INDEX);

    int first_instruction = get_mem_value(IPR);
    set_reg(IR, first_instruction);

    inc_IPR();
    main_loop();
}

void
main_loop()
{
    //Clock delay per instruction
    while(1 == power_on_cpu)
    {
        sleep(CLOCK_DELAY_SECONDS);

        display_all_reg();

        run_cycles(-1);

        int next_instruction = get_mem_value(IPR);

        set_reg(IR, next_instruction);
        inc_IPR();
    }
}

void
run_cycles(int instruction_manual_mode)
{
    int instruction;
    if(-1 == instruction_manual_mode)
    {
        instruction = get_reg(IR);
    }
    else
    {
        instruction = instruction_manual_mode;
    }
    debug_printf(DEBUG_LEVEL_0, "Instruction Running: 0x%x\n", instruction);

    int opcode = instruction & OPCODE_MASK;
    opcode = opcode >> 12;
    debug_printf(DEBUG_LEVEL_0, "Instruction Opcode: 0x%x\n", opcode);

    int operand1 = instruction & OPERAND_1_MASK;
    operand1 = operand1 >> 8;
    int operand2 = instruction & OPERAND_2_MASK;
    operand2 = operand2 >> 4;

    int result;
    int test;

    if(opcode != JZ)
    {
        clear_ZF();
    }
    switch (opcode)
    {
        case ADD:
            result = add(operand1, operand2);
            set_reg(operand1, result);

            test = get_reg(operand1);
            debug_printf(DEBUG_LEVEL_0,
                        "Operand1: 0x%x Operand2: 0x%x RESULT: 0x%x\n",
                        operand1, operand2, test);
            break;
        case SUB:
            result = sub(operand1, operand2);
            set_reg(operand1, result);

            test = get_reg(operand1);
            debug_printf(DEBUG_LEVEL_0,
                        "Operand1: 0x%x Operand2: 0x%x RESULT: 0x%x\n",
                        operand1, operand2, test);
            break;
        case LSHF:
            operand2 = instruction & DATA_MASK;
            result = lshf(operand1, operand2);
            set_reg(operand1, result);
            debug_printf(DEBUG_LEVEL_0,
                        "Operand1: 0x%x Operand2: 0x%x RESULT: 0x%x\n",
                        operand1, operand2, result);
            break;
        case MUL:
            result = mul(operand1, operand2);
            set_reg(operand1, result);

            test = get_reg(operand1);
            debug_printf(DEBUG_LEVEL_0,
                        "Operand1: 0x%x Operand2: 0x%x RESULT: 0x%x\n",
                        operand1, operand2, result);
            break;
        case DIV:
            result = div(operand1, operand2);
            set_reg(operand1, result);

            test = get_reg(operand1);
            debug_printf(DEBUG_LEVEL_0,
                        "Operand1: 0x%x Operand2: 0x%x RESULT: 0x%x\n",
                        operand1, operand2, result);
            break;
        case GET:
            int regx_value = get_reg(operand1);
            int regy_value = get_reg(operand2);
            result = get_mem_value(operand2);

            set_reg(operand1, result);
            test = get_reg(operand1);
            debug_printf(DEBUG_LEVEL_0,
                        "Operand1: 0x%x Operand2: 0x%x RESULT: 0x%x\n",
                        operand1, operand2, test);
            break;
        case PUT:
            put_mem_value(operand1, operand2);
            debug_printf(DEBUG_LEVEL_0,
                        "Operand1: 0x%x Operand2: 0x%x\n",
                        operand1, operand2);
            break;
        case JZ:
            int zero_reg = get_reg(ZF);
            if(zero_reg == 1) {
                debug_printf(DEBUG_LEVEL_0,
                            "Operand1: 0x%x\n",
                            operand1);

                int regx_value = get_reg(operand1);
                set_reg(IPR, regx_value);
            }
            clear_ZF();
            break;
        default:
            printf("OPCODE NOT DEFINED ERROR");
    }
}

void
inc_IPR()
{
    int current_IPR_value = get_reg(IPR);
    int next_IPR_value = current_IPR_value + 1;
    debug_printf(DEBUG_LEVEL_2,
                "Current IPR: %x, Next IPR: %x\n",
                current_IPR_value, next_IPR_value);
    set_reg(IPR, next_IPR_value);
}

/* End of file: control_unit.c */

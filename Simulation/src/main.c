/*
 * Program Name: SCC-16 Simulated CPU
 * Description: Simulates SCC-16 Instruction Set
 * Author: Samuel Cooper
 * Version: 1.0
 *
 *
 * Notes:
 *      None.
 *
 * Style:
 *  https://github.com/Samcooper01/StyleGuide/tree/main
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/control_unit.h"
#include "../include/MMU.h"
#include "../include/registers.h"
#include "../include/config.h"

/**
 * @brief Run simulator one command at a time
 */
void
manual_mode()
{
    printf("Entering Manual Mode:\n");

    printf("Enter an instruction in hex to execute:\n");

    printf("Make sure to include leading 0s\n");
    printf("All instructions must be 4 hex digits including 0s\n");

    int instruction;
    while(1){

        printf("Enter instruction: ");
        scanf("%x", &instruction);

        run_cycles(instruction);
        inc_IPR();
        display_all_reg();

    }
}

/**
 * @note If additional memory is added in MMU.h then it needs to be added
 *       to the printf statements here to be displayed.
 */
static void
available_memory()
{
    printf("\n\nAvailable Memory:\n\n");

    printf("Required Memory Spaces:\n");
    printf("\tProgram Memory Addresses (decimal) - (hex)\n");
    printf("\t\t- Start: %d   0x%x\n", PROGRAM_MEMORY_START,
                                        PROGRAM_MEMORY_START);
    printf("\t\t- End: %d   0x%x\n", PROGRAM_MEMORY_END, PROGRAM_MEMORY_END);

    printf("\tData Memory Addresses (decimal) - (hex)\n");
    printf("\t\t- Start: %d   0x%x\n", DATA_MEMORY_START, DATA_MEMORY_START);
    printf("\t\t- End: %d   0x%x\n", DATA_MEMORY_END, DATA_MEMORY_END);

    //ADD Additional outputs here if more memory added.

    printf("\nUser Memory Spaces:\n");
    printf("\tNone.\n");
}

/**
 * @brief Usage functions
 */
static void
short_usage()
{
    printf("Short Usage:\n");
    printf("\n./scc-16.run [-i] [debug_level] [manual/auto/list_mem/help]\n");
    printf("\nUse the tag [help] for full usage\n\n");
    printf("If using debug mode [-i] enter an integer in [debug_level]. ");
    printf("Default debug level is 0 which is if [-i] and [debug_level] are");
    printf(" not used.\n\n");
    printf("Use 'manual' for manual mode and 'auto' to run simulator ");
    printf("with instructions in the PROG_memory.EEPROM file.\n");
}
static void
full_usage()
{
    printf("\nWelcome to the simulated SCC-16 processor.\n\n");
    //Identation in lines below causes usage to be displayed incorrectly
    printf("Instructions:\n \
Opcode - [Operand 1] - [Operand 2] - data\n \
\n\n\
Arithmetic Instructions\n \
add [regx] [regy]\n \
 regx = regx + regy\n \
 Opcode: 0000\n \
\n \
sub [regx] [regy]\n \
 regx = regx - regy\n \
 Opcode: 0001\n \
 *if regy > regx then returns 0\n \
\n \
lshf [regx] data\n \
 regx << data\n \
 Opcode: 0010\n \
 *doesnt shift leading 0s in\n \
\n \
mul [regx] [regy]\n \
 regx = regx * regy\n \
 Opcode: 0011\n \
\n \
div [regx] [regy]\n \
 regx = regx / regy\n \
 opcode: 0100\n \
*div by 0 results in 0 being stored in regx\n \
\n\n \
Data Movement Instructions\n \
get [regx], [regy]\n \
 [regx] = &regy\n \
 Opcode: 0101\n \
\n \
put [regx], [regy]\n \
 &regy = [regx]\n \
 Opcode: 0110\n \
\n\n \
Program flow Instructions\n \
jz [regx]\n \
 if (ZF == 1) then\n \
 IPR = [regx]\n \
 else \n \
 nothing\n \
 opcode: 1000\n \
 \n \
\n \
Registers\n \
\n \
General Purpose Registers\n \
All 16 bits in size\n \
reg0 - 0000\n \
reg1 - 0001\n \
reg2 - 0010\n \
reg3 - 0011\n \
reg4 - 0100\n \
reg5 - 0101\n \
reg6 - 0110\n \
reg7 - 0111\n \
\n \
CPU Registers\n \
IPR - Instruction Pointer Register - 1100\n \
IR - Instruction Register - 1010\n \
ZF - Zero flag register - 1000\n \
 *is set (active high) only from the listed arithmetic operations\n \
 Add [reg] [reg]\n \
 sub [reg] [reg]\n \
 lshf [reg] [data]\n \
 mul [reg] [reg]\n \
 div [reg] [reg]\n");

}

int
main(int argc, char *argv[]) {

    if(1 == argc)
    {
        short_usage();
    }
    else if((2 == argc) || (4 == argc))
    {
            if(4 == argc)
            {
                if(strcmp(argv[1], "-i") == 0)
                {
                    current_debug_level = atoi(argv[2]);
                }
            }
            if(strcmp(argv[argc-1],"help") == 0)
            {
                short_usage();
                full_usage();
                available_memory();
            }
            else if(strcmp(argv[argc-1],"manual") == 0)
            {
                printf("Running Simulated SCC-16\n\n");
                manual_mode();
            }
            else if(strcmp(argv[argc-1],"auto") == 0)
            {
                printf("Running Simulated SCC-16\n\n");
                power_on();
            }
            else if(strcmp(argv[argc-1], "list_mem") == 0)
            {
                available_memory();
            }
    }
    else
    {
        short_usage();
    }
    exit(0);
}

/* End of file: main.c */

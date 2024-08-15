/*
 * File name: MMU.c
 * Description: Simulated Memory Manager Unit
 *
 * Notes:
 *      A good number of printf statements are left here for debugging purposes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/MMU.h"
#include "../include/registers.h"
#include "../include/config.h"

const char* program_mem_file = "./Simulation/Memory/PROG_memory.EEPROM";
const char* data_mem_file = "./Simulation/Memory/DATA_memory.EEPROM";

static void
fatal_error(char * message)
{
    printf("ERROR: %s\n", message);
    exit(1);
}

/**
 * @brief Get mem value from regy
 */
int
get_mem_value(int regy)
{

    int addr_in_regy = get_reg(regy);
    debug_printf(DEBUG_LEVEL_1, "Getting Mem Value: %d\n", addr_in_regy);

    if((addr_in_regy >= PROGRAM_MEMORY_START) &&
        (addr_in_regy <= PROGRAM_MEMORY_END))
    {
        FILE *program_mem = fopen(program_mem_file, "r");
        if(NULL == program_mem) fatal_error("Opening program memory file.");

        int value = get_value_from_file
                    (addr_in_regy, program_mem, PROGRAM_MEMORY_START);
        debug_printf(DEBUG_LEVEL_1, "Value: %d\n", value);
        return value;
    }
    else if((addr_in_regy >= DATA_MEMORY_START) &&
            (addr_in_regy <= DATA_MEMORY_END))
    {
        FILE *data_mem = fopen(data_mem_file, "r");
        if(NULL == data_mem) fatal_error("Opening data memory file.");

        int value = get_value_from_file
                    (addr_in_regy, data_mem, DATA_MEMORY_START);
        debug_printf(DEBUG_LEVEL_1, "Value: %d\n", value);
        return value;
    }
    else
    {
        fatal_error("Program attempts to access invalid memory address");
    }
    //Add additional memory segments with else if statements
}

/**
 * @brief Put mem value from regx into address at regy
 */
void
put_mem_value(int regx, int regy)
{
    int addr_in_regy = get_reg(regy);
    int value_from_regx = get_reg(regx);
    debug_printf(DEBUG_LEVEL_1, "Putting value: 0x%d in address 0x%x\n",
                 value_from_regx, addr_in_regy);

    if(addr_in_regy >= PROGRAM_MEMORY_START &&
    addr_in_regy <= PROGRAM_MEMORY_END)
    {
        FILE *program_mem = fopen(program_mem_file, "r");
        if(NULL == program_mem) fatal_error("Opening program memory file.");

        put_value_from_reg_to_file(addr_in_regy, value_from_regx,
                                    PROGRAM_MEMORY_START,
                                    program_mem, program_mem_file);
    }
    else if(addr_in_regy >= DATA_MEMORY_START &&
    addr_in_regy <= DATA_MEMORY_END)
    {
        FILE *data_mem = fopen(data_mem_file, "r");
        if(NULL == data_mem) fatal_error("Opening data memory file.");

        put_value_from_reg_to_file(addr_in_regy, value_from_regx,
                                    DATA_MEMORY_START,
                                    data_mem, data_mem_file);
    }
    else
    {
        fatal_error("Program attempts to access invalid memory address");
    }
    //Add additional memory segments with else if statements
}

/**
 * @brief This function reads the entire file into a buffer
 *        then finds the line with the addr specified
 *        then overwrites the data part of the line with value
 *        then rewrites the entire file back to itself.
 *
 * @param addr Address to be found
 * @param value Value to write into location at addr
 * @param min_index The starting index of the memory segment
 * @param file Memory segment file descriptor to read from
 * @param filename Memory segment filename to reopen file from
 */
static void
put_value_from_reg_to_file(int addr, int value, int min_index,
                            FILE *file, const char* filename)
{
    debug_printf(DEBUG_LEVEL_2,
                "Min Index: %d value: %d\n",
                min_index, value);

    //Get the fileSize
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    debug_printf(DEBUG_LEVEL_2, "File Size: %ld\n", fileSize);

    // Allocate memory to hold the file content
    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) fatal_error("Memory allocation failed");

    // Read the file content into the buffer
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);
    debug_printf(DEBUG_LEVEL_2, "Buffer:\n");
    for(int idx = 0; idx < fileSize; idx++){
        debug_printf(DEBUG_LEVEL_2,
                    "index: %d, buffer[idx] %c\n",
                    idx, buffer[idx]);
    }

    //Parse through buffer only looking at the addresses on each line
    //and look for the address from regy
    int start_comparing = 0;
    int stop_comparing = 0;
    char compare_buffer[4];
    int compare_index = 0;

    for(int idx = 0; idx < fileSize; idx++)
    {
        debug_printf(DEBUG_LEVEL_2, "idx: %d\n", idx);
        if('x' == buffer[idx])
        {
            start_comparing = 1;
            stop_comparing = 0;
        }
        else if(' ' == buffer[idx])
        {
            stop_comparing = 1;
            start_comparing = 0;
            compare_index = 0;
            int value_instruction = 0;

            int bit = single_hex_char_to_int(compare_buffer[3]);
            value_instruction = value_instruction + (pow(16,0) * bit);
            bit = single_hex_char_to_int(compare_buffer[2]);
            value_instruction = value_instruction + (pow(16, 1) * bit);
            bit = single_hex_char_to_int(compare_buffer[1]);
            value_instruction = value_instruction + (pow(16, 2) * bit);
            bit = single_hex_char_to_int(compare_buffer[0]);
            value_instruction = value_instruction + (pow(16, 3) * bit);
            value_instruction = value_instruction + min_index;

            debug_printf(DEBUG_LEVEL_2,
                        "Value To Compare: %d Addr we are comparing: %d\n",
                        value_instruction, addr);

            if(value_instruction == addr)
            {
                debug_printf(DEBUG_LEVEL_2,
                            "Address found: %d\n",
                            value_instruction);
                for(int bit = 0; bit < 16; bit++)
                {
                    debug_printf(DEBUG_LEVEL_2,
                                "j: %d, buffer[j]: %d\n",
                                bit, buffer[idx+bit + 1]);

                    int new_bit = get_nth_bit(value, (15-bit));
                    debug_printf(DEBUG_LEVEL_2, "Replacing: %d With: %d\n",
                                buffer[idx+bit+1], new_bit);

                    char new_bit_char = new_bit + '0';
                    buffer[idx+bit+1] = new_bit_char;
                }
            }
        }
        else if((start_comparing == 1) && (stop_comparing == 0))
        {
            debug_printf(DEBUG_LEVEL_2,
                        "buffer[idx]: %d compare_index: %d\n",
                        buffer[idx], compare_index);

            compare_buffer[compare_index] = buffer[idx];
            compare_index++;
        }
    }
    debug_printf(DEBUG_LEVEL_2, "%s\n", filename);
    FILE *mem = fopen(filename, "w");
    if(mem == NULL) fatal_error("File open failed");

    debug_printf(DEBUG_LEVEL_2, "Buffer:\n");
    for(int idx = 0; idx < fileSize; idx++){
        debug_printf(DEBUG_LEVEL_2,
                    "index: %d, buffer[idx] %c\n",
                    idx, buffer[idx]);
    }
    fwrite(buffer, 1, fileSize, mem);
    fclose(mem);
    free(buffer);
}

/**
 * @brief This function goes line by line comparing addr
 *        then finds the line with the addr specified
 *        then returns the value at that address as an int
 *
 * @param addr Address to get value from
 * @param file Memory segment file descriptor to read from
 * @param start_index Offset index to start from
 */
static int
get_value_from_file(int addr, FILE *file, int start_index)
{
    debug_printf(DEBUG_LEVEL_2, "Getting addr: 0x%x from memory\n", addr);
    char line_buffer[256];
    //This can be 256 bc the max line size should be 16 chars for addr
    //and 17 chars for value with a newline character at the end
    //so 16+17 = 33 chars

    while(fgets(line_buffer, sizeof(line_buffer), file) != NULL)
    {
        char chars_before_space[16]; // This should only be 6 MAX (0xXXXX) is
                                     // everything before the space

        for(int idx = 0; idx < sizeof(line_buffer); idx++)
        {
            debug_printf(DEBUG_LEVEL_2, "CHAR: %c\n", line_buffer[idx]);
            if(line_buffer[idx] != ' ')
            {
                chars_before_space[idx] = line_buffer[idx];
            }
            else {
                break; //Space found
            }
        }

        //Get value as int
        int value_instruction = 0;
        int bit = single_hex_char_to_int(chars_before_space[5]);
        value_instruction = value_instruction + (pow(16,0) * bit);
        bit = single_hex_char_to_int(chars_before_space[4]);
        value_instruction = value_instruction + (pow(16, 1) * bit);
        bit = single_hex_char_to_int(chars_before_space[3]);
        value_instruction = value_instruction + (pow(16, 2) * bit);
        bit = single_hex_char_to_int(chars_before_space[2]);
        value_instruction = value_instruction + (pow(16, 3) * bit);
        value_instruction = value_instruction + start_index;

        debug_printf(DEBUG_LEVEL_2,
                    "Line memory address: 0x%x Addr we are looking for: 0x%x\n",
                    value_instruction, addr);
        if (value_instruction == addr)
        {
            char value[32];
            int value_index = 0;
            int past_space = 0;

            for(int idx = 0; idx < sizeof(line_buffer); idx++)
            {
                debug_printf(DEBUG_LEVEL_2,
                            "Linebuffer[i] = %c\n",
                            line_buffer[idx]);

                if('\n' == line_buffer[idx])
                {
                    break;
                }
                if(' ' == line_buffer[idx])
                {
                    past_space = 1;
                }
                else if(1 == past_space)
                {
                    debug_printf(DEBUG_LEVEL_2,
                                "Adding to value: %c\n",
                                line_buffer[idx]);

                    value[value_index] = line_buffer[idx];
                    value_index++;
                }
            }
            int output = 0;
            for (int idx = 0; idx < sizeof(value); idx++)
            {
                if(0 != value[idx])
                {
                    int value_of_digit = pow(2, (15-idx));
                    debug_printf(DEBUG_LEVEL_2,
                                "BIT: %d  Value of digit: %d BIT VALUE: %d\n",
                                (15-idx), value_of_digit, (value[idx] - '0'));

                    output = output + value_of_digit * (value[idx] - '0');
                }
                else
                {
                    break;
                }
            }
            return output;
        }
    }
    fatal_error("Addr not found");
}

/**
 * @brief Converts hex chars in buffer to an int
 */
static int
convert_hex_chars_to_int(char *buffer)
{
    int output = 0;
    int x_reached = 0;

    for(int idx = 0; idx < sizeof(buffer); idx++)
    {
        debug_printf(DEBUG_LEVEL_2,
                    "HEX TO INT: %c\n", buffer[idx]);
        if(0 == buffer[idx])
        {
            return output;
        }
        if('x' == buffer[idx])
        {
            x_reached = 1;
        }
        else if (1 == x_reached)
        {
            debug_printf(DEBUG_LEVEL_2, "Buffer[i] = %d\n", buffer[idx]);
            int value = single_hex_char_to_int(buffer[idx]);
            debug_printf(DEBUG_LEVEL_2, "value: %d\n", value);
            output = output + value;
        }
    }

    return output;
}

static int
single_hex_char_to_int(char convert)
{
    if(convert == '0') return 0;
    else if(convert == '1') return 1;
    else if(convert == '2') return 2;
    else if(convert == '3') return 3;
    else if(convert == '4') return 4;
    else if(convert == '5') return 5;
    else if(convert == '6') return 6;
    else if(convert == '7') return 7;
    else if(convert == '8') return 8;
    else if(convert == '9') return 9;
    else if(convert == 'A' || convert == 'a') return 10;
    else if(convert == 'B' || convert == 'b') return 11;
    else if(convert == 'C' || convert == 'c') return 12;
    else if(convert == 'D' || convert == 'd') return 13;
    else if(convert == 'E' || convert == 'e') return 14;
    else if(convert == 'F' || convert == 'f') return 15;
    else fatal_error("BROKEN ADDRESS");
}

static int
get_nth_bit(int value, int bit)
{
    return (value >> bit) & 1;
}

/* End of file: MMU.c */

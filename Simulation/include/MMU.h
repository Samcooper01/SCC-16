#ifndef MMU_H
#define MMU_H

//Memory Segments
#define PROGRAM_MEMORY_START    0x0000
#define PROGRAM_MEMORY_END      0x0200  //0000_0010_0000_0000 (512)

#define DATA_MEMORY_START       0x0201
#define DATA_MEMORY_END         0x0F00 //0000_1111_0000_000 (3840)
//NOTE: if additional memory is added here it should be added in main.c function
//      available_memory() to let user know it exists

int get_mem_value(int regy);
static int get_value_from_file(int addr, FILE *file, int start_index);

void put_mem_value(int regx, int regy);
static void put_value_from_reg_to_file
            (int addr, int value, int start_index,
            FILE *file, const char* filename);

static int convert_hex_chars_to_int(char *buffer);
static int single_hex_char_to_int(char convert);
static int get_nth_bit(int value, int bit);

#endif /* MMU_H */
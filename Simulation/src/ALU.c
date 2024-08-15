/*
 * File name: ALU.c
 * Description: Simulated Arithmatic Logic
 *
 * Notes:
 *      A good number of printf statements are left here for debugging purposes.
 */

#include <stdio.h>

#include "../include/registers.h"
#include "../include/ALU.h"
#include "../include/config.h"

/**
 * @brief return = regx + regy
 *
 */
int
add(int regx, int regy)
{
    int result = 0;
    int regx_value = get_reg(regx);
    int regy_value = get_reg(regy);
    result = regx_value + regy_value;
    if(0 == result) {
        set_reg(ZF, 0x0001);
    }
    return result;
}

/**
 * @brief return = regx - regy
 *        if regy > regx then return 0
 *
 * @note if regx > regy then return 0
 *
 */
int
sub(int regx, int regy)
{
    int result = 0;
    int regx_value = get_reg(regx);
    int regy_value = get_reg(regy);

    if(regx_value < regy_value)
    {
        result = 0;
    }
    else
    {
        result = regx_value - regy_value;
    }   

    if(0 == result)
    {
        set_reg(ZF, 0x0001);
    }
    return result;
}

/**
 * @brief regx = regx << 8
 *        return = regx + data
 *
 */
int
lshf(int regx, int data)
{
    int regx_value = get_reg(regx);
    short result = regx_value;

    result = regx_value << 8;
    result = result + data;
    if(0 == result) {
        set_reg(ZF, 0x0001);
    }
    return result;
}

/**
 * @brief return = regx * regy
 *
 */
int
mul(int regx, int regy)
{
    int result = 0;
    int regx_value = get_reg(regx);
    int regy_value = get_reg(regy);

    result = regx_value * regy_value;
    if(0 == result)
    {
        set_reg(ZF, 0x0001);
    }
    return result;
}

/**
 * @brief return = regx * regy
 *
 * @note if dividing by 0 then 0 is returned
 *
 */
int
div(int regx, int regy)
{
    int result = 0;
    int regx_value = get_reg(regx);
    int regy_value = get_reg(regy);

    if(0 == regy_value)
    {
        set_reg(ZF, 0x0001);
        return result;
    }

    result = regx_value / regy_value;
    if(0 == result)
    {
        set_reg(ZF, 0x0001);
    }

    return result;
}

/**
 * @brief return num of bits required to make num
 *
 */
static int
countBits(int num)
{
    unsigned int count = 0;
    while (num > 0)
    {
        count++;
        num >>= 1;
    }
    return count;
}

/* End of file: ALU.c */

/**
* @file - conversion.c
* @brief - Implementation file for the data conversion functions
*
* @author Gunj/Ashish University of Colorado Boulder
* @date 02/10/2017
**/

#include "conversion.h"
#include "memory.h"

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
	return;
}

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base)
{
	return;
}

int8_t big_to_little32(uint32_t * data, uint32_t length)
{
	int8_t *p_reverse = (int8_t*)my_reverse((uint8_t*)data, (length*4));
	int8_t p_ret = 1;
	if(p_reverse)
		p_ret = 0;
	return p_ret;
}

int8_t little_to_big32(uint32_t * data, uint32_t length)
{
	int8_t *p_reverse = (int8_t*)my_reverse((uint8_t*)data, (length*4));
	int8_t p_ret = 1;
	if (p_reverse)
		p_ret = 0;
	return p_ret;
}

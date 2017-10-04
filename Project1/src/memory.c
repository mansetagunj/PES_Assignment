/**
* @file - memory.c
* @brief - Implementation file for the memory functions
*
* @author Gunj/Ashish University of Colorado Boulder
* @date 02/10/2017
**/

#include "memory.h"
#include <malloc.h>

uint8_t* my_memmove(uint8_t * src, uint8_t * dst, size_t length)
{
	uint8_t *p_ret = NULL;
	if (NULL != dst && NULL != src)
	{
		uint8_t *p_tempMem = (uint8_t*)malloc(sizeof(uint8_t)*length);
		uint8_t *p_src = src;
		uint8_t *p_dst = dst;

		//Deep copy of the Src memory to a temp memory to handle any memory overlap issue
		size_t tempLength = length;
		while (tempLength--)
		{
			*p_tempMem = *p_src++;
			++p_tempMem;
		}

		p_tempMem -= length;	//bringing back the pointer to point to the start of the allocated mem
		tempLength = length;
		while (tempLength--)
		{
			*p_dst = *p_tempMem++;
			++p_dst;
		}
		
		p_tempMem -= length;	//bringing back the pointer to point to the start of the allocated mem
		free(p_tempMem);
		p_tempMem = NULL;

		p_ret = p_dst;
	}
	
	return p_ret;
}

uint8_t* my_memcpy(uint8_t * src, uint8_t * dst, size_t length)
{
	uint8_t *p_ret = NULL;
	if (NULL != dst && NULL != src)
	{
		uint8_t *p_src = src;
		uint8_t *p_dst = dst;

		//Deep copy of the Src memory to Dst memory
		size_t tempLength = length;
		while (tempLength--)
		{
			*p_dst = *p_src++;
			++p_dst;
		}

		p_ret = dst;
	}

	return p_ret;
}

int8_t* my_memset(uint8_t * src, size_t length, uint8_t value)
{
	if (NULL != src)
	{
		uint8_t *p_src = src;
		size_t tempLength = length;
		while (tempLength--)
		{
			*p_src = value;
			++p_src;
		}
		p_src = NULL;
	}	
	return src;
}

uint8_t* my_memzero(uint8_t * src, size_t length)
{
	if (NULL != src)
	{
		uint8_t *p_src = src;
		size_t tempLength = length;
		while (tempLength--)
		{
			*p_src = 0;
			++p_src;
		}
		p_src = NULL;
	}
	return src;
}

uint8_t* my_reverse(uint8_t *src, size_t length)
{
	if (NULL != src && 0 < length)
	{
		char *forwardItr = src;
		char *backwardItr = src+length-1;

		//divide the length by two to get the midpoint value to use it in the loop
		int itr = length >> 1;
		while (itr && forwardItr && backwardItr)
		{
			//swapping routine
			uint8_t temp = *forwardItr;
			*forwardItr = *backwardItr;
			*backwardItr = temp;
			++forwardItr; //incrementing the forward pointer
			--backwardItr; //decrementing the reverse pointer
			--itr;
		}
		forwardItr = NULL;
		backwardItr = NULL;
	}
	return src;
}

int32_t* reserve_words(size_t length)
{
	int32_t *reservedMem = (int32_t*)malloc(sizeof(int32_t)*length);
	return reservedMem;
}

void free_words(int32_t *src)
{
	free(src);
}

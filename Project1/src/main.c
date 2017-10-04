/**
* @file - main.c
* @brief - Contains the entry point of the program which tests various functionalities
* 
* @author Gunj/Ashish University of Colorado Boulder
* @date	02/10/2017
**/

#define TESTCOUNT 8
#define PROJECT1
#ifdef PROJECT1
#include "project1.h"
#include "conversion.h"
#include "debug.h"
#include <stdlib.h>
#endif // PROJECT1
int main()
{
#ifdef PROJECT1
	//project1();
#endif // PROJECT1


	uint8_t i;
	int8_t failed = 0;
	int8_t results[TESTCOUNT];

	results[0] = 0;// test_data1();
	results[1] = 0;// test_data2();
	results[2] = test_memmove1();
	results[3] = test_memmove2();
	results[4] = test_memmove3();
	results[5] = test_memcpy();
	results[6] = test_memset();
	results[7] = test_reverse();
	uint32_t *data = (uint32_t*)malloc(sizeof(uint32_t));
	*data = 0x12345678;
	printf("/n/n");
	print_memory(data,4);
	printf("/n/n");
	big_to_little32(data,1);
	print_memory(data, 4);
	printf("/n/n");
	little_to_big32(data,1);
	print_memory(data, 4);
	printf("/n/n");

	for (i = 0; i < TESTCOUNT; i++)
	{
		failed += results[i];
	}

	printf("--------------------------------\n");
	printf("Test Results:\n");
	printf("  PASSED: %d / %d\n", (TESTCOUNT - failed), TESTCOUNT);
	printf("  FAILED: %d / %d\n", failed, TESTCOUNT);
	printf("--------------------------------\n");
	
	char ptr[33] = { 0 };
	itoa(-10, ptr, 16);
	printf("\nStr:%s", ptr);

	itoa(-10, ptr, 8);
	printf("\nStr:%s", ptr);
	
	itoa(-10, ptr, 2);
	printf("\nStr:%s", ptr);

	return 0;
}
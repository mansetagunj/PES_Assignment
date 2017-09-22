#include <stdio.h>

int main()
{
	unsigned char array[8] = 
	{ 	//arraypos=> emulates mem location
	0xEE,	//array+0 => 100
	0x12,	//array+1 => 101
	0x77,	//array+2 => 102
	0xBE,	//array+3 => 103
	0x66,	//array+4 => 104
	0x54,	//array+5 => 105
	0x33,	//array+6 => 106
	0xF0	//array+7 => 107
	};	
	
	unsigned char *ptr = array;
	*ptr = 0xF1 & 127;
	ptr++;
	*ptr += 17;
	ptr += 2;
	*ptr = 15 % 4;
	ptr--;
	*ptr >>= 4;
	ptr = (char*)(array+5);
	*ptr = (1<<5)|(4<<2);
	*((char*)(array+7)) = 22;

	int index = 0;
	ptr = array;
	while(index<8)
	{
		printf("Addr: %d	0x%x\n", (100+index),*ptr++);
		++index;
	}

	return 0;
}							

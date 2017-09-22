#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void print_arch_data()
{
	system("lscpu | awk '/Archi*/{print $NR $NF}'");
	
	printf("Size of char: %d\n",sizeof(char));
	printf("Size of int: %d\n",sizeof(int));
	printf("Size of float: %d\n",sizeof(float));
	printf("Size of double: %d\n",sizeof(double));
	printf("Size of short: %d\n",sizeof(short));
	printf("Size of long: %d\n",sizeof(long));
	printf("Size of long int: %d\n",sizeof(long int));
	printf("Size of long long: %d\n",sizeof(long long));
	printf("Size of int8_t: %d\n",sizeof(int8_t));
	printf("Size of uint8_t: %d\n",sizeof(uint8_t));
	printf("Size of uint16_t: %d\n",sizeof(uint16_t));
	printf("Size of uint32_t: %d\n",sizeof(uint32_t));
	printf("Size of char*: %d\n",sizeof(char*));
	printf("Size of int*: %d\n",sizeof(int*));
	printf("Size of float*: %d\n",sizeof(float*));
	printf("Size of void*: %d\n",sizeof(void*));
	printf("Size of void**: %d\n",sizeof(void**));
	printf("Size of int8_t*: %d\n",sizeof(int8_t*));
	printf("Size of int16_t*: %d\n",sizeof(int16_t*));
	printf("Size of int32_t: %d\n",sizeof(int32_t*));
	printf("Size of size_t: %d\n",sizeof(size_t));
}

int main()
{

	print_arch_data();
	return 0;
}

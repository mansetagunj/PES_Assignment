/*
r Gunj Manseta
* @date 09/15/2017
* * @version 1.0
* */

#include <stdio.h>

/*
 * * Enum used to encapsulate the status codes for the Reverse String
 * function.
 * */
typedef enum reverseStringResultCode
{
	successCode,
	inputLengthActualLengthMismatchErrCode,
	inputStringEmptyErrCode,
	inputLengthNegativeErrCode,
	inputStringNullErrCode,
	inputLengthMismatchErrCode,
	inputLengthZeroErrCode,
}ResultCode;

/*
 * * @brief Reverses a string
 * *
 * * Given the pointer to the non-constant string as input along with its
 * length,
 * * the function reverses the string in the same memory location.
 * * The reverse string can be accessed using the same pointer passed as
 * input * param.
 * *
 * * @param str char* Pointer to the non-constant string
 * * @param length int Length of the non-constant string
 * *
 * * @return char Status code of the operation in the function. Can be
 * mapped to the * ResultCode enum to get the description.
 * */

char reverse(char *str, int length)
{
	if (NULL == str)
		return inputLengthActualLengthMismatchErrCode;
	if (0 > length)
		return inputLengthNegativeErrCode;
	char *startStr = str;
	char *copyStr = str;
	int checkLength = 0;
	while ('\0' != *str)
	{
		++checkLength;
		++str;
	}
	if (checkLength != length)
		return inputLengthMismatchErrCode;
	if (0 == checkLength)
		return inputStringEmptyErrCode;
	//here str points to the null char in the string so decrementing it to point it to last char
	--str;
	//divide the length by two to get the midpoint value to use it in the loop
	int itr = length >> 1;
	//copyStr points to the first char of the input string. So, forward pointer
	//str points to the end char of the input string. So, reverse pointer
	while (itr && copyStr && str)
	{
	//swapping routine
	char temp = *copyStr;
	*copyStr = *str;
	*str = temp;
	++copyStr;	//incrementing the forward pointer
	--str; 		//decrementing the reverse pointer
	--itr;
	}
	str = startStr;
	return successCode;
}


int main()
{
	char testString1[18] = "This is a string.";
	char testString2[19] = "some NUMmbers12345";
	char testString3[31] = "Does it reverse \n\0\t correctly?";

	printf("\nTestString1 - %s",testString1);
	char status = reverse(testString1,17);
	if(0 == status)
		printf("\nAfter Reverse TestString1 - %s",testString1);
	else
		printf("\nError. Code : %d",status);
	
	printf("\n--------------------------------------------");
	
	printf("\nTestString2 - %s",testString2);
	status = reverse(testString2,18);
	if(0 == status)
		printf("\nAfter Reverse TestString2 - %s",testString2);
	else
		printf("\nError. Code : %d",status);
	
	printf("\n--------------------------------------------");
	
	printf("\nTestString3 - %s",testString3);
	status = reverse(testString3,30);
	if(0 == status)
		printf("\nAfter Reverse TestString3 - %s",testString3);
	else
		printf("\nError. Code : %d",status);

	printf("\nTEST END\n");
	return 0;
}

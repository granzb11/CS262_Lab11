#include <stdio.h>
#include <stdlib.h>

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"

#define BYTETOBINARY(byte)  \
	(byte & 0x80 ? 1 : 0), \
(byte & 0x40 ? 1 : 0), \
(byte & 0x20 ? 1 : 0), \
(byte & 0x10 ? 1 : 0), \
(byte & 0x08 ? 1 : 0), \
(byte & 0x04 ? 1 : 0), \
(byte & 0x02 ? 1 : 0), \
(byte & 0x01 ? 1 : 0) 

#define PRINTBIN(x)  printf(BYTETOBINARYPATTERN, BYTETOBINARY(x));
#define ARRAYLEN 8

//This function will take as its parrameter an array of unsigned character types and return a byte which will containing the least significant byte of each of the different unsigned characters in the *p array
unsigned char getlsbs(unsigned char *p)
{
	unsigned char final=0; //unsigned character that will be return at the end of the function
	int i;

//This for loop will go through the array passed in and 'add' the last significant bit to final
	for(i=0;i<8; i++)
	{
		final >>=1;//moves over to the next bit of the byte 
		if(p[i] & 1)
			final |= 0x80;

	}
	return final;
}


//This function will take in as its parameters an array of 8 different bytes and one unsigned character byte. It will then change the least significant bit of each of the bytes in the array to match the byte passed in 
void setlsbs(unsigned char *p, unsigned char b0)
{
	int i;

//For loop that will go through each byte in the array and 'change' the lsbs to match the byte 'b0' that was passed in
	for(i=0; i<ARRAYLEN; i++)
	{
		if(b0 & 1)
			p[i] |=1;//when the least significant bit of the byte is 1 and b0 is 1 do the "or" bitwise operation
		else
			p[i] &=0xFE;//when the least significant bit of the byte is 0 do the "and" bitwise operation
		b0>>=1;//shift the b0 byte over by one bit to the left and compare its lsbs to the next lsbs of the next byte in the array

	}
}

int main(int argc, char **argv)
{

	unsigned char myArray[ARRAYLEN];
	unsigned char b, newB;
	int i,seed;

	sscanf(argv[1], "%d", &seed);//read in the random seed from the command line
	srandom(seed);//seed the random number generator using what was read in from the command line

//for loop that will initialize the random numbers in the array with numbers between 0 and 255
	for(i=0; i<ARRAYLEN; i++)
	{
		myArray[i]=random()%(255+1);
		printf("\nThe %dth random number is %d: ", i, myArray[i]);
		PRINTBIN(myArray[i]);
	}
	b = random()%(255+1);//initializing our b0 byte to a random number
	printf("\n\nThe original b0 is %d: ", b);
	PRINTBIN(b);
	printf("\n");

	setlsbs(myArray, b);//calling setlsbs
	printf("\n");


	printf("In the setlsbs function:\n");
//printing out the results from setlsbs
	for(i=0; i<ARRAYLEN; i++)
	{
		printf("The %dth random number with replaced least significant bit is %d: ", i, myArray[i]);
		PRINTBIN(myArray[i]);
		printf("\n");
	}

	newB = getlsbs(myArray);//calling getlsbs and assigning the value returned to 'newB'

	printf("\n");

printf("In the getlsbs function:\n");

//printing out the results of getlsbs
	for(i=ARRAYLEN-1; i>=0; i--)
	{
		printf("The %dth random number with replaced least significant bit is %d: ", i, myArray[i]);
		PRINTBIN(myArray[i]);
		printf("\n");
	}
	printf("The b0 from 'myArray' is %d: ", newB);
	PRINTBIN(newB);
	printf("\n");

}


// made by roscoe casita

#include <stdio.h>
#include <math.h>

struct ieee754
{
	// order of variables matter
	unsigned int exponent : 8;
	unsigned int mantissa : 23;
	unsigned int sign_bit : 1;
};

struct ieee754 float_to_struct(float data)
{
	// retrieve address and place in pointer to struct
	struct ieee754* ptr = (struct ieee754*) &data;
	struct ieee754 item;
	// derefernce pointer
	item = (*ptr);
	return item;

	return * ((struct ieee754*) &data);
};

float struct_to_float(struct ieee754 data)
{
	float *ptr = (float *) &data;
	float item = (*ptr);
	return item;
}


void ieee754_print((struct ieee754) ieee754 item)
{
	printf("Sign Bit:\t%d\n", item.sign_bit);
	printf("Mantissa:\t%d\n", item.mantissa);
	printf("Exponent:\t%d\n", item.exponent);
	printf("Float:\t%f\n", (float*) &item);

}

// read float in
struct ieee754 ieee754_read()
{
	float temp = 0.0;
	struct ieee754 item;
	printf("Enter a floating point value:\n");
	scanf("%f", &temp);
	item = float_to_struct(temp);
	return item;
}

struct four_byte
{
	unsigned int b0:8;
	unsigned int b1:8;
	unsigned int b2: 8;
	unsigned int b3: 8;
}

// *A and A[0] are the same derefernce operation
int main(int argc, char *argv[])
{
	struct ieee754 value;
	float temp;

	value = ieee754_read();

	ieee754_print(value);

	value.sign_bit = ~value.sign_bit;
	// shift right >> 31 bits, position 0
	// copy value into temp register
	// invert value
	// shift left << 31 bits, position 31
	// logical and signbit by 0
	// logical or signbit with new signbit

	ieee754_print(value);


}

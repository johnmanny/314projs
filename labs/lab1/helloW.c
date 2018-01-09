#include "string.h"
#include "stdio.h"
#include "math.h"

int main (int argc, char *argv[])
{
	int i;
	char question[] = "The answer to life, the universe, and everything is: %f\r\n";
	float answer = 42.0;

	printf("Total Arguments: %d\r\n", argc);
	for (i = 0; i < argc; i++)
	{
		printf("Argument %d is: %s\r\n", i, argv[i]);
	}
	printf(question,answer);
	return answer;
}

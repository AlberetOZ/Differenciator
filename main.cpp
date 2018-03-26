#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <iostream>
#include "Node.h"
#include "Differenciator.h"
#define MAX_INPUT 10000


#define asserted || assert(!printf("Error, asserted here\n"))



int main()
{

	printf("beta version//\nПример ввода:* ( + ( X ) ( * ( 1234 ) ( Y ) ) ) ( 228 )\n");

	int input_number = 0;

	char input[MAX_INPUT] = {0};

	for(int i = 0; scanf("%c", &input[i]) == 1; i++)
	{
		if(input[i] == '*')
		{
			input[i + input_number] = input[i];

			for(int j = 1; j <= input_number; j++)
			{
				input[i+input_number+j] = '_';
				input[i+j-1] = '_';
			}
			i += input_number;
			input_number++;
			//////
		}


		if(i > MAX_INPUT - 10)
			printf("Завязывай давай, я столько не продифференцирую, не больше 10 символов ещё\n");
		if(i == MAX_INPUT - 1)
		{
			printf("limit of member\n");
			assert(!"limit");
		}

	}

	FILE* data = fopen("data", "w");
	
	assert(data);

	fprintf(data, " ( ");

	fputs(input, data);

	fprintf(data, " $$$$$$$$$$$$$");

	fclose(data);

	Node test;

//	for(; scanf("%s %s", data_operand + 1, data_number) == 2; number_input++)
//	{



//	}



	test.scan();    //задебажил этоооо

	test.dump();

	return 0;
}

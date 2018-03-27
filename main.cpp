#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <iostream>
#include "Node.h"
#include "Differenciator.h"
#include "check_skobki.h"
#define MAX_INPUT 10000



int main()
{

	printf("beta version//\nПример ввода:exp ( * ( + ( * ( + ( X ) ( 123 ) ) ( sin ( 98 ) ) ) ( err ) ) ( log ( 231 ) ( z ) ) )\n");

	char input[MAX_INPUT] = {0};

	for(int i = 0; scanf("%c", &input[i]) == 1; i++)
	{

		if(input[i] == '\n')
		{
			input[i] = '\0';

			break;
		}


		if(i > MAX_INPUT - 100)
			printf("Завязывай давай, я столько не продифференцирую, не больше 100 символов ещё\n");
		if(i == MAX_INPUT - 1)
		{
			printf("limit of member\n");
			assert(!"limit");
		}

	}


	FILE* data = fopen("data", "w");
	
	assert(data);

	fprintf(data, " ");

	fputs(input, data);

	fprintf(data, " $$$$$$$$$$$$$");

	fclose(data);

	if(check_scobki(data) == 0)
	{

		printf("\n!!!!!!!!!!!!!!!!!!!\nТут проблема со скобками, я такое не дифференцирую((((\n!!!!!!!!!!!!!!!!\n");
		return 1;	


	}

	Node test;

	test.scan();    //задебажил этоооо

	FILE * dump_input_file = fopen("input", "w");

	assert(dump_input_file);

	test.dump(dump_input_file);

	fclose(dump_input_file);

	system("dot -Tgif -Oinput.gif input");

	return 0;
}

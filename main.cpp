#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <iostream>
#include "Node.h"
#include "Differenciator.h"
#include "check_skobki.h"
#define MAX_INPUT 10000

int print_data(const char* input)
{
	FILE* data = fopen("data", "w");
	
	assert(data);

	fprintf(data, " ");

	fputs(input, data);

	fprintf(data, " $$$$$$$$$$$$$");

	fclose(data);
    

	
	if(check_scobki(data) == 0)
	{

		printf("\n!!!!!!!!!!!!!!!!!!!\nТут проблема со скобками, я такое не дифференцирую((((\n!!!!!!!!!!!!!!!!\n");
		return -1;	


	}


	return 0;
}


int dump_input(Node* expression)
{
	FILE * dump_input_file = fopen("input", "w");

	assert(dump_input_file);

	(*expression).dump(dump_input_file);

	fclose(dump_input_file);
    
	return 0;
}

int scanf_input(char* input)
{

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

	if(input[0] == '\0')
	{
	
		printf("\n!!!!!!!!!!!!!!!!!!!\nНичего не введено, я такое не дифференцирую((((\n!!!!!!!!!!!!!!!!\n");


		return -1;


	}
	return 0;    
}

int main()
{

	printf("beta version//\nПример ввода:\nexp ( * ( + ( * ( + ( X ) ( 123 ) ) ( sin ( X ) ) ) ( X ) ) ( log ( 2 ) ( X ) ) )\n\n");

	char input[MAX_INPUT] = {0};
    
	assert(!scanf_input(input));

	assert(!print_data(input));

	Node expression;
    

	FILE* data = fopen("data", "r");

	expression.scan(data);    //задебажил этоооо

	fclose(data);

	assert(!dump_input(&expression));

	system("dot -Tgif -Oinput.gif input");

	return 0;
}

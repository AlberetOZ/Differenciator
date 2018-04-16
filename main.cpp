#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <iostream>
#include "Node.hpp"
#include "Differenciator.hpp"
#include "check_skobki.h"
#define MAX_INPUT 10000

int print_data(const char* input)
{
	FILE* data = fopen("data", "w");
	
	assert(data);

	fprintf(data, " ");

	fputs(input, data);

	fprintf(data, "$$$$$$$$$$$$$");

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

int dump_answer(Node* expression)
{
	FILE * dump_answer_file = fopen("answer_dump", "w");

	assert(dump_answer_file);

	(*expression).dump(dump_answer_file);

	fclose(dump_answer_file);

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
			printf("\nlimit of member\n");
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

//	int optimize = 0;		пока без оптимизации

	printf("beta version\nДиффиренцирую только по Х\nПример ввода:\n* ( + ( sin ( 13x ) ) ( ln ( 9x ) ) ) ( 5x )\n\n");

	char input[MAX_INPUT] = {0};

	printf("Вводите выражение:\n");
    
	assert(!scanf_input(input));

	assert(!print_data(input));

	Node expression;
    

	FILE* data = fopen("data", "r");

	expression.scan(data);    //задебажил этоооо

//	expression.print();

	fclose(data);

//	printf("\nВведите степень оптимизации:\n");		пока не готово
//	scanf("%d", &optimize);
//	printf("\n");

//	for(int i = 0; i < optimize; i++)
//	{
//		assert(!expression.optimize());
//	}

	assert(!dump_input(&expression));

	system("dot -Tgif -Oinput.gif input");

//Begin diff

	Node answer;

	data = fopen("answer", "w");

	expression.diff_step(data);

	/////

	fprintf(data, "$$$$$$$$$$$$$");

	fclose(data);

	data = fopen("answer", "r");
	
	answer.scan(data);

	fclose(data);
    

//	for(int i = 0; i < optimize; i++)
//	{
//		assert(!answer.optimize());             пока не готово
//	}


	assert(!dump_answer(&answer));

	system("dot -Tgif -Oanswer.gif answer_dump");

	printf("\nТа-даммм, а вот и производная по Х:\n");
	assert(!answer.print_postfix());
	printf("\n\n");

	return 0;
}

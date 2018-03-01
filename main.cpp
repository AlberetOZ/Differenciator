#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <iostream>
#include "Node.h"



int main()
{
	int number_input = 0;
	int step_operand = 0;
	char data_operand[MAX_LINE] = {0};
	char data_number[MAX_LINE] = {0};

	Node test;

	for(; scanf("%s %s", data_operand + 1, data_number) == 2; number_input++)
	{
		data_operand[0] = '\"';
		
		for(step_operand = 0; step_operand < number_input; step_operand++)
		{

			data_operand[2 + step_operand] = ' ';


		}
		data_operand[number_input + 2] = '\"'; 

		test.add(data_operand, data_number);



	}



	test.dump();

	return 0;
}

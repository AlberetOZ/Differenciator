// тут основа дифференциатора
///////////////

int Node::diff_step(FILE* data)
{
	assert(data);

	if((left == NULL) && (right == NULL))
	{

		if(strstr(value, "X") != NULL || strstr(value, "x") != NULL)
		{
			
			if(value[0] == 'x' || value[0] == 'X')
				fprintf(data, "( 1 ) ");
			else
			{
				int Nx = 0;
				sscanf(value, "%d", &Nx);
				fprintf(data, "( %d ) ", Nx);
			}
		}
		else
			fprintf(data, "( 0 ) ");




	}
	else
	{

		assert(!diff_switch(data));







	}

	return 0;
}


int Node::diff_switch(FILE* data)
{


	if(strcmp(value, "+") == 0)
	{
		fprintf(data, "( + ");
		(*left).diff_step(data);
		(*right).diff_step(data);

		fprintf(data, ") ");
	}
	else
	if(strcmp(value, "-") == 0)
	{
		fprintf(data, "( - ");
		(*left).diff_step(data);
		(*right).diff_step(data);

		fprintf(data, ") ");
	}
	else
	if(strcmp(value, "sin") == 0)
	{
		fprintf(data, "( * ( cos ");
		(*left).print(data); 

		fprintf(data, ") ");


		(*left).diff_step(data);

		fprintf(data, ") ");
	}
	else
	if(strcmp(value, "cos") == 0)
	{
		fprintf(data, "( * ( * ( -1 ) ( sin ");
		(*left).print(data);

		fprintf(data, ") ) ");
		(*left).diff_step(data);
		fprintf(data, ") ");
	}
	else
	if((strcmp(value, "ln") == 0) || (strcmp(value, "Ln") == 0))
	{
		fprintf(data, "( * ( / ( 1 ) ");
		(*left).print(data);
		fprintf(data, ") ");
		(*left).diff_step(data);

		fprintf(data, ") ");
	}
	else
	if(strcmp(value, "*") == 0)
	{
		fprintf(data, "( + ( * ");
		(*left).diff_step(data);
		(*right).print(data);
		fprintf(data, ") ( * ");
		(*right).diff_step(data);
		(*left).print(data);
		fprintf(data, ") ) ");

	}



	else


	{
		printf("\n!!!!!!!!!!!!!!!!!!!\nТут проблема с выражением, встречено: %s, я такое не дифференцирую((((\n!!!!!!!!!!!!!!!!\n", value);
		assert(!"unknown expression");

	}
	

	return 0;
}

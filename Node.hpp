#define MAX_LINE 100

const static int CANARY = rand() % (time(0)) + 1;	//	Канарейки

typedef char*  Data;

class  Node
{
private:
	int canary1 = CANARY; 
	Data value;		 //      данные в узле	
	class Node* left;	 //      левая ветвь
	class Node* right;	 //      правая ветвь
	class Node* prev;	 //	 родитель (предыдущий узел)
public:
	Node();			 //	конструктор
	~Node();		 //	деструктор

	

	void scan(FILE*);	 //	считывание из файла базы в дерево
	void scan_step(FILE*);	 //	шаг считывания узла дерева	
	void Check();		 //	проверка дерева
	class Node* down_right();//	идёт до нижнего правой ветви, возвращает указатель на неё
	void add(Data, Data);	 //	добавить ветку, уже существующее значение не добавляется
	void print(FILE*);		 //	инфексный вывод дерева	
	void reset();		 //	обнуление(сброс) дерева
	size_t mass();		 //	колво узлов дерева
	void dump(FILE*);	 //	печать дерева через Dot
	void dump_in_file(FILE*, int);//	вывод дерева в файл dota2 на языке dot
//	void print_links(FILE*, int);//		распечатка костылей для dota

	int diff_step(FILE*);	 //	шаг дифференцирования
	int diff_switch(FILE*);	 //	свич для разных производных

	int print_postfix();	 //	принт в stdout выражения в норм виде

	int optimize();		 //	оптимизация выражения
private:
	int canary2 = CANARY;
};


void Node::Check()
{
	assert(canary1 == CANARY);
	assert(canary2 == CANARY);	
	
	assert(&value);
	if(left != NULL)
		(*left).Check();
	if(right != NULL)
		(*right).Check();
}



Node::Node ()
{
	value = (char*)calloc(1, MAX_LINE);
	*value = '0';
	left = NULL;
	right = NULL;
	
	Node::Check();


}

size_t Node::mass()
{
	size_t mas = 1;
	if(left != NULL)
		mas += (*left).mass();
	if(right != NULL)
		mas += (*right).mass();
	return mas;
}

void Node::reset()
{
	if(left != NULL)
	{
		(*left).~Node();
		free(left);
	}
	if(right != NULL)
	{
		(*right).~Node();
		free(right);
	}
	free(value);
	left = NULL;
	right = NULL;
	Node::Check();

}

class Node* Node::down_right()
{
	if(right == NULL)
		return this;
	else
		return (*right).down_right();



}

void Node::add(Data operand, Data number)
{
	Node::Check();

	class Node* right_Node = down_right();

	right_Node -> right = (Node*)calloc(1, sizeof(class Node));
	right_Node -> right -> canary1 = CANARY;
	right_Node -> right -> canary2 = CANARY;
	right_Node -> right -> value = (char*)calloc(1, MAX_LINE);
	stpcpy(right_Node -> right -> value, number);

	right_Node -> left = (Node*)calloc(1, sizeof(class Node));
	right_Node -> left -> canary1 = CANARY; 
	right_Node -> left -> canary2 = CANARY; 
	right_Node -> left -> value = (char*)calloc(1, MAX_LINE);
	stpcpy(right_Node -> left -> value, right_Node -> value);

	strcpy(right_Node -> value, operand);

	Node::Check();
}

void Node::print(FILE* data)
{
	fprintf(data, "( ");

	fprintf(data, "%s ", value);

	if(left != NULL)
		(*left).print(data);

	if(right != NULL)
		(*right).print(data);

	fprintf(data, ") ");
}



void Node::scan(FILE* data)
{


	assert(data);

	Node::scan_step(data);

	Node::Check();

}

void Node::scan_step(FILE* data)
{
	char step = '\0';

	fscanf(data, "%c%c", &step, &step);
	
	if(step == '(')
	{
		if(left == NULL)
		{
			
			left = (Node*)calloc(1, sizeof(class Node));
			left -> canary1 = CANARY;
			left -> canary2 = CANARY;
			left -> prev = this; 
			left -> value = (char*)calloc(1, MAX_LINE);
			(*left).Check();



			(*left).scan_step(data);
	
		}
		else
		{
			right = (Node*)calloc(1, sizeof(class Node));
			right -> canary1 = CANARY;
			right -> canary2 = CANARY;
			right -> prev = this;
			right -> value = (char*)calloc(1, MAX_LINE);
			(*right).Check();
			(*right).scan_step(data);
		}
	}
	else if(step == ')')
		(*prev).scan_step(data);
	else if(step == '$')
		ungetc(step , data);
	else
	{
		ungetc(step, data);
		fscanf(data, "%s", value);
		Node::scan_step(data);

	}
	
}

void Node::dump(FILE* dota)
{
	Node::Check();	

	assert(dota);
	
	fprintf(dota, "digraph dota_one_love {\nbgcolor=\"white\";\nresolution=720;\n");

	Node::dump_in_file(dota, 0);


	fprintf(dota, "\n}\n");

}

//void Node::print_links(FILE* dota, int dump_number)
//{
//	Node::Check();
//
//	for(int i = 0; i < dump_number; i++)
//	{
//		fprintf(dota, " ");
//	}
//}

void Node::dump_in_file(FILE* dota, int dump_number)
{
	Node::Check();

	fprintf(dota, "\t\"");
//	print_links(dota, dump_number);
	fprintf(dota, "%p", value);
//	print_links(dota, dump_number);
	fprintf(dota, "\"[label = \"%s\"][color = \"red\"] [fillcolor = \"red\"][fontcolor = blue] ;\n", value);


	if(left != NULL)
	{
		int step = rand() % (strlen(value)*3) + 1;

		fprintf(dota, "\t\"");
//		print_links(dota, dump_number); 
       		fprintf(dota, "%p", value);
//		print_links(dota, dump_number);
		fprintf(dota, "\" -> \"");
//		print_links(dota, dump_number + step);
		fprintf(dota, "%p", left -> value);
//		print_links(dota, dump_number + step);
		fprintf(dota, "\"[color = \"red\"] [fillcolor = \"blue\"] ;\n");
		



		(*left).dump_in_file(dota, dump_number + step);
	}
	if(right != NULL)
	{
		int step = rand() % (strlen(value)*2) + 1;

		fprintf(dota, "\t\"");
  //      	print_links(dota, dump_number);
        	fprintf(dota, "%p", value);
//		print_links(dota, dump_number);
		fprintf(dota, "\" -> \"");
  //          	print_links(dota, dump_number + step+1);
            
           	fprintf(dota, "%p", right -> value);
//		print_links(dota, dump_number + step+1);
		fprintf( dota, "\"[color = \"red\"] [fillcolor = \"blue\"] ;\n");
            
		(*right).dump_in_file(dota, dump_number + step+1);
	}


}

int Node::print_postfix()
{

	Node::Check();

	if((strcmp(value, "sin") == 0) || (strcmp(value, "cos") == 0) || (strcmp(value, "ln") == 0) || (strcmp(value, "tg") == 0) || (strcmp(value, "ctg") == 0) || (strcmp(value, "exp") == 0))
	{
		printf("%s( ", value);

		if(left != NULL)
			(*left).print_postfix();

		printf(") ");


	}
	else
	if(strcmp(value, "-") == 0 || strcmp(value, "+") == 0)
	{

		if(left != NULL)
		{
			(*left).print_postfix();
		}

		printf("%s ", value);

		if(right != NULL)
		{
			(*right).print_postfix();
		}
	}
	else
	{

		if(left != NULL)
		{
			printf("( ");
			(*left).print_postfix();
			printf(") ");
		}

		printf("%s ", value);

		if(right != NULL)
		{
			printf("( ");
			(*right).print_postfix();
			printf(") ");
		}
	}


	return 0;
}

int Node::optimize()
{
	Node::Check();

	if(left != NULL && right != NULL)
	{
		char* found_left = NULL;
		char* found_right = NULL;
		long converted_left = strtol(left -> value, &found_left, 10);
		long converted_right = strtol(right -> value, &found_right, 10);

		if((strcmp(value, "+") == 0 || strcmp(value, "-") == 0) && (strcmp(left -> value, "0")) == 0 && (strcmp(right -> value, "0")) == 0)
		{
			value[0] = '0';
			value[1] = '\0';
			(*left).~Node();
			left = NULL;
			(*right).~Node();
			right = NULL;

		}
		else
		if((strcmp(value, "+") == 0 || strcmp(value, "-") == 0) && (strcmp(left -> value, "0")) == 0)
		{
			strcpy(value, right -> value);
			(*left).~Node();
			left = NULL;
			(*right).~Node();
			right = NULL;

		}
		else
		if((strcmp(value, "+") == 0 || strcmp(value, "-") == 0) && (strcmp(right -> value, "0")) == 0)
		{
			strcpy(value, left -> value);
			(*left).~Node();
			left = NULL;
			(*right).~Node();
			right = NULL;

		}
		else
		if(strcmp(value, "+") == 0 && (!*found_left) && (!*found_right))
		{
			sprintf(value, "%ld", converted_left+converted_right);

			
			(*left).~Node();
			left = NULL;
			(*right).~Node();
			right = NULL;


		}
		else
		if(strcmp(value, "-") == 0 && (!*found_left) && (!*found_right))
		{
			sprintf(value, "%ld", converted_left-converted_right);

			
			(*left).~Node();
			left = NULL;
			(*right).~Node();
			right = NULL;


		}


		else
		{
			assert(!(*left).optimize());
			assert(!(*right).optimize());
		}
	}
	else



	if(left != NULL)
		assert(!(*left).optimize());
	else

	if(right != NULL)
		assert(!(*right).optimize());

	return 0;
}



Node::~Node()
{
	Node::Check();	

	free(value);

	if(left != NULL)
	{
		(*left).~Node();
		free(left);
	}
	if(right != NULL)
	{
		(*right).~Node();
		free(right);

	}
}

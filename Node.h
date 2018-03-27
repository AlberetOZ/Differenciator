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

	

	void scan();				     //	считывание из файла базы дифференциатора
	void scan_step(FILE*);	 //	шаг считывания узла дерева	
	void Check();		 //	проверка дерева
	class Node* down_right();//	идёт до нижнего правой ветви, возвращает указатель на неё
	void add(Data, Data);	 //	добавить ветку, уже существующее значение не добавляется
	void print();		 //	инфексный вывод дерева	
	void reset();		 //	обнуление(сброс) дерева
	size_t mass();		 //	колво узлов дерева
	void dump(FILE*);	 //	печать дерева через Dot
	void dump_in_file(FILE*, int);//	вывод дерева в файл dota2 на языке dot
	void print_links(FILE*, int);//		распечатка костылей для dota
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

void Node::print()
{

	if(left != NULL)
		(*left).print();

	printf("%s ", value);


	if(right != NULL)
		(*right).print();


}



void Node::scan()
{

	FILE* data = fopen("data", "r");

	assert(data);

//	char temp = '\0';	

//	fscanf(data, "%c%c%s",  &temp, &temp,  value); 

	Node::scan_step(data);

	Node::Check();


	fclose(data);

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

void Node::print_links(FILE* dota, int dump_number)
{
	for(int i = 0; i < dump_number; i++)
	{
        	fprintf(dota, " ");
	}
}

void Node::dump_in_file(FILE* dota, int dump_number)
{
	fprintf(dota, "\t\"");
	print_links(dota, dump_number);
	fprintf(dota, "%s", value);
	print_links(dota, dump_number);
	fprintf(dota, "\"[color = \"red\"] [fillcolor = \"red\"][fontcolor = blue] ;\n");


	if(left != NULL)
	{
		fprintf(dota, "\t\"");
		print_links(dota, dump_number); 
       		fprintf(dota, "%s", value);
		print_links(dota, dump_number);
		fprintf(dota, "\" -> \"");
		print_links(dota, dump_number + 1);
		fprintf(dota, "%s", left -> value);
		print_links(dota, dump_number + 1);
		fprintf(dota, "\"[color = \"red\"] [fillcolor = \"blue\"] ;\n");
		



		(*left).dump_in_file(dota, dump_number + 1);
	}
	if(right != NULL)
	{
		fprintf(dota, "\t\"");
        	print_links(dota, dump_number);
        	fprintf(dota, "%s", value);
		print_links(dota, dump_number);
		fprintf(dota, "\" -> \"");
            	print_links(dota, dump_number + 2);
            
           	fprintf(dota, "%s", right -> value);
		print_links(dota, dump_number + 2);
		fprintf( dota, "\"[color = \"red\"] [fillcolor = \"blue\"] ;\n");
            
		(*right).dump_in_file(dota, dump_number + 2);
	}


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

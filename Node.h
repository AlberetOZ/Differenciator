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

	

	void scan();				     //	считывание из файла базы акинатора
	void scan_step(FILE*, class Node*);	     //	шаг считывания узла дерева	
	void Check();		 //	проверка дерева
	class Node* down_right();//	идёт до нижнего правой ветви, возвращает указатель на неё
	void add(Data, Data);	 //	добавить ветку, уже существующее значение не добавляется
	void print();		 //	инфексный вывод дерева	
	void reset();		 //	обнуление(сброс) дерева
	size_t mass();		 //	колво узлов дерева
	void dump();		 //	печать дерева через Dot
	void dump_in_file(FILE*);//	вывод дерева в файл dota2 на языкке dot
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

	char temp = '\0';	

//	fscanf(data, "%c%c%s",  &temp, &temp,  value); 

	Node::scan_step(data, this);

	Node::Check();


	fclose(data);

}

void Node::scan_step(FILE* data, class Node* root)
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
			left -> prev = root; 
			left -> value = (char*)calloc(1, MAX_LINE);
			(*left).Check();



			(*left).scan_step(data, left);
	
		}
		else
		{
			right = (Node*)calloc(1, sizeof(class Node));
			right -> canary1 = CANARY;
			right -> canary2 = CANARY;
			right -> prev = root;
			right -> value = (char*)calloc(1, MAX_LINE);
			(*right).Check();
			(*right).scan_step(data, right);
		}
	}
	else if(step == ')')
		(*prev).scan_step(data, prev);
	else if(step == '$')
		ungetc(step , data);
	else
	{
		ungetc(step, data);
		fscanf(data, "%s", value);
		Node::scan_step(data, root);

	}
	
}

void Node::dump()
{
	Node::Check();	

	FILE* dota = fopen("dota2", "w");
	assert(dota);
	
	fprintf(dota, "digraph dota_one_love {\nbgcolor=\"white\";\nresolution=720;\n");

	Node::dump_in_file(dota);


	fprintf(dota, "\n}\n");

	fclose(dota);

	system("dot -Tgif -Odota.gif dota2");

}

void Node::dump_in_file(FILE* dota)
{
	fprintf(dota, "\t\"%s\"[color = \"red\"] [fillcolor = \"red\"][fontcolor = blue] ;\n", value);
	if(left != NULL)
	{
		fprintf(dota, "\t\"%s\" -> \"%s\"[color = \"red\"] [fillcolor = \"blue\"] ;\n", value, left -> value);
		(*left).dump_in_file(dota);
	}
	if(right != 0)
	{
		fprintf(dota, "\t\"%s\" -> \"%s\"[color = \"red\"] [fillcolor = \"blue\"] ;\n", value, right -> value);
		(*right).dump_in_file(dota);
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

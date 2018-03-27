//
//  main.c
//
//  Created by Beda Diana on 24.03.2018.
//  Copyright © 2018 Beda Diana. All rights reserved.
//
#define N 10000
typedef int Data_Stack;

struct Stack {
    int n;
    Data_Stack a[N];
};

void stack_create(struct Stack * s)
{
    for(int i = 0; i < N; i++)
    {
        s -> a[i] = 0;
    }
    s -> n = 0;
}

void stack_push(struct Stack * s, Data_Stack x)
{
    s -> a[s -> n] = x;
    s -> n++;
}
Data_Stack stack_pop(struct Stack * s)
{
    s -> n--;
    return s -> a[s -> n];
}
Data_Stack stack_get(struct Stack * s)
{
    
    return s -> a[s -> n-1];
}
void stack_print(struct Stack * s)
{
    if(s -> n == 0)
    {
        printf("Empty stack");
    }
    else
    {
        for( int i = 0; i < s -> n; i++)
        {
            printf("%d ", s -> a[i]);
        }
    }
    printf("\n");
}
int  stack_size(struct Stack * s)
{
    printf("%d\n", s -> n-1);
    return 0;
}

void stack_clear(struct Stack * s)
{
    for(int i = 0; i < N; i++)
    {
        s -> a[i] = 0;
    }
    s -> n = 0;
}


int check_scobki(FILE* data)
{
//    fclose(data);
    data = fopen("data", "r");
    char m = 0;
    struct Stack * s = (Stack*)calloc(sizeof(struct Stack),1);
    stack_create(s);

    fscanf(data, "%c%c", &m, &m);
    
    for(; fscanf(data, "%c", &m) == 1;)
    {
        if( m == '('  || m == '[' || m == '{' || m == '<')
                stack_push(s,(m));
     ///////////////////////////
        if( m == ')')
        {
            if(stack_pop(s) != '(')
            {  
                free(s);
		fclose(data);
                return 0;
            }
        }
    ///////////////////////////////
        if( m == ']')
        {
            if(stack_pop(s) != '[')
            { 
                free(s);
		fclose(data);
                return 0;
            }
        }
    //////////////////////////////
        if( m == '}')
        {
            if(stack_pop(s) != '{')
            {  
                free(s);
		fclose(data);
                return 0;
            }
        }
    /////////////////////////////////
        if( m == '>')
        {
            if(stack_pop(s) != '<')
            {    
                free(s);
		fclose(data);
                return 0;
            }
        }

    }
    fclose(data);
    if(s -> n == 0)
    {
	free(s);
        return 1;
    }
    else
    {
	free(s);
        return 0;

    }
}

































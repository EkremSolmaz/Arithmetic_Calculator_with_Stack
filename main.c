#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct STACK
{
    int top;
    char st[SIZE];

    int topInt;
    int stInt[SIZE];
}STACK;




//Char deðerleri icin stack fonlsiyonlari

void Initialize(STACK *s)
{
    s->top = 0;
    s->topInt = 0;
}

int IsEmpty(STACK s)
{
    if(s.top == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int IsFull(STACK s)
{
    if(s.top == SIZE){
        return 1;
    }
    else{
        return 0;
    }
}

void Push(STACK *s, char value)
{
    if(IsFull(*s)){
        printf("Stack is full.\n");
    }
    else{
        s->st[s->top] = value;
        s->top++;
    }
}

char Pop(STACK *s)
{
    if(IsEmpty(*s)){
        printf("Stack is empty.\n");
    }
    else{
        return s->st[--(s->top)];
    }
}

char WhatNext(STACK *s)
{
    if(IsEmpty(*s)){
        printf("Stack is empty.\n");
    }
    else{
        return s->st[s->top-1];
    }
}


// Integer deðerleri icin stack fonsiyonlari

int IsEmptyInt(STACK s)
{
    if(s.topInt == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int IsFullInt(STACK s)
{
    if(s.topInt == SIZE){
        return 1;
    }
    else{
        return 0;
    }
}

void PushInt(STACK *s, int value)
{
    if(IsFullInt(*s)){
        printf("Stack is full.\n");
    }
    else{
        s->stInt[s->topInt] = value;
        (s->topInt)++;
    }
}

int PopInt(STACK *s)
{
    if(IsEmptyInt(*s)){
        printf("\nStack is empty.\n");
    }
    else{
        return s->stInt[--(s->topInt)];
    }
}

int WhatNextInt(STACK *s)
{
    if(IsEmptyInt(*s)){
        printf("Stack is empty.\n");
    }
    else{
        return s->stInt[s->topInt-1];
    }
}


int Precedence(char c)
{
    printf("\nOperator : %c\n", c);

    if(c == '+' || c == '-'){
        return 1;
    }
    else if(c == '*' || c == '/'){
        return 2;
    }
    else{
        return -1;
    }

}


char * ToPostfix(char infix[])
{

    char postfix[100];
    int p = 0;

    STACK * stack;
    Initialize(stack);

    char c = infix[0];
    int i = 0;



    while(c != ';'){

        if(isalpha(c) || isdigit(c)){
            postfix[p++] = c;
            while(infix[i+1] != ' '){
                printf("%c to postfix.\n", infix[i]);
                postfix[p++] = infix[++i];
            }
            postfix[p++] = ' ';
            printf("%c to postfix.\n", c);
        }
        else if(c == '('){
            Push(stack, c);
            printf("%c pushed.\n", c);
        }
        else if(c == ')'){
            while(!IsEmpty(*stack) && WhatNext(stack) != '('){
                printf("%c to postfix.\n", WhatNext(stack));
                postfix[p++] = Pop(stack);
                postfix[p++] = ' ';

            }
            if(IsEmpty(*stack)){
                printf("Invalid Expression.AMK\n");
                return -1;
            }
            else{
                printf("%c Popped from stack to nothing.\n", WhatNext(stack));
                Pop(stack);

            }
        }
        else{
            while(!IsEmpty(*stack) && Precedence(c) <= Precedence(WhatNext(stack))){
                printf("%c to postfix.\n", WhatNext(stack));
                postfix[p++] = Pop(stack);
                postfix[p++] = ' ';

                }
                Push(stack, c);
                printf("%c pushed.\n", c);
        }


        i += 2;
        c = infix[i];
        printf("c = %c\n", c);


    }

    //Infix string bittigi icin her seyi pop ediyoruz.

    while(!IsEmpty(*stack)){
        printf("%c to postfix.\n", WhatNext(stack));
        postfix[p++] = Pop(stack);
        postfix[p++] = ' ';

    }


    postfix[p] = ';';
    postfix[p+1] = '\0';


    return postfix;
}

int SolvePostfix(char postfix[])
{

    //islemleri yapmak icin kullanacagým yýgýn.

    STACK * solveStack;
    solveStack = (STACK*) malloc(sizeof(STACK));
    Initialize(solveStack);

    //postfix ifadede ilerlemek icin kullanacagýz.
    int p = 0;
    char c = postfix[p];

    char integer[10];
    int digitCount = 0;

    //islemler icin kullanacagým int degýskenler
    int x, y;

    printf("X");

    while(c != ';'){

        if(isdigit(c)){
            while(postfix[p+1] != ' '){
            integer[digitCount++] = c;

            c = postfix[++p];

            }
            integer[digitCount++] = c;
            PushInt(solveStack, atoi(integer));
            printf("%d pushed to stack\n", atoi(integer));
            memset(integer, 0, 9);
            digitCount = 0;
        }
        else{
            y = PopInt(solveStack);
            x = PopInt(solveStack);
            printf("%d and %d popped\n", x, y);

            switch(c){

            case '+':
                PushInt(solveStack, x+y);
                printf("%d pushed to stack\n", x+y);
                break;

            case '-':
                PushInt(solveStack, x-y);
                printf("%d pushed to stack\n", x-y);
                break;

            case '*':
                PushInt(solveStack, x*y);
                printf("%d pushed to stack\n", x*y);
                break;

            case '/':
                PushInt(solveStack, x/y);
                printf("%d pushed to stack\n", x/y);
                break;


            }
        }

        p += 2;
        c = postfix[p];
    }


    return PopInt(solveStack);

}


int main()
{





    /*
    char op[100];
    printf("Operation :\n");
    gets(op);
    printf("\n");
    puts(op);

    strcpy(op, ToPostfix(op));

    printf("\n");
    puts(op);
    */




    /*
    char op[100] = "22 37 41 + * ;";

    int res = SolvePostfix(op);
    printf("\nResult : %d", res);

    */


    char op[100]= "3 * ( 13 - 7 ) / 2 ;";
    /*
    printf("Operation :\n");
    gets(op);
    printf("\n");
    */
    puts(op);

    strcpy(op, ToPostfix(op));
    printf("\n");
    puts(op);

    int res = SolvePostfix(op);
    printf("\nResult : %d", res);





    return 0;
}

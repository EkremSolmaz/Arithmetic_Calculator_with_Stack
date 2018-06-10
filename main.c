#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct
{
    int top;
    char st[SIZE];

    int topInt;
    int stInt[SIZE];
}STACK;




//Stack functions for stack operations with chars

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

void DisplayStack(STACK *s)
{
    if(IsEmpty(*s)){
        printf("Empty");
    }
    else{

        //Second stack to not lose data while printing
        STACK * temp;
        temp =(STACK*) malloc(sizeof(STACK));
        Initialize(temp);
        char c;

        while(!IsEmpty(*s)){
            c = Pop(s);

            Push(temp, c);
        }

        while(!IsEmpty(*temp)){
            c = Pop(temp);
            printf("%c ",c);
            Push(s, c);
        }



    }
}




// Stack functions for stack operations with integers

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


void DisplayStackInt(STACK *s)
{
    if(IsEmptyInt(*s)){
        printf("Empty");
    }
    else{

        //Second stack to not lose data while printing
        STACK * temp;
        temp = (STACK*) malloc(sizeof(STACK));
        Initialize(temp);
        int c;

        while(!IsEmptyInt(*s)){
            c = PopInt(s);

            PushInt(temp, c);
        }

        while(!IsEmptyInt(*temp)){
            c = PopInt(temp);
            printf("%d ",c);
            PushInt(s, c);
        }



    }
}



int Precedence(char c)
{
    //printf("\nOperator : %c\n", c);

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
    stack = (STACK*) malloc(sizeof(STACK));
    Initialize(stack);


    char c = infix[0];
    int i = 0;



    while(c != ';'){

        if(isalpha(c) || isdigit(c)){
            postfix[p++] = c;
            while(infix[i+1] != ' '){
                //printf("%c to postfix.\n", infix[i]);
                postfix[p++] = infix[++i];
            }
            postfix[p++] = ' ';
            //printf("%c to postfix.\n", c);
        }
        else if(c == '('){
            Push(stack, c);
            //printf("%c pushed.\n", c);
        }
        else if(c == ')'){
            while(!IsEmpty(*stack) && WhatNext(stack) != '('){
                //printf("%c to postfix.\n", WhatNext(stack));
                postfix[p++] = Pop(stack);
                postfix[p++] = ' ';

            }
            if(IsEmpty(*stack)){
                printf("Invalid Expression.AMK\n");
                return -1;
            }
            else{
                //printf("%c Popped from stack to nothing.\n", WhatNext(stack));
                Pop(stack);

            }
        }
        else{
            while(!IsEmpty(*stack) && Precedence(c) <= Precedence(WhatNext(stack))){
                //printf("%c to postfix.\n", WhatNext(stack));
                postfix[p++] = Pop(stack);
                postfix[p++] = ' ';

                }
                Push(stack, c);
                //printf("%c pushed.\n", c);
        }


        i += 2;
        c = infix[i];
        //printf("c = %c\n", c);

        printf("Postfix: %.*s \tStack:", p, postfix);
        DisplayStack(stack);
        printf("\n");



    }

    //Infix string bittigi icin her seyi pop ediyoruz.

    while(!IsEmpty(*stack)){
        //printf("%c to postfix.\n", WhatNext(stack));
        postfix[p++] = Pop(stack);
        postfix[p++] = ' ';

    }


    postfix[p] = ';';
    postfix[p+1] = '\0';


    return postfix;
}

int SolvePostfix(char postfix[], int alphabet[])
{

    //Stack needed to solve the operation in postfix form

    STACK * solveStack;
    solveStack = (STACK*) malloc(sizeof(STACK));
    Initialize(solveStack);

    //to travel in postfix string
    int p = 0;
    char c = postfix[p];

    char integer[10];
    int digitCount = 0;

    //variables to use when doing operations
    int x, y;


    while(c != ';'){

        if(isdigit(c)){
            while(postfix[p+1] != ' '){
            integer[digitCount++] = c;

            c = postfix[++p];

            }
            integer[digitCount++] = c;
            PushInt(solveStack, atoi(integer));
            //printf("%d pushed to stack\n", atoi(integer));
            memset(integer, 0, 9);
            digitCount = 0;
        }
        else if(isalpha(c)){
            PushInt(solveStack, alphabet[c - 97]);
            //printf("%c = %d pushed to stack\n", c, alphabet[c-97]);
        }
        else{
            y = PopInt(solveStack);
            x = PopInt(solveStack);
            //printf("%d and %d popped\n", x, y);

            switch(c){

            case '+':
                PushInt(solveStack, x+y);
                //printf("%d pushed to stack\n", x+y);
                break;

            case '-':
                PushInt(solveStack, x-y);
                //printf("%d pushed to stack\n", x-y);
                break;

            case '*':
                PushInt(solveStack, x*y);
                //printf("%d pushed to stack\n", x*y);
                break;

            case '/':
                PushInt(solveStack, x/y);
                //printf("%d pushed to stack\n", x/y);
                break;


            }
        }

        p += 2;
        c = postfix[p];


        printf("Stack: ");
        DisplayStackInt(solveStack);
        printf("\n");


    }


    return PopInt(solveStack);

}


int main()
{




    int alphabet[26] = {NULL};


    //Input file name
    FILE *fr;
    fr = fopen("input.txt", "r");


    int i = 0;
    char line[100], rightSide[100], postfix[100];
    char c;

    while(fgets(line, 100, fr) != NULL){



        printf("\nInfix operation:");
        puts(line);
        memcpy(rightSide, &line[4], 95);

        printf("\n\nInfix to Postfix:\n\n");

        strcpy(postfix, ToPostfix(rightSide));

        printf("\n\nPostfix Final Form:");
        puts(postfix);

        printf("\n\nSolving postfix:\n\n");

        alphabet[line[0] - 97] = SolvePostfix(postfix, alphabet);


        printf("\n%c = %d", line[0], alphabet[line[0]- 97]);

        memset(line, 0, 99);
        memset(rightSide, 0, 99);
        memset(postfix, 0, 99);
        i = 0;


        printf("\n-------------------------\n");


    }


    printf("RESULTS : \n");

    for(i = 0 ; i < 26 ; i++){

        if(alphabet[i] != NULL){

            printf("%c = %d\n", (char)(i+97) , alphabet[i]);

        }

    }






    return 0;
}













#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 100

int top = -1;
char stack[MAX];

// checking if stack is full
int isFull() {
    return top == MAX - 1;
}

// checking is stack is empty
int isEmpty() {
    return top == -1;
}

void push(char item) {
    if (isFull())
        return;
    top++;
    stack[top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
int pop() {
    if (isEmpty())
        return INT_MIN;

    return stack[top--];
}

int peek() {
    if (isEmpty())
        return INT_MIN;
    return stack[top];
}

int checkIfOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;

        case '^':
            return 3;
    }
    return -1;
}

int getPostfix(char *expression) {
    int i, j;

    for (i = 0, j = -1; expression[i]; ++i) {
        if (checkIfOperand(expression[i]))
            expression[++j] = expression[i];
        else if (expression[i] == '(')
            push(expression[i]);
        else if (expression[i] == ')') {
            while (!isEmpty() && peek() != '(')
                expression[++j] = pop();
            if (!isEmpty() && peek() != '(')
                return -1;
            else
                pop();
        } else {
            while (!isEmpty() && precedence(expression[i]) <= precedence(peek()))
                expression[++j] = pop();
            push(expression[i]);
        }
    }

    while (!isEmpty())
        expression[++j] = pop();

    expression[++j] = '\0';
}

void reverse(char *exp) {
    int size = strlen(exp);
    int j = size, i = 0;
    char temp[size];

    temp[j--] = '\0';
    while (exp[i] != '\0') {
        temp[j] = exp[i];
        j--;
        i++;
    }
    strcpy(exp, temp);
}

void brackets(char *exp) {
    int i = 0;
    while (exp[i] != '\0') {
        if (exp[i] == '(')
            exp[i] = ')';
        else if (exp[i] == ')')
            exp[i] = '(';
        i++;
    }
}

void InfixtoPrefix(char *exp) {
    int size = strlen(exp);
    reverse(exp);
    brackets(exp);
    getPostfix(exp);
    reverse(exp);
}

void getInput(char *expression) {
    printf("Enter the infix expression: ");
    fgets(expression, MAX, stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Removing newline character
}

int main() {
    printf("The infix is: ");

    char expression[MAX];
    getInput(expression);
    printf("%s\n", expression);

    InfixtoPrefix(expression);

    printf("The prefix is: ");
    printf("%s\n", expression);

    return 0;
}
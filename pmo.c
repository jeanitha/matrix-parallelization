////////////////////////////////Libraries///////////////////////////////////////
#include <assert.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
// for linux, use sysinfo (uncomment below and delete sysctl)
// #include <sys/sysinfo.h>

// for mac, use sysctl (uncomment below and delete sysinfo)
#include <sys/sysctl.h>

////////////////////////////////////////////////////////////////////////////////

////////////////////////////GLOBAL VARIABLES/STRUCTS////////////////////////////
/*
  statement stores the whole equation to solve
*/
char statement[30];

/*
  operation stores all the operations found in the statement.
  Including '+', '-', and '*'
*/
char operation[11];

/*
  matrix count
*/
int totalMatrix = 0;

typedef struct
{
  int rows;
  int cols;
  int **data;
} Matrix;

typedef struct
{
  Matrix *matrix;
  char operation;
} Expression;

typedef struct
{
  Expression *expressions;
  int top;
  int capacity;
} Stack;

/*
  struct for the arguments of thread functions
*/
struct arg
{
  Matrix *matrix_1;
  Matrix *matrix_2;
  Matrix *matrix_result;
  int i;
  int j;
  int max;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////FUNCTIONS///////////////////////////////////////

void append(char *s, char c)
{
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
}
/*
scan the very first statements in input files
*/
void scanStatement()
{
  scanf("%s", statement);

  int i = 0;
  while (statement[i])
  {
    if (statement[i] == '*' || statement[i] == '-' || statement[i] == '+')
    {
      append(operation, statement[i]);
    }
    else
    {
      totalMatrix++;
    }
    i++;
  }
}
/*
  loop through every row and col to print matrix
*/
void printMatrix(Matrix *matrix)
{
  printf("%d\t%d\n", matrix->rows, matrix->cols);
  for (int m = 0; m < matrix->rows; m++)
  {
    for (int n = 0; n < matrix->cols; n++)
    {
      printf("%d\t", matrix->data[m][n]);
    }
    printf("\n");
  }
  printf("\n");
} 

/*
thread function for add()
*/
void *addFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  Matrix *matrix_1 = params->matrix_1;
  Matrix *matrix_2 = params->matrix_2;
  int param_i = params->i;
  int max = params->max;
  for (int i = param_i; i < max; i++)
  {
    for (int j = 0; j < matrix_1->cols; j++)
    {
      matrix_1->data[i][j] = matrix_1->data[i][j] + matrix_2->data[i][j];
    }
  }
  return NULL;
}

/*
  add two matrix, matrix_1 is replaced with the resulting addition
  used 3 threads for each thirds of the rows
*/
void add(Matrix *matrix_1, Matrix *matrix_2)
{
  pthread_t thr[4];
  struct arg args[4];

  int third = matrix_1->rows / 4;
  args[0].i = 0;
  args[0].max = third;
  args[0].matrix_1 = matrix_1;
  args[0].matrix_2 = matrix_2;
  

  args[1].i = third;
  args[1].max = third * 2;
  args[1].matrix_1 = matrix_1;
  args[1].matrix_2 = matrix_2;

  args[2].i = third * 2;
  args[2].max = third * 3;
  args[2].matrix_1 = matrix_1;
  args[2].matrix_2 = matrix_2;

  args[3].i = third * 3;
  args[3].max = matrix_1->rows;
  args[3].matrix_1 = matrix_1;
  args[3].matrix_2 = matrix_2;

  pthread_create(&thr[0], NULL, addFunc, (void *)&args[0]);
  pthread_create(&thr[1], NULL, addFunc, (void *)&args[1]);
  pthread_create(&thr[2], NULL, addFunc, (void *)&args[2]);
  pthread_create(&thr[3], NULL, addFunc, (void *)&args[3]);
  pthread_join(thr[0], NULL);
  pthread_join(thr[1], NULL);
  pthread_join(thr[2], NULL);
  pthread_join(thr[3], NULL);
}

/*
thread function for subtract()
*/
void *subtractFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  Matrix *matrix_1 = params->matrix_1;
  Matrix *matrix_2 = params->matrix_2;
  int param_i = params->i;
  int max = params->max;
  for (int i = param_i; i < max; i++)
  {
    for (int j = 0; j < matrix_1->cols; j++)
    {
      matrix_1->data[i][j] = matrix_1->data[i][j] - matrix_2->data[i][j];
    }
  }
  return NULL;
}

/*
  subtract two matrix, matrix_1 is replaced with the resulting subtraction
  used 3 threads for each thirds of the rows
*/
void subtract(Matrix *matrix_1, Matrix *matrix_2)
{
  pthread_t thr[4];
  struct arg args[4];

  int third = matrix_1->rows / 4;
  args[0].i = 0;
  args[0].max = third;
  args[0].matrix_1 = matrix_1;
  args[0].matrix_2 = matrix_2;

  args[1].i = third;
  args[1].max = third * 2;
  args[1].matrix_1 = matrix_1;
  args[1].matrix_2 = matrix_2;

  args[2].i = third * 2;
  args[2].max = third * 3;
  args[2].matrix_1 = matrix_1;
  args[2].matrix_2 = matrix_2;

  args[3].i = third * 3;
  args[3].max = matrix_1->rows;
  args[3].matrix_1 = matrix_1;
  args[3].matrix_2 = matrix_2;

  pthread_create(&thr[0], NULL, subtractFunc, (void *)&args[0]);
  pthread_create(&thr[1], NULL, subtractFunc, (void *)&args[1]);
  pthread_create(&thr[2], NULL, subtractFunc, (void *)&args[2]);
  pthread_create(&thr[3], NULL, subtractFunc, (void *)&args[3]);
  pthread_join(thr[0], NULL);
  pthread_join(thr[1], NULL);
  pthread_join(thr[2], NULL);
  pthread_join(thr[3], NULL);
}

/*
thread function for multiply_multithread()
*/
void *multiplyFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  Matrix *matrix_1 = params->matrix_1;
  Matrix *matrix_2 = params->matrix_2;
  Matrix *matrix_result = params->matrix_result;
  int param_i = params->i;
  int max = params->max;

  for (int i = param_i; i < max; i++)
  {
    for (int j = 0; j < matrix_2->cols; j++)
    {
      for (int p = 0; p < matrix_1->cols; p++)
      {
        matrix_result->data[i][j] = matrix_result->data[i][j] + matrix_1->data[i][p] * matrix_2->data[p][j];
      }
    }
  }
  return NULL;
}
/*
  Multiply function. columns_1 = rows_2 hence no need for rows_2 as parameters.
  These two are refered as 'p' in the project document
  Result of the multiplication is placed in matrix_result
  used 3 threads for each thirds of the rows
*/
void multiply_multithread(Matrix *matrix_1, Matrix *matrix_2, Matrix *matrix_result)
{
  pthread_t thr[4];
  struct arg args[4];

  int third = matrix_1->rows / 4;
  args[0].i = 0;
  args[0].max = third;
  args[0].matrix_1 = matrix_1;
  args[0].matrix_2 = matrix_2;
  args[0].matrix_result = matrix_result;

  args[1].i = third;
  args[1].max = third * 2;
  args[1].matrix_1 = matrix_1;
  args[1].matrix_2 = matrix_2;
  args[1].matrix_result = matrix_result;

  args[2].i = third * 2;
  args[2].max = third * 3;
  args[2].matrix_1 = matrix_1;
  args[2].matrix_2 = matrix_2;
  args[2].matrix_result = matrix_result;

  args[3].i = third * 3;
  args[3].max = matrix_1->rows;
  args[3].matrix_1 = matrix_1;
  args[3].matrix_2 = matrix_2;
  args[3].matrix_result = matrix_result;

  pthread_create(&thr[0], NULL, multiplyFunc, (void *)&args[0]);
  pthread_create(&thr[1], NULL, multiplyFunc, (void *)&args[1]);
  pthread_create(&thr[2], NULL, multiplyFunc, (void *)&args[2]);
  pthread_create(&thr[3], NULL, multiplyFunc, (void *)&args[3]);
  pthread_join(thr[0], NULL);
  pthread_join(thr[1], NULL);
  pthread_join(thr[2], NULL);
  pthread_join(thr[3], NULL);
}

//////////////////////////////////////////////////////////////////////////////

Matrix *initMatrix(int rows, int cols)
{
  // Allocate memory for the matrix structure
  Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));

  // Set the number of rows and columns
  matrix->rows = rows;
  matrix->cols = cols;

  // Allocate memory for the matrix data
  matrix->data = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++)
  {
    matrix->data[i] = (int *)malloc(cols * sizeof(int));
  }

  return matrix;
}

void pushOperator(Stack *stack, char operator)
{
  if (stack->top == stack->capacity - 1)
  {
    printf("Operator Stack Overflow\n");
    return;
  }
  stack->expressions[++stack->top].operation = operator;
}

char popOperator(Stack *stack)
{
  if (stack->top == -1)
  {
    printf("Operator Stack Underflow\n");
    return '\0';
  }
  return stack->expressions[stack->top--].operation;
}

char getTopOperator(const Stack *stack)
{
  return stack->expressions[stack->top].operation;
}

void pushMatrix(Stack *stack, Matrix *matrix)
{
  stack->expressions[++stack->top].matrix = matrix;
}

Matrix *popMatrix(Stack *stack)
{
  return stack->expressions[stack->top--].matrix;
}

int getPriority(char operator)
{
  switch (operator)
  {
  case '*':
    return 3;
  case '+':
    return 1;
  case '-':
    return 2;
  default:
    return 0;
  }
}

int isOperator(char c)
{
  if (c == '*' || c == '+' || c == '-')
  {
    return 1;
  }
  return 0;
}

bool isNotEmpty(const Stack *stack)
{
  return (stack->top != -1);
}
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////MAIN FUNCTION//////////////////////////////////
int main()
{
  scanStatement();

  // Initialize Matrix stack & Operator stack
  Stack matrixStack;
  matrixStack.capacity = totalMatrix;
  matrixStack.top = -1;
  matrixStack.expressions = (Expression *)malloc(matrixStack.capacity * sizeof(Expression));

  Stack operatorStack;
  operatorStack.capacity = sizeof(operation);
  operatorStack.top = -1;
  operatorStack.expressions = (Expression *)malloc(operatorStack.capacity * sizeof(Expression));

  // Create matrices
  Matrix *matrices[totalMatrix];
  for (int i = 0; i < totalMatrix; i++)
  {
    int rows, cols;
    scanf("%d\t%d", &rows, &cols);

    Matrix *matrix = initMatrix(rows, cols);
    for (int m = 0; m < rows; m++)
    {
      for (int n = 0; n < cols; n++)
      {
        scanf("%d", &(matrix->data[m][n]));
      }
    }
    matrices[i] = matrix;
  }

  // Add the first 2 characters character into stack
  int numMat = 0;
  pushMatrix(&matrixStack, matrices[numMat]);
  pushOperator(&operatorStack, statement[1]);

  // Evaluate the rest of expression & do multiplication
  for (int i = 2; i < strlen(statement); i++)
  {
    char currentChar = statement[i];

    // If current operator > top stack
    if ((isOperator(currentChar) == 1) && (getPriority(currentChar) > getPriority(getTopOperator(&operatorStack))))
    {
      pushOperator(&operatorStack, currentChar);
    }
    else if ((isOperator(currentChar) == 1))
    {
      while (getPriority(currentChar) <= getPriority(getTopOperator(&operatorStack)) && isNotEmpty(&operatorStack))
      {
        Matrix *matrix_first = popMatrix(&matrixStack);
        Matrix *matrix_second = popMatrix(&matrixStack);

        int cur = popOperator(&operatorStack);
        if (cur == '*')
        {
          Matrix *matrix_result = initMatrix(matrix_second->rows, matrix_first->cols);
          multiply_multithread(matrix_second, matrix_first, matrix_result);
          pushMatrix(&matrixStack, matrix_result);
        }
        else if (cur == '-')
        {
          subtract(matrix_second, matrix_first);
          pushMatrix(&matrixStack, matrix_second);
        }
        else if (cur == '+')
        {
          add(matrix_first, matrix_second);
          pushMatrix(&matrixStack, matrix_first);
        }
      }
      pushOperator(&operatorStack, currentChar);
    }

    // If current character is a matrix
    else if (isalpha(currentChar) != 0)
    {
      pushMatrix(&matrixStack, matrices[++numMat]);
    }
  }

  // Repeat popping operators
  while (isNotEmpty(&operatorStack))
  {
    Matrix *matrix_first = popMatrix(&matrixStack);
    Matrix *matrix_second = popMatrix(&matrixStack);

    char op = popOperator(&operatorStack);
    if (op == '*')
    {
      Matrix *matrix_result = initMatrix(matrix_second->rows, matrix_first->cols);
      multiply_multithread(matrix_second, matrix_first, matrix_result);
      pushMatrix(&matrixStack, matrix_result);
    }
    else if (op == '+')
    {
      add(matrix_first, matrix_second);
      pushMatrix(&matrixStack, matrix_first);
    }
    else if (op == '-')
    {
      subtract(matrix_second, matrix_first);
      pushMatrix(&matrixStack, matrix_second);
    }
  }

  // print the final result
  printMatrix(popMatrix(&matrixStack));

  return 0;
}
////////////////////////////////////////////////////////////////////////////////

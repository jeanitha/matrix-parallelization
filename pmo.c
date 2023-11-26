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
  holds all the matrixes (A,B,C,D,...)
*/
char matrix[11];

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

struct arg
{
  Matrix *matrix_1;
  Matrix *matrix_2;
  Matrix *matrix_result;
  int i;
  int j;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////FUNCTIONS///////////////////////////////////////

void append(char *s, char c)
{
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
}

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
      append(matrix, statement[i]);
      totalMatrix++;
    }
    i++;
  }
  // puts(operation);
  // puts(matrix);
  // printf("%d", totalMatrix);
}

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
arguments struct are:
int (*matrix_1)[matrix_1_column], int (*matrix_2)[matrix_2_column], int i, int columns
*/
void *addFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  Matrix *matrix_1 = params->matrix_1;
  Matrix *matrix_2 = params->matrix_2;
  int i = params->i;

  for (int j = 0; j < matrix_1->cols; j++)
  {
    matrix_1->data[i][j] = matrix_1->data[i][j] + matrix_2->data[i][j];
  }
  return NULL;
}

/*
  add two matrix, matrix_1 is replaced with the resulting addition
*/
void add(Matrix *matrix_1, Matrix *matrix_2)
{
  pthread_t thr[matrix_1->rows];
  struct arg args[matrix_1->rows];

  for (int i = 0; i < matrix_1->rows; i++)
  {
    args[i].i = i;
    args[i].matrix_1 = matrix_1;
    args[i].matrix_2 = matrix_2;
    pthread_create(&thr[i], NULL, addFunc, (void *)&args[i]);
  }

  for (int i = 0; i < matrix_1->rows; i++)
  {
    pthread_join(thr[i], NULL);
  }
}

/*
arguments struct are:
int (*matrix_1)[matrix_1_column], int (*matrix_2)[matrix_2_column], int i, int columns
*/
void *subtractFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  Matrix *matrix_1 = params->matrix_1;
  Matrix *matrix_2 = params->matrix_2;
  int i = params->i;
  int columns = matrix_1->cols;

  for (int j = 0; j < columns; j++)
  {
    matrix_1->data[i][j] = matrix_1->data[i][j] - matrix_2->data[i][j];
  }

  return NULL;
}

/*
  subtract two matrix, matrix_1 is replaced with the resulting subtraction
*/
void subtract(Matrix *matrix_1, Matrix *matrix_2)
{
  pthread_t thr[matrix_1->rows];
  struct arg args[matrix_1->rows];

  for (int i = 0; i < matrix_1->rows; i++)
  {
    args[i].i = i;
    args[i].matrix_1 = matrix_1;
    args[i].matrix_2 = matrix_2;
    pthread_create(&thr[i], NULL, subtractFunc, (void *)&args[i]);
  }

  for (int i = 0; i < matrix_1->rows; i++)
  {
    pthread_join(thr[i], NULL);
  }
}

void *multiplyFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  Matrix *matrix_1 = params->matrix_1;
  Matrix *matrix_2 = params->matrix_2;
  Matrix *matrix_result = params->matrix_result;
  int i = params->i;
  for (int j = 0; j < matrix_2->cols; j++)
  {
    for (int p = 0; p < matrix_1->cols; p++)
    {
      matrix_result->data[i][j] = matrix_result->data[i][j] + matrix_1->data[i][p] * matrix_2->data[p][j];
    }
  }
  return NULL;
}
/*
  Multiply function. columns_1 = rows_2 hence no need for rows_2 as parameters.
  These two are refered as 'p' in the document
*/
void multiply_multithread(Matrix *matrix_1, Matrix *matrix_2, Matrix *matrix_result)
{
  pthread_t thr[matrix_1->rows];
  struct arg args[matrix_1->rows];
  for (int i = 0; i < matrix_1->rows; i++)
  {
    args[i].i = i;
    args[i].matrix_1 = matrix_1;
    args[i].matrix_2 = matrix_2;
    args[i].matrix_result = matrix_result;
    pthread_create(&thr[i], NULL, multiplyFunc, (void *)&args[i]);
  }
  for (int i = 0; i < matrix_1->rows; i++)
  {
    pthread_join(thr[i], NULL);
  }
}

void multiply(Matrix *matrix_1, Matrix *matrix_2, Matrix *matrix_result)
{
  for (int i = 0; i < matrix_1->rows; i++)
  {
    for (int j = 0; j < matrix_2->cols; j++)
    {
      for (int p = 0; p < matrix_1->cols; p++)
      {
        matrix_result->data[i][j] = matrix_result->data[i][j] + matrix_1->data[i][p] * matrix_2->data[p][j];
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////

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

void freeMatrix(Matrix *matrix)
{
  if (matrix == NULL)
    return;

  // Free the memory for the matrix data
  for (int i = 0; i < matrix->rows; i++)
  {
    free(matrix->data[i]);
  }
  free(matrix->data);

  // Free the memory for the matrix structure
  free(matrix);
}

Matrix *readMatrix(int rows, int cols)
{
  Matrix *matrix = initMatrix(rows, cols);

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      scanf("%d", &(matrix->data[i][j]));
    }
  }

  return matrix;
}

void pushOperator(Stack* stack, char operator)
{
  if (stack->top == stack->capacity -1){
    printf("Operator Stack Overflow\n");
    return;
  }
  stack->expressions[++stack->top].operation = operator;
}

char popOperator(Stack* stack)
{
  if (stack->top == -1){
    printf("Operator Stack Underflow\n");
    return '\0';
  }
  return stack->expressions[stack->top--].operation;
}

char getTopOperator(const Stack* stack)
{
  if (stack->top == -1){
    printf("Operator Stack Underflow\n");
    return '\0';
  }
  return stack->expressions[stack->top].operation;
}

void pushMatrix(Stack* stack, Matrix* matrix)
{
  if (stack->top == stack->capacity - 1) {
    printf("Matrix Stack Overflow\n");
    return;
  }
  stack->expressions[++stack->top].matrix = matrix;
}

Matrix* popMatrix(Stack* stack)
{
  if (stack->top == -1){
    printf("Matrix Stack Underflow\n");
    return NULL;
  }
  return stack->expressions[stack->top--].matrix;
}

int getPriority(char operator)
{
  switch(operator){
    case '*':
      return 2;
    case '+':
    case '-':
      return 1;
    default:
      return 0;
  }
}

void freeStack(Stack *stack)
{
  for (int i = 0; i <= stack->top; i++)
  {
    freeMatrix(stack->expressions[i].matrix);
  }
  free(stack->expressions);
  free(stack);
}

int isOperator(char c) {
  if (c == '*' || c== '+' || c == '-') {
    return 1;
  }
  return 0;
}

bool isNotEmpty(const Stack* stack)
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
  matrixStack.expressions = (Expression*)malloc(matrixStack.capacity * sizeof(Expression));

  Stack operatorStack;
  operatorStack.capacity = sizeof(operation);
  operatorStack.top = -1;
  operatorStack.expressions = (Expression*)malloc(operatorStack.capacity * sizeof(Expression));
  
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
  for (int i = 2; i < strlen(statement); i++){
    char currentChar = statement[i];

    // If current character is *
    if ((isOperator(currentChar) == 1) && getPriority(currentChar) >= getPriority(getTopOperator(&operatorStack))) {
      pushOperator(&operatorStack, currentChar);
    }
    // If current character is + - and there is a * in stack
    else if((isOperator(currentChar) == 1) && getPriority(currentChar) < getPriority(getTopOperator(&operatorStack))) {
      Matrix* matrix_result = initMatrix(matrices[0]->rows, matrices[1]->cols);
      
      multiply(popMatrix(&matrixStack), popMatrix(&matrixStack), matrix_result);
      printMatrix(matrix_result);
      pushMatrix(&matrixStack, matrix_result);

      // pop the * and push the current operator
      popOperator(&operatorStack);
      pushOperator(&operatorStack, currentChar);
    }
    // If current character is a matrix
    else if (isalpha(currentChar) != 0){
      pushMatrix(&matrixStack, matrices[++numMat]);
    }
  }

  // Repeat popping + or - operators
  while (isNotEmpty(&operatorStack))
  {
    char op = popOperator(&operatorStack);
    if (op == '+')
    {
      add(popMatrix(&matrixStack), popMatrix(&matrixStack));
      // add() harus return matrix buat di push balik ke stack, terus uncomment yg dibawah
      //pushMatrix(&matrixStack, result_from_add);
    }
    else if (op == '-')
    {
      subtract(popMatrix(&matrixStack), popMatrix(&matrixStack));
      // ini juga sama
      //pushMatrix(&matrixStack, result_from_subtract);
    }
  }

  //// --------------- Scan all the matrix ---------------------- /////

  // if (operation[0] == '+')
  // {
  //   add(matrices[0], matrices[1]);
  //   printMatrix(matrices[0]);
  // }
  // else if (operation[0] == '-')
  // {
  //   subtract(matrices[0], matrices[1]);
  //   printMatrix(matrices[0]);
  // }
  // else if (operation[0] == '*')  {

  //   Matrix* matrix_result = initMatrix(matrices[0]->rows, matrices[1]->cols);

  // multiply_multithread(matrices[0], matrices[1], matrix_result);
  //   printMatrix(matrix_result);
  // }

  printMatrix(popMatrix(&matrixStack));
  //// --------------- Scan all the matrix ---------------------- /////

  return 0;
}
////////////////////////////////////////////////////////////////////////////////

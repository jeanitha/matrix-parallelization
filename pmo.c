////////////////////////////////Libraries///////////////////////////////////////
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
// for linux, use sysinfo (uncomment below and delete sysctl)
// #include <sys/sysinfo.h>

// for mac, use sysctl (uncomment below and delete sysinfo)
#include <sys/sysctl.h>




// --------------- Stack --------------------
// A structure to represent a stack
struct Stack
{
  int top;
  unsigned capacity;
  char *array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack *createStack(unsigned capacity)
{
  struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (char *)malloc(stack->capacity * sizeof(char));
  return stack;
}

// Stack is full when top is equal to the last index
int stackIsFull(struct Stack *stack)
{
  return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int stackIsEmpty(struct Stack *stack)
{
  return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void stackPush(struct Stack *stack, char item)
{
  if (stackIsFull(stack))
    return;
  stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
int stackPop(struct Stack *stack)
{
  if (stackIsEmpty(stack))
    return INT_MIN;
  return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
int stackPeek(struct Stack *stack)
{
  if (stackIsEmpty(stack))
    return INT_MIN;
  return stack->array[stack->top];
}
// --------------- Stack --------------------

void append(char *s, char c)
{
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
}

void print2DArray(int arr[][101], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}


////////////////////////////////////////////////////////////////////////////////

////////////////////////////GLOBAL VARIABLES/STRUCTS////////////////////////////
char statement[30];
char operation[11];
char matrix[11];
int totalMatrix = 0;
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////FUNCTIONS///////////////////////////////////////

// example code of 2d array multiplication
int multiply()
{
  int a[10][10], b[10][10], mul[10][10], r, c, i, j, k;
  system("cls");
  printf("enter the number of row=");
  scanf("%d", &r);
  printf("enter the number of column=");
  scanf("%d", &c);
  printf("enter the first matrix element=\n");
  for (i = 0; i < r; i++)
  {
    for (j = 0; j < c; j++)
    {
      scanf("%d", &a[i][j]);
    }
  }
  printf("enter the second matrix element=\n");
  for (i = 0; i < r; i++)
  {
    for (j = 0; j < c; j++)
    {
      scanf("%d", &b[i][j]);
    }
  }

  printf("multiply of the matrix=\n");
  for (i = 0; i < r; i++)
  {
    for (j = 0; j < c; j++)
    {
      mul[i][j] = 0;
      for (k = 0; k < c; k++)
      {
        mul[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  // for printing result
  for (i = 0; i < r; i++)
  {
    for (j = 0; j < c; j++)
    {
      printf("%d\t", mul[i][j]);
    }
    printf("\n");
  }
  return 0;
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

void scanMatrix()
{
  int row = 0;
  scanf("%d", &row);
  int col = 0;
  scanf("%d", &col);
  int current_matrix[row][col];
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      scanf("%d", &current_matrix[i][j]);
    }
  }
  // printf("%d", current_matrix[79][88]);
  // print2DArray(current_matrix, row, col);
}
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////MAIN FUNCTION//////////////////////////////////
int main()
{
  scanStatement();
  // scanMatrix();

  //// --------------- Scan all the matrix ---------------------- /////
  // ------------------ Matrix A
  int row = 0;
  scanf("%d", &row);
  int col = 0;
  scanf("%d", &col);
  int matrix_A[row][col];
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      scanf("%d", &matrix_A[i][j]);
    }
  }

  // ------------------ Matrix B
  row = 0;
  scanf("%d", &row);
  col = 0;
  scanf("%d", &col);
  int matrix_B[row][col];
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      scanf("%d", &matrix_B[i][j]);
    }
  }

  // ------------------ Matrix C
  if (totalMatrix >= 3) {
    row = 0;
    scanf("%d", &row);
    col = 0;
    scanf("%d", &col);
    int matrix_C[row][col];
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        scanf("%d", &matrix_C[i][j]);
      }
    }
    // printf("%s", "3");

  }

    // ------------------ Matrix D
  if (totalMatrix >= 4) {
    row = 0;
    scanf("%d", &row);
    col = 0;
    scanf("%d", &col);
    int matrix_D[row][col];
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        scanf("%d", &matrix_D[i][j]);
      }
    }
    // printf("%s", "4");

  }

    // ------------------ Matrix E
  if (totalMatrix >= 5) {
    row = 0;
    scanf("%d", &row);
    col = 0;
    scanf("%d", &col);
    int matrix_E[row][col];
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        scanf("%d", &matrix_E[i][j]);
      }
    }
    // printf("%s", "5");
    // printf("%d", matrix_E[325][459]);

  }

    // ------------------ Matrix F
  if (totalMatrix >= 6) {
    row = 0;
    scanf("%d", &row);
    col = 0;
    scanf("%d", &col);
    int matrix_F[row][col];
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        scanf("%d", &matrix_F[i][j]);
      }
    }
  }

    // ------------------ Matrix G
  if (totalMatrix >= 7) {
    row = 0;
    scanf("%d", &row);
    col = 0;
    scanf("%d", &col);
    int matrix_G[row][col];
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        scanf("%d", &matrix_G[i][j]);
      }
    }
  }

    // ------------------ Matrix H
  if (totalMatrix >= 8) {
    row = 0;
    scanf("%d", &row);
    col = 0;
    scanf("%d", &col);
    int matrix_H[row][col];
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        scanf("%d", &matrix_H[i][j]);
      }
    }
  }

    // ------------------ Matrix I
  if (totalMatrix >= 9) {
    row = 0;
    scanf("%d", &row);
    col = 0;
    scanf("%d", &col);
    int matrix_I[row][col];
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        scanf("%d", &matrix_I[i][j]);
      }
    }
  }

    // ------------------ Matrix J
  if (totalMatrix >= 10) {
    row = 0;
    scanf("%d", &row);
    col = 0;
    scanf("%d", &col);
    int matrix_J[row][col];
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        scanf("%d", &matrix_J[i][j]);
      }
    }
  }

  //// --------------- Scan all the matrix ---------------------- /////

  // if (totalMatrix >= 3) {
  //   printf("%d", matrix_E[0][0]);
  // }

  

  return 126;
}
////////////////////////////////////////////////////////////////////////////////

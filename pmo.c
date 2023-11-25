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
  these integer will be used to print the matrices.
  It must be set to the column size of the matrix.
  It will be used on the printMatrix() function
*/
int finalMatrixLength = 0;
int matrix_1_length = 0;
int matrix_2_length = 0;
int matrix_3_length = 0;

/*
  holds all the matrixes (A,B,C,D,...)
*/
char matrix[11];

/*
  matrix count
*/
int totalMatrix = 0;
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

void printFinalMatrix(int (*ptr)[finalMatrixLength], int rows, int columns)
{
  printf("%d", rows);
  printf("%s", " ");
  printf("%d ", columns);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      printf("%d\t", ptr[i][j]);
    }
    printf("\n");
  }
}

void print_first_matrix(int (*ptr)[matrix_1_length], int rows, int columns)
{
  printf("%d", rows);
  printf("%s", " ");
  printf("%d ", columns);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      printf("%d\t", ptr[i][j]);
    }
    printf("\n");
  }
}

void print_second_matrix(int (*ptr)[matrix_2_length], int rows, int columns)
{
  printf("%d", rows);
  printf("%s", " ");
  printf("%d ", columns);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      printf("%d\t", ptr[i][j]);
    }
    printf("\n");
  }
}

void print_third_matrix(int (*ptr)[matrix_3_length], int rows, int columns)
{
  printf("%d", rows);
  printf("%s", " ");
  printf("%d ", columns);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      printf("%d\t", ptr[i][j]);
    }
    printf("\n");
  }
}

struct arg
{
  int (*matrix_1)[];
  int (*matrix_2)[];
  int i;
  int columns;
  int direction;
};

/*
arguments struct are:
int (*matrix_1)[matrix_1_length], int (*matrix_2)[matrix_2_length], int i, int columns
*/
void *addFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  int(*matrix_1)[matrix_1_length] = params->matrix_1;
  int(*matrix_2)[matrix_2_length] = params->matrix_2;
  int i = params->i;
  int columns = params->columns;

  for (int j = 0; j < columns; j++)
  {
    matrix_1[i][j] = matrix_1[i][j] + matrix_2[i][j];
  }
  return NULL;
}

/*
  add two matrix, matrix_1 is replaced with the resulting addition
*/
void add(int (*matrix_1)[matrix_1_length], int (*matrix_2)[matrix_2_length], int rows, int columns)
{
  pthread_t thr[rows];
  struct arg args[rows];

  for (int i = 0; i < rows; i++)
  {
    args[i].i = i;
    args[i].columns = columns;
    args[i].matrix_1 = matrix_1;
    args[i].matrix_2 = matrix_2;
    pthread_create(&thr[i], NULL, addFunc, (void *)&args[i]);
  }

  for (int i = 0; i < rows; i++)
  {
    pthread_join(thr[i], NULL);
  }
}

/*
arguments struct are:
int (*matrix_1)[matrix_1_length], int (*matrix_2)[matrix_2_length], int i, int columns
*/
void *subtractFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  int(*matrix_1)[matrix_1_length] = params->matrix_1;
  int(*matrix_2)[matrix_2_length] = params->matrix_2;
  int i = params->i;
  int columns = params->columns;
  int direction = params->direction;

  if (direction == 1)
  {
    for (int j = 0; j < columns; j++)
    {
      matrix_1[i][j] = matrix_1[i][j] - matrix_2[i][j];
    }
  }
  else
  {
    for (int j = 0; j < columns; j++)
    {
      matrix_1[i][j] = matrix_2[i][j] - matrix_1[i][j];
    }
  }

  return NULL;
}

/*
  subtract two matrix, matrix_1 is replaced with the resulting subtraction
*/
void subtract(int (*matrix_1)[matrix_1_length], int (*matrix_2)[matrix_2_length], int rows, int columns, int direction)
{
  pthread_t thr[rows];
  struct arg args[rows];

  for (int i = 0; i < rows; i++)
  {
    args[i].i = i;
    args[i].columns = columns;
    args[i].matrix_1 = matrix_1;
    args[i].matrix_2 = matrix_2;
    args[i].direction = direction;
    pthread_create(&thr[i], NULL, subtractFunc, (void *)&args[i]);
  }

  for (int i = 0; i < rows; i++)
  {
    pthread_join(thr[i], NULL);
  }
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
  // ------------------ Matrix A ----------------------
  int row = 0;
  scanf("%d", &row);
  int col = 0;
  scanf("%d", &col);

  int(*ptr1)[col];

  int matrix_A[row][col];
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      scanf("%d", &matrix_A[i][j]);
    }
  }
  ptr1 = matrix_A;
  matrix_1_length = col;
  // print_first_matrix(ptr1, row, col);

  // ------------------ Matrix B ----------------------
  row = 0;
  scanf("%d", &row);
  col = 0;
  scanf("%d", &col);

  int(*ptr2)[col];

  int matrix_B[row][col];
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      scanf("%d", &matrix_B[i][j]);
    }
  }

  ptr2 = matrix_B;
  matrix_2_length = col;
  // print_second_matrix(ptr2, row, col);
  // subtract(ptr1, ptr2, row, col, 0);

  if (operation[0] == '+')
  {
    add(ptr1, ptr2, row, col);
  }
  else if (operation[0] == '-')
  {
    subtract(ptr1, ptr2, row, col, 1);
  }

  print_first_matrix(ptr1, row, col);

  // ------------------ Matrix C ----------------------
  if (totalMatrix >= 3)
  {
    row = 0;
    scanf("%d", &row);
    col = 0;
    scanf("%d", &col);

    int(*ptr3)[col];

    int matrix_C[row][col];
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        scanf("%d", &matrix_C[i][j]);
      }
    }

    ptr3 = matrix_C;
    matrix_3_length = col;
    print_third_matrix(ptr3, row, col);
  }

  // ------------------ Matrix D ----------------------
  if (totalMatrix >= 4)
  {
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

  // ------------------ Matrix E ----------------------
  if (totalMatrix >= 5)
  {
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

  // ------------------ Matrix F ----------------------
  if (totalMatrix >= 6)
  {
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

  // ------------------ Matrix G ----------------------
  if (totalMatrix >= 7)
  {
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

  // ------------------ Matrix H ----------------------
  if (totalMatrix >= 8)
  {
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

  // ------------------ Matrix I ----------------------
  if (totalMatrix >= 9)
  {
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

  // ------------------ Matrix J ----------------------
  if (totalMatrix >= 10)
  {
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

  return 0;
}
////////////////////////////////////////////////////////////////////////////////

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
int finalMatrixcolumn = 0;
int finalMatrixrow = 0;
int matrix_1_column = 0;
int matrix_2_column = 0;
int matrix_3_column = 0;
int matrix_4_column = 0;
int matrix_5_column = 0;
int matrix_6_column = 0;
int matrix_7_column = 0;
int matrix_8_column = 0;
int matrix_9_column = 0;
int matrix_10_column = 0;

int matrix_1_row = 0;
int matrix_2_row = 0;
int matrix_3_row = 0;
int matrix_4_row = 0;
int matrix_5_row = 0;
int matrix_6_row = 0;
int matrix_7_row = 0;
int matrix_8_row = 0;
int matrix_9_row = 0;
int matrix_10_row = 0;

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

void printFinalMatrix(int (*ptr)[finalMatrixcolumn], int rows, int columns)
{
  printf("%d ", rows);
  printf("%d", columns);
  printf("\n");
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      printf("%d\t", ptr[i][j]);
    }
    printf("\n");
  }
}

void print_first_matrix(int (*ptr)[matrix_1_column], int rows, int columns)
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

void print_second_matrix(int (*ptr)[matrix_2_column], int rows, int columns)
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

void print_third_matrix(int (*ptr)[matrix_3_column], int rows, int columns)
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
int (*matrix_1)[matrix_1_column], int (*matrix_2)[matrix_2_column], int i, int columns
*/
void *addFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  int(*matrix_1)[matrix_1_column] = params->matrix_1;
  int(*matrix_2)[matrix_2_column] = params->matrix_2;
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
void add(int (*matrix_1)[matrix_1_column], int (*matrix_2)[matrix_2_column], int rows, int columns)
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
int (*matrix_1)[matrix_1_column], int (*matrix_2)[matrix_2_column], int i, int columns
*/
void *subtractFunc(void *args)
{
  struct arg *params = (struct arg *)args;
  int(*matrix_1)[matrix_1_column] = params->matrix_1;
  int(*matrix_2)[matrix_2_column] = params->matrix_2;
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


void *multiplyFunc(void *args)
{
    struct arg *params = (struct arg *)args;
  int(*matrix_1)[matrix_1_column] = params->matrix_1;
  int(*matrix_2)[matrix_2_column] = params->matrix_2;
  int i = params->i;
  int columns = params->columns;
  return NULL;
}
/*
  subtract two matrix, matrix_1 is replaced with the resulting subtraction
*/
void subtract(int (*matrix_1)[matrix_1_column], int (*matrix_2)[matrix_2_column], int rows, int columns, int direction)
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


/*
  Multiply function. columns_1 = rows_2 hence no need for rows_2 as parameters.
  These two are refered as 'p' in the document
*/
void multiply(int (*matrix_1)[matrix_1_column], int (*matrix_2)[matrix_2_column], int (*matrix_result)[finalMatrixcolumn], int rows_1, int columns_1, int columns_2)
{
  for (int i = 0; i < rows_1; i++)
  {
    for (int j = 0; j < columns_2; j++)
    {
      pthread_t thr[columns_1];
      struct arg args[columns_1];
      for (int p = 0; p < columns_1; p++)
      {
        matrix_result[i][j] = matrix_result[i][j] + matrix_1[i][p] * matrix_2[p][j];
      }  
    } 
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
  scanf("%d", &matrix_1_row);
  scanf("%d", &matrix_1_column);

  int(*ptr1)[matrix_1_column];

  int matrix_A[matrix_1_row][matrix_1_column];
  for (int i = 0; i < matrix_1_row; i++)
  {
    for (int j = 0; j < matrix_1_column; j++)
    {
      scanf("%d", &matrix_A[i][j]);
    }
  }
  ptr1 = matrix_A;
  // print_first_matrix(ptr1, row, col);

  // ------------------ Matrix B ----------------------
  scanf("%d", &matrix_2_row);
  scanf("%d", &matrix_2_column);

  int(*ptr2)[matrix_2_column];

  int matrix_B[matrix_2_row][matrix_2_column];
  for (int i = 0; i < matrix_2_row; i++)
  {
    for (int j = 0; j < matrix_2_column; j++)
    {
      scanf("%d", &matrix_B[i][j]);
    }
  }

  ptr2 = matrix_B;
  // print_second_matrix(ptr2, row, col);

  if (operation[0] == '+')
  {
    add(ptr1, ptr2, matrix_2_row, matrix_2_column);
    print_first_matrix(ptr1, matrix_1_row, matrix_1_column);
  }
  else if (operation[0] == '-')
  {
    subtract(ptr1, ptr2, matrix_2_row, matrix_2_column, 1);
    print_first_matrix(ptr1, matrix_1_row, matrix_1_column);
  } else if (operation[0] == '*')  {
    int(*ptrX)[matrix_2_column];

    int matrix_X[matrix_1_row][matrix_2_column];
    finalMatrixcolumn = matrix_2_column;
    finalMatrixrow = matrix_1_row;
    ptrX = matrix_X;

    multiply(ptr1, ptr2, ptrX, matrix_1_row, matrix_1_column, matrix_2_column);
    printFinalMatrix(ptrX, finalMatrixrow, finalMatrixcolumn);
  }

  // print_first_matrix(ptr1, matrix_1_row, matrix_1_column);

  // // need to replace row and col with each corresponding matrix_[n]_row and matrix_[n]_column
  int row;
  int col;
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
    matrix_3_column = col;
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

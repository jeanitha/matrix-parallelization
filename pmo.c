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

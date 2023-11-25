/*
 Manual addition functions ----------
*/
// void addFunc(int (*matrix_1)[matrix_1_length], int (*matrix_2)[matrix_2_length], int i, int j) {
//   matrix_1[i][j] = matrix_1[i][j] + matrix_2[i][j];
// }

// void add(int (*matrix_1)[matrix_1_length], int (*matrix_2)[matrix_2_length], int rows, int columns)
// {

//   for (int i = 0; i < rows; i++)
//   {
//     for (int j = 0; j < columns; j++)
//     {
//       addFunc(matrix_1, matrix_2, i,j);
//     }
//   }
// }
 


/*
  Manual substraction function ---------------
*/
// void subtractFunc(int (*matrix_1)[matrix_1_length], int (*matrix_2)[matrix_2_length], int i, int j, int direction)
// {
//   if (direction == 1)
//   {
//     matrix_1[i][j] = matrix_1[i][j] - matrix_2[i][j];
//   } else {
//     matrix_1[i][j] = matrix_2[i][j] - matrix_1[i][j];
//   }

// }

// /*
//   subtract two matrix, matrix_1 is replaced with the resulting subtraction.
//   'direction' will decide which matrix is subtracted by which
// */
// void subtract(int (*matrix_1)[matrix_1_length], int (*matrix_2)[matrix_2_length], int rows, int columns, int direction)
// {
//     for (int i = 0; i < rows; i++)
//     {
//       for (int j = 0; j < columns; j++)
//       {
//         subtractFunc(matrix_1, matrix_2, i, j, direction);
//       }
//     }
// }
/*
 *
 * Prints a 8 by 126 matrix 
 *
 */

#include <stdio.h>

void printMatrix2( double matrix[][126] ){
  int i,j;

  for(i=0; i<126; i++){
    for(j=0; j<8; j++){
      printf("%.8lg\t", matrix[j][i]);
    }
    printf("\n");
  }
}

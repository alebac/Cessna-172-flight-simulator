/*
 *
 * Prints a 4 by 60 matrix 
 *
 */

#include <stdio.h>

void printMatrix3( double matrix[][60] ){
  int i,j;

  for(i=0; i<60; i++){
    for(j=0; j<4; j++){
      printf("%.8lg\t", matrix[j][i]);
    }
    printf("\n");
  }
}

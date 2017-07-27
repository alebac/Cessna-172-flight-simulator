/*
 *
 * Prints a 7 by 126 matrix 
 *
 */

#include <stdio.h>

void printMatrix( double matrix[][126] ){
  int i,j;

  for(i=0; i<126; i++){
    for(j=0; j<7; j++){
      printf("%.8lg\t", matrix[j][i]);
    }
    printf("\n");
  }
}

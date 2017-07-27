/*
 *
 * Reads a 7 by 126 matrix 
 *
 */

#include <stdio.h>

void readMatrix( double matrix[][126], FILE * fPtr ){
  int i,j;

  for(i=0; i<126; i++){
    for(j=0; j<7; j++){
      fscanf( fPtr, "%lg", &matrix[j][i]);
    }
  }
}

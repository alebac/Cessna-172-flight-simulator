/*
 *
 * Reads a 4 by 60 matrix 
 *
 */

#include <stdio.h>

void readMatrix3( double matrix[][60], FILE * fPtr ){
  int i,j;

  for(i=0; i<60; i++){
    for(j=0; j<4; j++){
      fscanf( fPtr, "%lg", &matrix[j][i]);
    }
  }
}

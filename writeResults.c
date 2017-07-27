#include <stdio.h>

void writeResults( double Y[][12], int n, double dt, char* outputFileName, double command[] ){
  FILE* fPtr;
  int i, j;
  double t = 0;

  if( ( fPtr = fopen( outputFileName, "w" ) ) == NULL ){
    printf("File results could not be opened.\n");
  } else{
    for( i=0; i<n; i++){
    fprintf( fPtr, "%lg ", t);
    t = t + dt;
      for( j=0; j<12; j++){
        fprintf( fPtr, "%lg ", Y[i][j]);
      }
    fprintf( fPtr, "%lg", command[i]);
    fprintf( fPtr, "\n");
    }
    fclose(fPtr);
  } 
}

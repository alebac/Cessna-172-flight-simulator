/*
 *
 * Reads input from user in file input.txt 
 *
 */

#include <stdio.h>

void readInput( double input[], char* outputFileName ){

  char tokenPtr[300] = { 0 };
  double dt;
  double simulationDuration;
  double stepNumber;
  int i;
  double speed;
  double altitude;

  FILE* fPtr;

  if( ( fPtr = fopen("input.txt","r") ) == NULL ){
    printf("File could not be opened\n");
  }
  else {
    fscanf( fPtr, "%lg", &dt );
    fscanf( fPtr, "%s", tokenPtr );
    fscanf( fPtr, "%lg", &simulationDuration );
    fscanf( fPtr, "%s", tokenPtr );
    fscanf( fPtr, "%s", outputFileName );
    fscanf( fPtr, "%s", tokenPtr );
    fscanf( fPtr, "%lg", &speed );
    fscanf( fPtr, "%s", tokenPtr );
    fscanf( fPtr, "%lg", &altitude );
    fscanf( fPtr, "%s", tokenPtr );
    fscanf( fPtr, "%lg", &stepNumber );
    if(stepNumber > 20){
      printf("Step number too big, no command considered.\n");
    } else {
      fscanf( fPtr, "%s", tokenPtr );
      for(i=0; i<stepNumber*3; i++){
        fscanf( fPtr, "%lg", &input[i+5] );
      }
    }
    fclose(fPtr);
  }

  input[0] = dt;
  input[1] = simulationDuration;
  input[2] = speed;
  input[3] = altitude;
  input[4] = stepNumber;
}

/*
 *
 * Reads input file propeller.txt 
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void readPropeller( int* stationsNumberPtr, double dataPropeller[], double propeller[][60] ){

  double diameter;
  double spinnerDiameter;
  double bladeNumber;
  double inertia;
  double ClalphaPropeller;
  double Cl0Propeller;
  double a0Propeller;
  double Cdalpha2Propeller;
  double CdalphaPropeller;
  double Cd0Propeller;

  char c;
  char tokenPtr[200] = { 0 };
  int count = 0;
  int i;

  FILE* fPtr;

  if( ( fPtr = fopen("propeller.txt","r") ) == NULL ){
    printf("File could not be opened\n");
  }
  else {
    fscanf( fPtr, "%c", &c );
    while( !feof( fPtr ) ){
      if( (c != ' ') && (c != '\t') && (c != '\n') ){
        tokenPtr[count] = c;
        count++; 
      } else if (count != 0){
        tokenPtr[count] = '\0';
        count = 0;

	/* Propeller Data */
        if( strcmp( tokenPtr, "S.I.") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &diameter);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &spinnerDiameter);
          for(i=0; i<3; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &bladeNumber);
          for(i=0; i<3; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &inertia);
          for(i=0; i<2; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%d", stationsNumberPtr);
        }  else if( strcmp( tokenPtr, "CLARK") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &ClalphaPropeller);
          for(i=0; i<2; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &Cl0Propeller);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &a0Propeller);
          for(i=0; i<2; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &Cdalpha2Propeller);
          for(i=0; i<2; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &CdalphaPropeller);
          for(i=0; i<2; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &Cd0Propeller);
        } else if( strcmp( tokenPtr, "BA") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix3( propeller, fPtr );
        }
      } 

      fscanf( fPtr, "%c", &c );  
    }

    fclose(fPtr);

  dataPropeller[0] =  diameter;
  dataPropeller[1] = spinnerDiameter;
  dataPropeller[2] = bladeNumber;
  dataPropeller[3] = inertia;
  dataPropeller[4] = ClalphaPropeller;
  dataPropeller[5] = Cl0Propeller;
  dataPropeller[6] = a0Propeller;
  dataPropeller[7] = Cdalpha2Propeller;
  dataPropeller[8] = CdalphaPropeller;
  dataPropeller[9] = Cd0Propeller;
  }
}

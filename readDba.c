/*
 *
 * Reads input file dba.txt 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void readDba( double dataDba[], double steadyStateCoefficients[][126], double XForceDerivatives[][126], double YForceDerivatives[][126], double ZForceDerivatives[][126], double RollingMomentDerivatives[][126], double PitchingMomentDerivatives[][126], double YawingMomentDerivatives[][126], double ControlForceDerivatives[][126], double ControlMomentDerivatives[][126], double RotaryDerivatives[][126] ){

  double mass;
  double wingspan;
  double surface;
  double chord;
  double MachDragRaise;
  double Jx;
  double Jy;
  double Jz;
  double Jxz; 
  double minElevators;
  double maxElevators;
  double ailerons;  
  double rudder;
  double minFlaps;
  double maxFlaps;
  double fuelFraction;

  char c;
  char tokenPtr[300] = { 0 };
  int count = 0;
  int i;

  FILE* fPtr;

  if( ( fPtr = fopen("dba.txt","r") ) == NULL ){
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

        /* Generic Data */
        if( strcmp( tokenPtr, "VELIVOLO") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &mass);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &wingspan);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &surface);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &chord);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &MachDragRaise);
        } 
        else if( strcmp( tokenPtr, "LOCATION") == 0){
          fscanf( fPtr, "%lg", &Jx);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &Jy);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &Jz);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &Jxz);

          for(i=0; i<39; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &maxElevators);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &minElevators);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &ailerons);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &rudder);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &minFlaps);
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &maxFlaps);

          for(i=0; i<13; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &fuelFraction);
        }

	/* Steady State Coefficients */
        else if( strcmp( tokenPtr, "Cm") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix( steadyStateCoefficients, fPtr );
        }

        /* X Force Derivatives */
        else if( strcmp( tokenPtr, "CXP") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix2( XForceDerivatives, fPtr );
        }

        /* Y Force Derivatives */
        else if( strcmp( tokenPtr, "CYA") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix( YForceDerivatives, fPtr );
        }

        /* Z Force Derivatives */
        else if( strcmp( tokenPtr, "CZP") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix2( ZForceDerivatives, fPtr );
        }

        /* Rolling Moment Derivatives */
        else if( strcmp( tokenPtr, "ClA") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix( RollingMomentDerivatives, fPtr );
        }

        /* Pitching Moment Derivatives */
        else if( strcmp( tokenPtr, "CmP") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix2( PitchingMomentDerivatives, fPtr );
        }
 
        /* Yawing Moment Derivatives */
        else if( strcmp( tokenPtr, "CnA") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix( YawingMomentDerivatives, fPtr );
        }

        /* Control Force Derivatives */
        else if( strcmp( tokenPtr, "CYda") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix( ControlForceDerivatives, fPtr );
        }

        /* Control Moment Derivatives */
        else if( strcmp( tokenPtr, "Cnda") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix( ControlMomentDerivatives, fPtr );
        }

        /* Rotary Derivatives */
        else if( strcmp( tokenPtr, "Cmom") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          readMatrix( RotaryDerivatives, fPtr );
        }
      }

      fscanf( fPtr, "%c", &c );  
    }

    fclose(fPtr);

    dataDba[0] = mass;
    dataDba[1] = wingspan;
    dataDba[2] = surface;
    dataDba[3] = chord;
    dataDba[4] = MachDragRaise;
    dataDba[5] = Jx;
    dataDba[6] = Jy;
    dataDba[7] = Jz;
    dataDba[8] = Jxz; 
    dataDba[9] = minElevators;
    dataDba[10] = maxElevators;
    dataDba[11] = ailerons;  
    dataDba[12] = rudder;
    dataDba[13] = minFlaps;
    dataDba[14] = maxFlaps;
    dataDba[15] = fuelFraction;

  }
}

/*
 *
 * Reads input file engine.txt 
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void readEngine( double dataEngine[] ){

  double maxPower;
  double exponent;
  double minRpm;
  double maxRpm;
  double reduction;
  double efficiency;
  double specificConsumption;

  char c;
  char tokenPtr[200] = { 0 };
  int count = 0;
  int i;

  FILE* fPtr;

  if( ( fPtr = fopen("engine.txt","r") ) == NULL ){
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

	/* Engine Data */
        if( strcmp( tokenPtr, "UNITA'") == 0){
          fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &maxPower);
          for(i=0; i<9; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &exponent);
          for(i=0; i<8; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &minRpm);
          for(i=0; i<7; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &maxRpm);
          for(i=0; i<7; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &reduction);
          for(i=0; i<6; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &efficiency);
          for(i=0; i<4; i++)
            fscanf( fPtr, "%s", tokenPtr );
          fscanf( fPtr, "%lg", &specificConsumption);        
        }
      }

      fscanf( fPtr, "%c", &c );  
    }

    fclose(fPtr);

    dataEngine[0] = maxPower;
    dataEngine[1] = exponent;
    dataEngine[2] = minRpm;
    dataEngine[3] = maxRpm;
    dataEngine[4] = reduction;
    dataEngine[5] = efficiency;
    dataEngine[6] = specificConsumption;

  }
}

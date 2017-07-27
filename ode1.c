#include <stdio.h>
#include <math.h>

void ode1( double mass, double specificConsumption, double wingspan, double surface, double chord, double Jx, double Jy, double Jz, double Jxz, double dt, int n, double steadyStateCoefficients[][126], double YForceDerivatives[][126], double ZForceDerivatives[][126], double RollingMomentDerivatives[][126], double PitchingMomentDerivatives[][126], double YawingMomentDerivatives[][126], double  ControlForceDerivatives[][126], double ControlMomentDerivatives[][126], double Y[][12], double y0[], double deTrim, double da, double dr, double T, double command[] ){

  int i;
  int j;
  double dy[12] = {0};
  double t = 0;
  double de;
  int dots = 0;
  double initialMass = mass;

  for( i=0; i<12; i++ ){
    Y[0][i] = y0[i];
  } 

  for( j=1; j<n; j++ ){
    de = deTrim + command[j];    
    mathModel( dy, Y[j-1], mass, surface, wingspan, chord, steadyStateCoefficients, YForceDerivatives, ZForceDerivatives, RollingMomentDerivatives, PitchingMomentDerivatives, YawingMomentDerivatives, ControlForceDerivatives, ControlMomentDerivatives, Jx, Jy, Jz, Jxz, de, da, dr, T );

    for( i=0; i<12; i++){
      Y[j][i] = Y[j-1][i] + dt*dy[i]; 
      }
    t = t + dt;
    if(dots == 100){
      printf(".");
      dots = 0; 
    }
    dots++;

 // Update of the mass 
    mass = mass - dt*specificConsumption;
  }

  printf("\nFinal mass is: %lg\n", mass);
  printf("Mass variation is: %lg\n", initialMass - mass);
}

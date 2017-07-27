#include <math.h>
#include <stdio.h>

void atmoDensity( double h, double rho[] ){

  double T = 298.15 - 0.0065 * h; 

  rho[0] = 1.225 * pow( T/298.15, 4.25);

}

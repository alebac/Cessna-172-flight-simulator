#include <math.h>

double atmoPressure( double h ){

  double pressure;

  pressure = 101325 * pow( atmoT(h)/298.15, 5.25);

  return pressure;
}

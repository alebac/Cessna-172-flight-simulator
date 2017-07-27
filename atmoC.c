#include <math.h>

double atmoC( double h ){

  double c;
  double T;

  T = atmoT(h);
  c = 20.05 * sqrt( T );
 
  return c;
}

/*
 *
 * The main file 
 *
 */

#include <math.h>
#include <stdio.h>
#include "matrix.h"

int main(){

  double dataDba[16];
  double steadyStateCoefficients[7][126];
  double XForceDerivatives[8][126];
  double YForceDerivatives[7][126];
  double ZForceDerivatives[8][126];
  double RollingMomentDerivatives[7][126];
  double PitchingMomentDerivatives [8][126];
  double YawingMomentDerivatives [7][126];
  double ControlForceDerivatives [7][126];
  double ControlMomentDerivatives [7][126];
  double RotaryDerivatives [7][126];

  double dataEngine[7];

  int stationsNumber;
  double dataPropeller[10];
  double propeller[4][60];
  double resultsPropel[3];

  double Cx;
  double Cy;
  double Cz;
  double Cl;
  double Cm;
  double Cn;

  double de = 0;
  double da = 0;
  double dr = 0;

  double rpm;
  
  int i,j;
  double input[25];
  char outputFileName[50];
  readInput( input, outputFileName );
  double dt = input[0];
  double durataSimulazione = input[1];                   
  int n = ceil(durataSimulazione/dt) + 1;    
  double command[n];
  double stepNumber = input[4];
  double start;
  double end;
  double value;
  double t = 0;

  for( i=0; i<n; i++ ){
    command[i] = 0; 
  }            
 
// Assembling command vector  
  for( i=0; i<stepNumber; i++ ){
    start = input[3*i+5];
    end = input[3*i+6];
    value = input[3*i+7];
    for( j=0; j<n; j++ ){
      if( (t >= start) && (t < end) ){
        command[j] = value; 
      } 
      t = t + dt;
    }
    t = 0;
  }

  double y0[12];  
  y0[0] = input[2]; 
  y0[1] = 0;
  y0[2] = 0;
  y0[3] = 0;
  y0[4] = 0;
  y0[5] = 0;
  y0[6] = 0;
  y0[7] = 0;
  y0[8] = 0;
  y0[9] = 0;
  y0[10] = 0;
  y0[11] = input[3]; 

  double u = y0[0];
  double v = y0[1];
  double w = y0[2];
  double p = y0[3];
  double q = y0[4];
  double r = y0[5];
  double phi = y0[6];
  double theta = y0[7];
  double psi = y0[8];
  double xv = y0[9];
  double yv = y0[10];
  double zv = y0[11];

  double Rho[1];
  atmoDensity( zv, Rho ); 
  double rho = Rho[0];
  printf("rho = %lg\n", rho);
  printf("zv = %lg\n", zv);

  double V = sqrt( u*u + v*v + w*w );
  double alpha = atan2(w,u);
  double beta = atan2(v,u);
  double alphaDot = q - p*cos(alpha)*tan(beta) - r*sin(alpha)*tan(beta);
  double betaDot = p*sin(alpha) - r*cos(alpha);

// database for time integration
  double Y[n][12];
  for( i=0; i<100; i++){
    for( j=0; j<12; j++){
      Y[i][j] = 0.0;
    }
  }          

  readDba( dataDba, steadyStateCoefficients, XForceDerivatives, YForceDerivatives, ZForceDerivatives, RollingMomentDerivatives, PitchingMomentDerivatives, YawingMomentDerivatives, ControlForceDerivatives, ControlMomentDerivatives, RotaryDerivatives );

  double mass = dataDba[0];
  double wingspan = dataDba[1];
  double surface = dataDba[2];
  double chord = dataDba[3];
  double MachDragRaise = dataDba[4];
  double Jx = dataDba[5];
  double Jy = dataDba[6];
  double Jz = dataDba[7];
  double Jxz = dataDba[8]; 
  double minElevators = dataDba[9];
  double maxElevators = dataDba[10];
  double ailerons = dataDba[11];  
  double rudder = dataDba[12];
  double minFlaps = dataDba[13];
  double maxFlaps = dataDba[14];
  double fuelFraction = dataDba[15];

  readEngine( dataEngine );

  double maxPower = dataEngine[0];
  double exponent = dataEngine[1];
  double minRpm = dataEngine[2];
  double maxRpm = dataEngine[3];
  double reduction = dataEngine[4];
  double efficiency = dataEngine[5];
  double specificConsumption = dataEngine[6];

  readPropeller( &stationsNumber, dataPropeller, propeller );

  double diameter = dataPropeller[0];
  double spinnerDiameter = dataPropeller[1];
  double bladeNumber = dataPropeller[2];
  double inertia = dataPropeller[3];
  double ClalphaPropeller = dataPropeller[4];
  double Cl0Propeller = dataPropeller[5];
  double a0Propeller = dataPropeller[6];
  double Cdalpha2Propeller = dataPropeller[7];
  double CdalphaPropeller = dataPropeller[8];
  double Cd0Propeller = dataPropeller[9];

/*******************************/
// trim
/*******************************/

  printf("\nTRIM\n\n");

  double Clift;
  double Cd;
  double Lift = 10000;
  double W = 9.81*mass;
 
// alpha cycle
  while( fabs(Lift-W) > 1){
    if( Lift-W > 0 ){
      alpha -= 0.000001;
    } else{
      alpha += 0.000001;
    }
 
    interp( &Cx, &Cy, &Cz, &Cl, &Cm, &Cn, steadyStateCoefficients, YForceDerivatives, ZForceDerivatives, RollingMomentDerivatives, PitchingMomentDerivatives, YawingMomentDerivatives, ControlForceDerivatives, ControlMomentDerivatives, alpha, beta, alphaDot, betaDot, p, q, r, V, de, da, dr, wingspan, chord );
    Clift = -Cz*cos(alpha) + Cx*sin(alpha);
    Cd = -Cz*sin(alpha) - Cx*cos(alpha);
    Lift = Clift*0.5*rho*V*V*surface;
  }

  printf("Cz = %lg\n", Cz);
  printf("Cx = %lg\n", Cx);
  printf("alpha = %lg\n", alpha);
  printf("Lift = %lg\n", Lift);
  printf("W = %lg\n", W);

  double uTrim = V*cos(alpha);  
  double wTrim = V*sin(alpha);

  y0[0] = uTrim;
  y0[2] = wTrim;

  double D = Cd*0.5*rho*V*V*surface; 
  double T = 0;

  rpm = minRpm;

// rpm cycle
  while( fabs(T-D) > 1 ){ 
    propel( rpm, rho, V, stationsNumber, dataPropeller, propeller, resultsPropel );  
    T = resultsPropel[0];
    if( T > D ){
      printf("Minimum power exceeds drag.\n");
      break;
    }
    if(rpm >= maxRpm){
      printf("Not enough engine power for sustained flight.\n");
      break;
    }
    rpm += 0.2;
}

  printf("rpm = %lg\n", rpm);
  printf("T = %lg\n", T);
  printf("D = %lg\n", D);

  double M = 10000;
// M, de cycle
  while( fabs(M) > 1 ){
    if( M > 0 ){
      de += 0.000001;
    } else{
      de -= 0.000001;
    }
    interp( &Cx, &Cy, &Cz, &Cl, &Cm, &Cn, steadyStateCoefficients, YForceDerivatives, ZForceDerivatives, RollingMomentDerivatives, PitchingMomentDerivatives, YawingMomentDerivatives, ControlForceDerivatives, ControlMomentDerivatives, alpha, beta, alphaDot, betaDot, p, q, r, V, de, da, dr, wingspan, chord );
    M = Cm*0.5*rho*chord*V*V*surface;
  }
  printf("M = %lg\n", M );
  printf("de = %lg\n", de );

/*******************************/
// time integration
/*******************************/

  printf("\nTIME INTEGRATION\n");

  ode1( mass, specificConsumption, wingspan, surface, chord, Jx, Jy, Jz, Jxz, dt, n, steadyStateCoefficients,  YForceDerivatives, ZForceDerivatives, RollingMomentDerivatives, PitchingMomentDerivatives, YawingMomentDerivatives, ControlForceDerivatives, ControlMomentDerivatives, Y, y0, de, da, dr, T, command );

  writeResults( Y, n, dt, outputFileName, command );

/*******************************/
// dynamic stability
/*******************************/

  printf("\nDYNAMIC STABILITY\n\n");
  double mu = 2*mass/(rho*surface*chord);
  double Cwe = Clift;
  double Ctu = -3 * Cd;
  printf("mu = %lg\n", mu);
  printf("Ctu = %lg\n", Ctu);

/********************************/
// PHUGOID MODE

  printf("\nPHUGOID MODE\n");
  // definition of frequency and damping 
  double zetaph = -Ctu/(2.82843*Cwe);
  double omegaph = Cwe/(mu*1.4142)*(2*V)/chord;
  printf("zetaph = %lg\n", zetaph);
  printf("omegaph = %lg\n", omegaph);

  // eigenvalues 
  printf("Eigenvalues:\n");
  double lambdaph[2];
  double n1ph = -zetaph*omegaph;
  double omega1ph = omegaph*sqrt(fabs(zetaph*zetaph - 1));
  double Tph;
  double thalf;


  if( (zetaph*zetaph - 1) > 0 ){
    lambdaph[0] = -zetaph*omegaph + omegaph*sqrt(zetaph*zetaph - 1);
    lambdaph[1] = -zetaph*omegaph - omegaph*sqrt(zetaph*zetaph - 1);
    printf("lambdaph 1 = %lg\n", lambdaph[0]);  
    printf("lambdaph 2 = %lg\n", lambdaph[1]);
  } else {
    printf("lambdaph 1 = %lg + i%lg\n", n1ph, omega1ph);  
    printf("lambdaph 2 = %lg - i%lg\n", n1ph, omega1ph);
    // Period and half-time
    Tph = 2*M_PI/omega1ph;
    thalf = -0.69 / n1ph;
    printf("Period = %lg\n", Tph);
    printf("t(1/2) = %lg\n", thalf);
  }

/********************************/
// SHORT PERIOD MODE

  printf("\nSHORT PERIOD MODE\n");
  // definition of frequency and damping
  double Cma = -0.88; 
  double Cmq = -12.40;
  double omegas = 2*V/chord*sqrt(-Cma/Jy);
  double zetas = -(0.5*rho*V*V*surface*chord*chord)*(Cmq/(2*V*Jy))/(2*omegas);
  printf("zetas = %lg\n", zetas);
  printf("omegas = %lg\n", omegas);

  // eigenvalues 
  printf("Eigenvalues:\n");
  double lambdas[2];
  double n1s = -zetas*omegas;
  double omega1s = omegas*sqrt(fabs(zetas*zetas - 1));
  double Ts;
  double thalfs;


  if( (zetas*zetas - 1) > 0 ){
    lambdas[0] = -zetas*omegas + omegas*sqrt(zetas*zetas - 1);
    lambdas[1] = -zetas*omegas - omegas*sqrt(zetas*zetas - 1);
    printf("lambdas 1 = %lg\n", lambdas[0]);  
    printf("lambdas 2 = %lg\n", lambdas[1]);
  } else {
    printf("lambdas 1 = %lg + i%lg\n", n1s, omega1s);  
    printf("lambdas 2 = %lg - i%lg\n", n1s, omega1s);
    // Period and half-time
    Ts = 2*M_PI/omega1s;
    thalf = -0.69 / n1s;
    printf("Period = %lg\n", Ts);
    printf("t(1/2) = %lg\n", thalfs);
  }  

  return 0;
}

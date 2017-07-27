/*
 *
 * Mathematic model of the Cessna 172 plane.
 * We use a model in which the longitudinal dynamic is decoupled form the latero-directional dynamic.
 *
 */ 


#include <math.h>
#include <stdio.h>

void mathModel( double dy[12], double y[12], double mass, double surface, double wingspan, double chord, double steadyStateCoefficients[][126], double YForceDerivatives[][126], double ZForceDerivatives[][126], double RollingMomentDerivatives[][126], double PitchingMomentDerivatives[][126], double YawingMomentDerivatives[][126], double  ControlForceDerivatives[][126], double ControlMomentDerivatives[][126], double Jx, double Jy, double Jz, double Jxz, double de, double da, double dr, double T ){

  int i;

  double u = y[0];
  double v = y[1];
  double w = y[2];
  double p = y[3];
  double q = y[4];
  double r = y[5];
  double phi = y[6];
  double theta = y[7];
  double psi = y[8];
  double xv = y[9];
  double yv = y[10];
  double zv = y[11];

  double Cx;
  double Cy;
  double Cz;
  double Cl;
  double Cm;
  double Cn;

  double Rho[1];
  atmoDensity( y[11], Rho ); 
  double rho = Rho[0];
  double V = sqrt( u*u + v*v + w*w );
  double alpha = atan2(w,u);
  double beta = atan2(v,u);
  double alphaDot = q - p*cos(alpha)*tan(beta) - r*sin(alpha)*tan(beta);
  double betaDot = p*sin(alpha) - r*cos(alpha);

  double X;
  double Y;
  double Z;
  double L;
  double M;
  double N;

  // calculating engine thrust
  double Tx = T;
  double Ty = 0;
  double Tz = 0;

  // interpolator 
  interp( &Cx, &Cy, &Cz, &Cl, &Cm, &Cn, steadyStateCoefficients, YForceDerivatives, ZForceDerivatives, RollingMomentDerivatives, PitchingMomentDerivatives, YawingMomentDerivatives, ControlForceDerivatives, ControlMomentDerivatives, alpha, beta, alphaDot, betaDot, p, q, r, V, de, da, dr, wingspan, chord );

  // calculating forces and moments
  X = Cx*0.5*rho*V*V*surface;
  Y = Cy*0.5*rho*V*V*surface;
  Z = Cz*0.5*rho*V*V*surface;
  L = Cl*0.5*rho*wingspan*V*V*surface;
  M = Cm*0.5*rho*chord*V*V*surface;
  N = Cn*0.5*rho*wingspan*V*V*surface;

  double uDot = 1/mass*( X - mass*q*w + mass*r*v - mass*9.81*sin(theta) + Tx );
  double vDot = 1/mass*( Y - mass*r*u + mass*p*w + mass*9.81*cos(theta)*sin(phi) + Ty );
  double wDot = 1/mass*( Z - mass*p*v + mass*q*u + mass*9.81*cos(theta)*cos(phi) + Tz );
  double pDot = 1/(Jx*Jz - Jxz*Jxz) * ( Jz*L + Jxz*N + Jz*Jxz*p*q - Jz*(Jz-Jy)*q*r + Jxz*(Jy-Jx)*p*q - Jxz*Jxz*q*r );
  double qDot = 1/Jy * ( M - (Jx-Jz)*p*r - Jxz*(p*p - r*r) );
  double rDot = 1/(Jx*Jz - Jxz*Jxz) * ( Jx*N + Jxz*L - Jx*Jxz*q*r - Jx*(Jy-Jx)*p*q - Jxz*(Jz-Jy)*q*r + Jxz*Jxz*p*q );
  double phiDot = p + q*tan(theta)*sin(phi) + r*tan(theta)*cos(phi);
  double thetaDot = q*cos(phi) - r*sin(phi);
  double psiDot = r*cos(phi)/cos(theta) + q*sin(phi)/cos(theta);
  double xDot = u*cos(psi)*cos(theta) + v*( cos(psi)*sin(theta)*sin(phi) - sin(psi)*cos(phi) ) + w*( cos(psi)*sin(theta)*cos(phi) + sin(psi)*sin(phi) ); 
  double yDot = u*sin(psi)*cos(theta) + v*( sin(psi)*sin(theta)*sin(phi) + cos(psi)*cos(phi) ) + w*( sin(psi)*sin(theta)*cos(phi) + cos(psi)*sin(phi) );
  double zDot = u*sin(theta) - v*cos(theta)*sin(phi) - w*cos(theta)*cos(phi);

  dy[0] = uDot; 
  dy[1] = vDot;
  dy[2] = wDot;
  dy[3] = pDot;
  dy[4] = qDot;
  dy[5] = rDot;
  dy[6] = phiDot;
  dy[7] = thetaDot;
  dy[8] = psiDot;
  dy[9] = xDot;
  dy[10] = yDot;
  dy[11] = zDot;

} 

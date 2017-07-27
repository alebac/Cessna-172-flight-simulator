/*
 *
 * interpolates coefficients from database for the specified flight conditions
 *
 */


#include <stdio.h>
#include <math.h>

void interp( double* CxPtr, double* CyPtr, double* CzPtr, double* ClPtr, double* CmPtr, double* CnPtr, double steadyStateCoefficients[][126], double YForceDerivatives[][126], double ZForceDerivatives[][126], double RollingMomentDerivatives[][126], double PitchingMomentDerivatives[][126], double YawingMomentDerivatives[][126], double  ControlForceDerivatives[][126], double ControlMomentDerivatives[][126], double alpha, double beta, double alphaDot, double betaDot, double p, double q, double r, double v, double de, double da, double dr, double wingspan, double chord ){

  int alphaIndex;

  alpha = alpha*180/M_PI;

  if( alpha < -5 ){
    alpha = -5;
    printf("Data out of range: alpha < -5\n");
  } else if( alpha > 20 ){
    alpha = 20;
    printf("Data out of range: alpha > 20\n");
  }

  alphaIndex = (alpha + 5) * 5;                // gives the index of the nearest minor alpha

  *CxPtr = steadyStateCoefficients[1][alphaIndex] + (steadyStateCoefficients[1][alphaIndex+1] - steadyStateCoefficients[1][alphaIndex]) * (alpha - steadyStateCoefficients[0][alphaIndex] ) / 0.2 + ControlForceDerivatives[1][alphaIndex] * de;
  *CyPtr = steadyStateCoefficients[2][alphaIndex] + (steadyStateCoefficients[2][alphaIndex+1] - steadyStateCoefficients[2][alphaIndex]) * (alpha - steadyStateCoefficients[0][alphaIndex] ) / 0.2 + YForceDerivatives[1][alphaIndex]*beta + YForceDerivatives[3][alphaIndex]*(p*(wingspan/2)/(2*v)) + YForceDerivatives[4][alphaIndex]*(r*(wingspan/2)/(2*v)) + ControlForceDerivatives[6][alphaIndex]*dr;
  *CzPtr = steadyStateCoefficients[3][alphaIndex] + (steadyStateCoefficients[3][alphaIndex+1] - steadyStateCoefficients[3][alphaIndex]) * (alpha - steadyStateCoefficients[0][alphaIndex] ) / 0.2 + ZForceDerivatives[4][alphaIndex]*(q*(chord/2)/(2*v)) + ZForceDerivatives[2][alphaIndex]*(alphaDot*(chord/2)/(2*v)) + ControlForceDerivatives[3][alphaIndex] * de;
  *ClPtr = steadyStateCoefficients[4][alphaIndex] + (steadyStateCoefficients[4][alphaIndex+1] - steadyStateCoefficients[4][alphaIndex]) * (alpha - steadyStateCoefficients[0][alphaIndex] ) / 0.2 + RollingMomentDerivatives[1][alphaIndex]*beta + RollingMomentDerivatives[3][alphaIndex]*(p*(wingspan/2)/(2*v)) + RollingMomentDerivatives[4][alphaIndex]*(r*(wingspan/2)/(2*v)) + ControlMomentDerivatives[1][alphaIndex] * da + ControlMomentDerivatives[2][alphaIndex] * dr;
  *CmPtr = steadyStateCoefficients[5][alphaIndex] + (steadyStateCoefficients[5][alphaIndex+1] - steadyStateCoefficients[5][alphaIndex]) * (alpha - steadyStateCoefficients[0][alphaIndex] ) / 0.2 + PitchingMomentDerivatives[2][alphaIndex]*(alphaDot*(chord/2)/(2*v)) + PitchingMomentDerivatives[4][alphaIndex]*(q*(chord/2)/(2*v)) + ControlMomentDerivatives[3][alphaIndex] * de;
  *CnPtr = steadyStateCoefficients[6][alphaIndex] + (steadyStateCoefficients[6][alphaIndex+1] - steadyStateCoefficients[6][alphaIndex]) * (alpha - steadyStateCoefficients[0][alphaIndex] ) / 0.2 + YawingMomentDerivatives[1][alphaIndex]*beta + YawingMomentDerivatives[3][alphaIndex]*(p*(wingspan/2)/(2*v)) + YawingMomentDerivatives[4][alphaIndex]*(r*(wingspan/2)/(2*v)) + ControlMomentDerivatives[5][alphaIndex] * da + ControlMomentDerivatives[6][alphaIndex] * dr;

}

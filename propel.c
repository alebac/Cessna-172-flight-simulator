/*
 *
 * Calculates propeller's thrust, torque and efficiency
 *
 */ 


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

// PROPEL 
void propel( double rpm, double rho, double v, int stationsNumber, double dataPropeller[], double propeller[][60], double resultsPropel[] ){
 
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
 
  int i=0;
 
  double chord;
  double pitch;
 
  double n=rpm/60.0;
  double omega=n*2.0*M_PI;
 
  double thrust=0.0;
  double torque=0.0;
  double radius;
  double theta = 0;
  double sigma;
  double a;
  double b;
  double a2[stationsNumber];
  double b2[stationsNumber];
  int finished;
  int startSpinner=0;
  double sum;
  double V0;
  double V2;
  double phi;
  double alpha;
  double cl;
  double cd;
  double Vlocal;
  double DtDr;
  double DqDr;
  double tem1;
  double tem2;
  double anew;
  double bnew;
  double t;
  double q;
  double J;
  double eff;
 
  i=0;
  while (propeller[1][i]<spinnerDiameter/2.0 && i<stationsNumber){
    i=i+1;
  }
  startSpinner=i;
 
 
  for(i=startSpinner; i<(stationsNumber ); i++){
    radius=propeller[1][i];
    chord = (propeller[2][i])*radius;
    theta=propeller[3][i]; /*[deg]*/
    a=0.1;
    b=0.01;
    finished=0;
    sum=1;
    while (finished==0){
      V0 = v *(1 + a);
      V2 = omega*radius*(1-b);
      phi = atan2(V0,V2);
      alpha = theta/180.0*M_PI - phi + a0Propeller;
      cl = ClalphaPropeller*(alpha-a0Propeller) + Cl0Propeller ;
      cd = Cd0Propeller + CdalphaPropeller*alpha + Cdalpha2Propeller*alpha*alpha;
      Vlocal = sqrt(V0*V0+V2*V2);                                                 // V1 nel disegno del pdf del prof
      DtDr=0.5*rho*Vlocal*Vlocal*bladeNumber *chord*(cl*cos(phi)-cd*sin(phi));
      DqDr=0.5*rho*Vlocal*Vlocal*bladeNumber *chord*radius*(cd*cos(phi)+cl*sin(phi));
      tem1=DtDr/(4.0*M_PI*radius*rho*v*v*(1+a));
      tem2=DqDr/(4.0*M_PI*radius*radius*radius*rho*v*(1+a)*omega);
      anew=0.5*(a+tem1);
      bnew=0.5*(b+tem2);
      if (fabs(anew-a)<1.0e-5){
        if (fabs(bnew-b)<1.0e-5){
          finished=1;
        }
      }
      a=anew;
      b=bnew;
      sum=sum+1;
      if (sum>500){
        finished=1;
      }
    } // end of while
    a2[i]=a;
    b2[i]=b;
    thrust=thrust+DtDr*(propeller[1][i] - propeller[1][i-1]);
    torque=torque+DqDr*(propeller[1][i] - propeller[1][i-1]);
  } // end of for
  t=thrust/(rho*n*n*diameter *diameter *diameter *diameter );
  q=torque/(rho*n*n*diameter *diameter *diameter *diameter *diameter );
  J=v/(n*diameter );
  if (t<0){
    eff=0;
  } else {
    eff=t/q*J/(2.0*M_PI);
  }
 
  resultsPropel[0] = thrust;
  resultsPropel[1] = torque;
  resultsPropel[2] = eff;
}

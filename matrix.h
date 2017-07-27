/* Declaration of functions */
void readMatrix( double matrix[][126], FILE * fPtr );
void readMatrix2( double matrix[][126], FILE * fPtr );
void readMatrix3( double matrix[][60], FILE * fPtr );
void printMatrix( double matrix[][126] );
void printMatrix2( double matrix[][126] );
void printMatrix3( double matrix[][60] );

void readDba( double dataDba[], double steadyStateCoefficients[][126], double XForceDerivatives[][126], double YForceDerivatives[][126], double ZForceDerivatives[][126], double RollingMomentDerivatives[][126], double PitchingMomentDerivatives[][126], double YawingMomentDerivatives[][126], double ControlForceDerivatives[][126], double ControlMomentDerivatives[][126], double RotaryDerivatives[][126] );

void readEngine( double dataEngine[] );

double atmoT( double h );
double atmoC( double h );
void atmoDensity( double h, double rho[] );
double atmoPressure( double h );

void propel( double rpm, double rho, double v, int stationsNumber, double dataPropeller[], double propeller[][60], double resultsPropel[] );

void interp( double* CxPtr, double* CyPtr, double* CzPtr, double* ClPtr, double* CmPtr, double* CnPtr, double steadyStateCoefficients[][126], double YForceDerivatives[][126], double ZForceDerivatives[][126], double RollingMomentDerivatives[][126], double PitchingMomentDerivatives[][126], double YawingMomentDerivatives[][126], double  ControlForceDerivatives[][126], double ControlMomentDerivatives[][126], double alpha, double beta, double alphaDot, double betaDot, double p, double q, double r, double v, double de, double da, double dr, double wingspan, double chord );

void mathModel( double dy[12], double y[12], double mass, double surface, double wingspan, double chord, double steadyStateCoefficients[][126], double YForceDerivatives[][126], double ZForceDerivatives[][126], double RollingMomentDerivatives[][126], double PitchingMomentDerivatives[][126], double YawingMomentDerivatives[][126], double  ControlForceDerivatives[][126], double ControlMomentDerivatives[][126], double Jx, double Jy, double Jz, double Jxz, double de, double da, double dr, double T );

void ode1( double mass, double specificConsumption, double wingspan, double surface, double chord, double Jx, double Jy, double Jz, double Jxz, double dt, int n, double steadyStateCoefficients[][126], double YForceDerivatives[][126], double ZForceDerivatives[][126], double RollingMomentDerivatives[][126], double PitchingMomentDerivatives[][126], double YawingMomentDerivatives[][126], double  ControlForceDerivatives[][126], double ControlMomentDerivatives[][126], double Y[][12], double y0[], double deTrim, double da, double dr, double T, double command[] );

void readInput( double input[], char* outputFileName );

void readPropeller( int* stationsNumberPtr, double dataPropeller[], double propeller[][60] );

void writeResults( double Y[][12], int n, double dt, char* outputFileName, double command[] );





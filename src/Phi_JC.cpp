#include <iostream>
#include <cmath>

double phi( double x );

// Same interface as Normals.hpp
constexpr double oneOverRootTwoPi = std::sqrt( 1.0/2.0/3.1415926 );

double normpdf(double x)
{
   return oneOverRootTwoPi*exp(-x*x/2);
}

double normcdf( double x )
{
  return phi(x);
}

// Code from http://www.johndcook.com/cpp_phi.html

double phi(double x)
{
    // constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;

    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x)/sqrt(2.0);

    // A&S formula 7.1.26
    double t = 1.0/(1.0 + p*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

    return 0.5*(1.0 + sign*y);
}

void testPhi()
{
    // Select a few input values
    double x[] = 
    {
        -3, 
        -1, 
        0.0, 
        0.5, 
        2.1 
    };

    // Output computed by Mathematica
    // y = Phi[x]
    double y[] = 
    { 
        0.00134989803163, 
        0.158655253931, 
        0.5, 
        0.691462461274, 
        0.982135579437 
    };

        int numTests = sizeof(x)/sizeof(double);

    double maxError = 0.0;
    for (int i = 0; i < numTests; ++i)
    {
        double error = fabs(y[i] - phi(x[i]));
        if (error > maxError)
            maxError = error;
    }

        std::cout << "Maximum error: " << maxError << "\n";
} 


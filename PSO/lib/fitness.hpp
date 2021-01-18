//#include "chromosome.hpp"
#include <assert.h>
#include <math.h>
#include <vector>
const double pi = acos(-1); 
/*
    https://en.wikipedia.org/wiki/Test_functions_for_optimization
*/

namespace fitness
{
    // Rastrigin Function
    inline double Rastrigin(const std::vector<double>& x){
        double result = 10*x.size();
        for (int i = 0; i < (int)x.size(); i++) 
            result += (x[i]*x[i] - 10*cos(2*pi*x[i]));
        return result;
    };
    
    //  Ackley Function
    inline double Ackley(const std::vector<double>& x){
        double p1 = -0.2*sqrt(0.5*(x[0]*x[0] + x[1]*x[1]));
        double p2 = 0.5*(cos(2*pi*x[0]) + cos(2*pi*x[1]));
        double result  = -20*exp(p1) - exp(p2) + exp(1.0) + 20;
        return result;
    };

    // Rosenbrock Function
    inline double Rosenbrock(const std::vector<double>& x){
       double result = 0.0;
       for (int i = 0; i < x.size() - 1; i++)
            result += (100*(x[i + 1] - x[i]*x[i])*(x[i + 1] - x[i]*x[i]) + (1 - x[i])*(1 - x[i]));
        return result;
    };

    // Eggholder Function
    inline double Eggholder(const std::vector<double>& x){
        double p1 = -(x[1] + 47)*sin(sqrt(fabs(x[0]/2.0 + (x[1] + 47))));
        double p2 = -x[0]*sin(sqrt(fabs(x[0] - (x[1] + 47))));
        double result = p1 + p2;
        return result;
    };

    inline double EvalFunc(const std::vector<double>& x,int type = 0){
        if (type == 0) return Rastrigin(x);
        if (type == 1) return Rosenbrock(x);
        if (type == 2) return Eggholder(x);
        return Ackley(x);
    }
}



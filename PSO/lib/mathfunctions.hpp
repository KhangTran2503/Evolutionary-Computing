#include <vector>
#include <assert.h>
#include <math.h>

namespace Math
{
    //Constrains
    inline std::pair<double,double> Constrains(int type_function){
        //if (type == 0) return Rastrigin(x);
        if (type_function == 0) return std::make_pair(-5.12,5.12);

        //if (type == 1) return Rosenbrock(x);
        if (type_function == 1) return std::make_pair(-128,128);
        
        //if (type == 2) return Eggholder(x);
        if (type_function == 2) return std::make_pair(-512,512);        
        
        //if (type == 3) reuturn Ackley(x);
        return std::make_pair(-5,5);
    };

    // Global minimum
    inline std::vector<double> Global_minimum(int dim,int type_function){
        //if (type == 0) return Rastrigin(x);
        std::vector<double> gminimum;
        if (type_function == 0){
            gminimum.assign(dim,0);
            return gminimum;
        }
        
        //if (type == 1) return Rosenbrock(x);
        if (type_function == 1){
            gminimum.assign(dim,0);
            return gminimum;
        }
        
        //if (type == 2) return Eggholder(x);
        if (type_function == 2){
            gminimum.assign(dim,-959.6704);        
            return gminimum;
        }

        //if (type == 3) reuturn Ackley(x);
        gminimum.assign(dim,0);
        return gminimum;
    };

    // Mean
    template<typename T>
    inline double mean(const std::vector<T>& parameters){
        assert(!parameters.empty());
        double Mean = 0.0;
        for (T x: parameters)
            Mean += (double)x;

        Mean /= (double)(parameters.size());
        return Mean;
    }
    
    /*
    inline double mean(const std::vector<double>& parameters){
        assert(parameters.empty());
        double Mean = 0.0;
        for (int x: parameters)
            Mean += (double)x;

        Mean /= (double)(parameters.size());
        return Mean;
    }
    */
    //  Standard 
    template<typename T>
    inline double std(const std::vector<T>& parameters){
        assert(!parameters.empty());

        if (parameters.size() == 1) return 0.0;
        double Mean = 0.0;
        for (T x: parameters)
            Mean += (double)x;

        Mean /= (double)(parameters.size());
        // Calculate std
        double Std = 0.0;
        for (int x: parameters) Std += ((double)x - Mean)*((double)x - Mean);
        Std /= ((double)(parameters.size()) - 1);
        Std = std::sqrt(Std);
        return Std;
    };
}



#include <vector>
#include <assert.h>
#include <math.h>
/*
    Reference: LTGA.c 
    Author   : Peter A.N. Bosman, Dirk Thierens
*/
namespace Math
{
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



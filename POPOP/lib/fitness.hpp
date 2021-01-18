#include "chromosome.hpp"
#include <assert.h>
/*
    Reference: LTGA.c 
    Author   : Peter A.N. Bosman, Dirk Thierens
*/

namespace fitness
{
    // Onemax Function Problem Evaluation
    inline int Onemax(const std::vector<int>& parameters){
        int result = 0;
        for (int bit: parameters) result += bit;
        return result;
    }
    
    //  Deceptive TrapK Tight Encoding Function Problem Evaluation
    inline int TrapKTightEncoding(const std::vector<int>& parameters,int K = 5){
        int number_of_parameters = parameters.size();
        assert(number_of_parameters % K == 0);

        int m = number_of_parameters / K;

        int result = 0;
        int sum_range = 0;
        for (int i = 0; i < m; i++){
            sum_range  = 0;
            for (int j = 0; j < K; j++)
                sum_range += parameters[i*K + j];
            
            if (sum_range == K) result += K;
            else result += (K - 1 - sum_range);
            //else result += ((double)(K - 1 - sum_range))/((double)K);
        }
        return result;
    };
}



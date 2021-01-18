#include <vector>
#include <random>
#include <algorithm>

namespace Random
{
    // Declare
    static std::random_device rdev{};
    static std::mt19937 mt_gen(rdev());

    // Functons 
    inline std::vector<int> permutation_random(int len){
        std::vector<int> per(len);
        for (int i = 0; i < len; ++i) per[i] = i;
        //mt_gen.seed(seed);
        shuffle(per.begin(),per.end(),mt_gen);
        return per;
    };

    inline void permutation_random(std::vector<int>& per){
        shuffle(per.begin(),per.end(),mt_gen);
    };

    
    inline double uniform_real(double low = 0,double high = 1){
        //mt_gen.seed(seed);
        //std::cout<< mt_gen << '\n';
        std::uniform_real_distribution<double> distrib(low,high);
        return distrib(mt_gen);
    };

    // low <= random <= high
    inline int uniform_int(int low,int high){
        //mt_gen.seed(seed);
        std::uniform_int_distribution<> distrib(low,high);
        return distrib(mt_gen);
    };
    
    // random vector (low,high)
    inline std::vector<double> random_vector(int dim,double low = 0,double high = 1){
        std::vector<double> x(dim);
        std::uniform_real_distribution<double> distrib(low,high);
        for (int i = 0; i < dim; i++) x[i] = distrib(mt_gen);
        return x;
    };

    /*
    inline std::vector<std::vector<int>> random_table(int height,int width){
        std::vector<std::vector<int>> table(height,std::vector<int> (width,0));
        int half_height = height >> 1;
        for (int i = 0; i < half_height; i++)
            for (int j = 0; j < width; j++) table[i][j] = 1;

        // Create permutation
        std::vector<int> per(height);
        for (int i = 0; i < height; i++) per[i] = i;

        std::vector<int> tmp(height);
        for (int j = 0; j < width; j++){
            shuffle(per.begin(),per.end(),mt_gen);    
            for (int i = 0; i < height; i++) tmp[per[i]] = table[i][j];
            for (int i = 0; i < height; i++) table[i][j] = tmp[i];
        } 
        return table;        
        
    };
    */
}



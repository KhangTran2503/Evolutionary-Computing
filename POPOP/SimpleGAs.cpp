#include <iostream>
#include <string>
#include <algorithm>
#include "./lib/myrandom.hpp"
#include "./lib/fitness.hpp"
#include "./lib/population.hpp"
#include "./lib/mathfunctions.hpp"
#include <tuple>
#include <map>
#include <fstream>
using namespace std;
const int MY_SEED = 18520072;

std::vector<int> problem_size{10,20,40,80,160};
//std::vector<std::string> problem_name{"10","20","40","80","160"};
std::map<int,std::string> file_name;
std::vector<std::string> fitness_name{"OneMax","Trap5"};
std::vector<std::string> crossover_name{"OX","UX"};
std::vector<std::string> out_name{"Evaluations","MRPS"};
std::ofstream f_summary ("./data/summary.txt",std::ofstream::trunc | std::ofstream::out);

/*-=-=-=-=-=-=-=-=-=-=-=-=- Bisection -=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 * 
 */
std::tuple<double,bool> run_multiple_times(int Pop_size,int solution_size,int type_fitness,int type_crossover,int random_seed,int times = 10){
    double avg_evals = 0;

    for (int i = 0; i < times; i++){
        //std::cout << "random_seed:\t" << random_seed + i << '\n';
        Population P(Pop_size,solution_size,4,type_fitness,type_crossover,random_seed + i);
        P.Evolution();

        if (P.best_chromosome.self_fitness < solution_size){
            return std::make_tuple(-1,false); 
        }

        avg_evals += (double)P.number_of_evaluations;
        //random_seed++;
    }
    //std::cout << "----------------------------------------\n";
    avg_evals /= times;
    return std::make_tuple(avg_evals,true);
} 

std::tuple<int,double,bool> get_MRPS_upper_bound(int solution_size,int type_fitness,int type_crossover,int random_seed){
    int N_upper = 4;
    double avg_evals;
    bool success = false;
    do{
        std::tuple<double,bool> T = run_multiple_times(N_upper,solution_size,type_fitness,type_crossover,random_seed);
        tie(avg_evals,success) = T;
        if (success) break;
        N_upper *= 2;
    }
    while (N_upper <= 8192);
    return std::make_tuple(N_upper,avg_evals,success);
}

std::tuple<double,int> find_MRPS(double avg_evals,int Pop_size,int solution_size,int type_fitness,int type_crossover,int random_seed){
    int Low = 1;
    int High= (Pop_size >> 1);
    int MRPS = Pop_size;
    double res_evals = avg_evals, evals;
    bool success;

    while (Low <= High) {
        int Mid = (Low + High) >> 1;
        std::tuple<double,bool> T = run_multiple_times(Mid << 1,solution_size,type_fitness,type_crossover,random_seed);
        tie(evals,success) = T;
        if (success){
            MRPS = Mid << 1;
            res_evals = evals;
            High = Mid - 1;
        }
        else Low = Mid + 1;
    }

    return std::make_tuple(res_evals,MRPS);

}

std::tuple<double,int,bool> bisection(int solution_size,int type_fitness,int type_crossover,int random_seed){
    // get MRPS 
    int N_upper;
    double evals_upper;
    bool success;
    std::tuple<int,double,bool> T1 = get_MRPS_upper_bound(solution_size,type_fitness,type_crossover,random_seed);
    tie(N_upper,evals_upper,success) = T1;

    if (!success) return std::make_tuple(-1.0,-1,false);
    f_summary << "N upper:\t" << N_upper << '\t';
    // if not success
    int MRPS;
    double avg_evals;
    std::tuple<double,int> T2 = find_MRPS(evals_upper,N_upper,solution_size,type_fitness,type_crossover,random_seed);
    tie(avg_evals,MRPS) = T2;
    f_summary << "MRPS:\t" << MRPS << '\n';

    return std::make_tuple(avg_evals,MRPS,true);

}

void run_bisection_multiple_times(int solution_size,int type_fitness,int type_crossover,int random_seed = MY_SEED,int times = 10){
    std::vector<int> number_of_evaluations;
    std::vector<double> MRPS;
    bool fail = false;
    for (int i = 0; i < times; ++i){
        // bisection 10 times
        double avg_evals;
        int mprs;
        bool success;
        std::tuple<double,int,bool> T = bisection(solution_size,type_fitness,type_crossover,random_seed + 10*i);
        tie(avg_evals,mprs,success) = T;
        if (!success){
            fail = true;
            f_summary << "Fail!\n";
            continue;
        }
        number_of_evaluations.emplace_back(avg_evals);
        MRPS.emplace_back(mprs);
        //random_seed += 10;
    }

    
    if (!fail){
        f_summary << "Problem Size:\t" << solution_size << '\n';
        f_summary << "Number of evaluation Mean(std):\t" << Math::mean(number_of_evaluations) << '(' << Math::std(number_of_evaluations) << ")\n";
        f_summary << "MRPS Mean(std)                :\t" << Math::mean(MRPS) << '(' << Math::std(MRPS) << ")\n";
        f_summary << '\n';
    }
    else{
        f_summary << "Problem Size:\t" << solution_size << '\n';
        f_summary << "Number of evaluation Mean(std):\t" << -1 << '(' << 0 << ")\n";
        f_summary << "MRPS Mean(std)                :\t" << -1 << '(' << 0 << ")\n";
        f_summary << '\n';
    } 

    // Output file

    std::string dir_path;
    for (int type = 0; type < 2; ++type){   
        dir_path = "./data/" + out_name[type] + "/" + fitness_name[type_fitness] + "_" + crossover_name[type_crossover] + "_" + std::to_string(solution_size) + ".txt";
        std::cout << dir_path << std::endl;
        std::ofstream fo (dir_path,std::ofstream::trunc| std::ofstream::out); 
        if (fail){
            for (int iter = 0; iter < times; ++iter) fo << -1 << ' ';
        }
        else {
            if (type == 0) for (double x: number_of_evaluations) fo << x << ' ';
            else for (double x: MRPS) fo << x << ' ';
        }
        fo.close();

    }
    
    //=-=-=-=-=-=-=-=-=
    
}

/*-=-=-=-=-=-=-=-=-=-=-=-=- File -=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 * 
 */
void Init_Filename(){
    file_name[0] = "OneMax_OnePoint";
    file_name[1] = "OneMax_Uniform";
    file_name[2] = "Trap5_OnePoint";
    file_name[3] = "Trap5_Uniform";
}

// Population(int Pop_size,int chromo_size,int tournament_size,int type_fitness,int type_crossover,int seed);
int main(){

    Init_Filename();
    //ofstream fo("./data/" + file_name[0] + ".txt"); 

    //fo << "?";
    
    //return 0;

    for (int type = 0; type < 4; type++){
        int type_fitness = (type >> 1) & 1;
        int type_crossover = type & 1;
        f_summary << "************************* " + file_name[type] + " ****************************\n";
        for (int i = 0; i < 5; i++)
            run_bisection_multiple_times(problem_size[i],type_fitness,type_crossover);
        f_summary << "\n";
        
    }
    f_summary.close();
    return 0;
}

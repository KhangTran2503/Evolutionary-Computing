#include <iostream>
#include <string>
#include <algorithm>
#include "./lib/myrandom.hpp"
#include "./lib/fitness.hpp"
#include "./lib/swarm.hpp"
#include "./lib/mathfunctions.hpp"
#include "./lib/operator.hpp"
#include <iomanip>
#include <map>
#include <fstream>
using namespace std;
const int MY_SEED = 18520072;

std::vector<int> problem_size{128,256,512,1024,2048};
std::vector<std::string> problem_name{"128","256","512","1024","2048"};
std::map<int,std::string> file_name;
std::vector<std::string> Function_name{"Rastrigin","Rosenbrock","Eggholder","Ackley"};
std::vector<std::string> Topology_name{"Star","Ring"};
/*std::ofstream f_summary ("./data/summary.txt",std::ofstream::trunc | std::ofstream::out);
*/






/*
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

void Run1(int max_iter = 50,int pop_size = 32){
    std::ofstream f_summary1("./data/Run1/summary1.txt",std::ofstream::trunc | std::ofstream::out);
    
    for (int type_topology = 0; type_topology < 2; ++type_topology){
        for (int type_fitness = 0; type_fitness < 4; ++type_fitness){
            Swarm P(pop_size,2,max_iter,type_fitness,type_topology,0,MY_SEED);
            P.Evolution();
            std:string F_T = '(' + Function_name[type_fitness] + ',' + Topology_name[type_topology] + ')';
            f_summary1 << F_T << '\t' << P.best_particle.best_par << '\t' << std::fixed << std::setprecision(10) << P.best_particle.best_fitness << '\n';

        }
    }

    f_summary1.close();
}


void Run2(){
    std::string dir_path = "./data/Run2/";
    for (int type_topology = 0; type_topology < 2; type_topology++){
        std::string dir_path2 = dir_path + Topology_name[type_topology] + '/'; 
        for (int type_fitness = 0; type_fitness < 2; type_fitness++){
            std::string summary_name = dir_path2 + Function_name[type_fitness] + "_summary.txt";
            std::cout << summary_name << '\n';
            std::ofstream f_summary(summary_name,std::ofstream::trunc | std::ofstream::out);
            
            for (int i = 0; i < 5; i++){
                std::string file_name = dir_path2 + Function_name[type_fitness] + '_' + problem_name[i] + ".txt";
                std::cout << file_name << '\n';
                std::ofstream f_file(file_name,std::ofstream::trunc | std::ofstream::out);
                
                std::vector<double> result;
                for (int seed = MY_SEED; seed < MY_SEED + 10; seed++){
                    Swarm P(problem_size[i],10,100,type_fitness,type_topology,1,seed);
                    P.Evolution();
                    result.push_back(P.best_particle.best_fitness);
                    f_file << "Random Seed: " << seed << '\t';
                    f_file << "Solution: " << P.best_particle.best_par << '\t' << "Fitness: "<< std::fixed << std::setprecision(10) << P.best_particle.best_fitness << '\n';
                }
                f_file.close();
                
                f_summary << "Problem Size: " << problem_size[i] << '\t';
                f_summary << "Mean Fitness: " << Math::mean(result) << '\t';
                f_summary << "Std Fitness: " << Math::std(result) << '\n';
                //return;
                // f.close()

            }

            f_summary.close();
        }
    }
}

// Swarm(int Pop_size,int dim,int maximum_number_of_gen,int type_fitness,int type_topology,int type_termination,int seed);
int main(int argc, char *argv[]){

    std::string type_run(argv[1]);
    if (type_run == "1") Run1();
    else if (type_run == "2") Run2();
    else std::cout << "Invalid!\n";
    return 0;
}

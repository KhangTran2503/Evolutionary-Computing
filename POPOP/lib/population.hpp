#ifndef POPULATION_H
#define POPULATION_H
#include "chromosome.hpp"
#include <vector>

class Population{
    private:
        double crossover_rate;
        double mutation_rate;
        int tournament_size;
        int type_fitness;
        int type_crossover;
        int seed;
        //bool checkFitnessVarianceTermination();
        bool CheckNumberOfEvaluationsTerminationCondition();
        void UpdateBestPrevGenSolution();
        void PrintGeneration(int generation_th);
    public:
        std::vector<chromosome> Pop;
        std::vector<chromosome> Pool;
        chromosome best_chromosome;
        int Pop_size;
        int chromo_size;
        int number_of_evaluations;
        // get mean and standard deviation of population
        double mean_of_population, std_of_population;
    
        Population();
        // Constructor
        Population(int Pop_size,int chromo_size,int tournament_size,int type_fitness,int type_crossover,int seed);

        // Copying Constructor
        Population(const Population& other);
        
        // Assignment Operator
        Population& operator=(const Population& other);

        // Create random population
        void InitPopulation();
        
        // Variation Operator
        std::pair<chromosome,chromosome> UX(const chromosome& parent1,const chromosome& parent2);
        std::pair<chromosome,chromosome> OX(const chromosome& parent1,const chromosome& parent2);
        //chromosome mutation(const std::vector<int>& parent);
        
        // Create Pool
        void Gene_Pool();

        // Tourament Selection
        void Tourament_Selection();

        //Criteria
        bool CheckTerminationCondition();
        
        void Evolution();
        // Deconstructor
        ~Population();
};  


#endif // !POPULATION_H
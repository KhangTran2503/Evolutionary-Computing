#ifndef SWARM_H
#define SWARM_H
#include "particle.hpp"
#include <vector>

class Swarm{
    private:
        int type_fitness;
        int type_topology; // 0: star topology, 1: ring topology
        int type_termination; // 0: maximum_number_of_gen , 1: maximum_number_of_evaluations
        int seed;
        int maximum_number_of_gen;
        int number_of_evaluations;
        int number_of_improvement;
        //bool checkFitnessVarianceTermination();
        bool CheckNumberOfEvaluationsTerminationCondition();
        bool CheckNumberOfGenerationsTerminationCondition();
        bool checkFitnessVarianceTermination();
        bool CheckNumberOfImprovementTerminationCondition();
        void UpdateBestParticle();
        int Topology(int idx);
        int RingTopo(int idx);
        int StarTopo(int idx);
        void PrintGeneration(int generation_th);
    public:
        std::vector<particle> Pop;
        particle best_particle;
        int Pop_size;
        int dim;
        int number_of_gen;
        // get mean and standard deviation of Swarm
        //double mean_of_Swarm, std_of_Swarm;
    
        Swarm();
        // Constructor
        Swarm(int Pop_size,int dim,int maximum_number_of_gen,int type_fitness,int type_topology,int type_termination,int seed);

        // Copying Constructor
        Swarm(const Swarm& other);
        
        // Assignment Operator
        Swarm& operator=(const Swarm& other);

        // Create random Swarm
        void InitSwarm();
        
        // Move on landscapes
        void Move();

        //Criteria
        bool CheckTerminationCondition();
        
        void Evolution();
        // Deconstructor
        ~Swarm();
};  


#endif // !SWARM_H
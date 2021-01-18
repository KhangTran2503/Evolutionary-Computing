#include "../lib/swarm.hpp"
#include "../lib/myrandom.hpp"
#include "../lib/particle.hpp"
#include "../lib/operator.hpp"
#include <utility>
#include <iostream>

//============ INIT =================
const double W = 0.7298;
const double C1 = 1.49618;
const double C2 = 1.49618;
const int MAX_NUMBER_OF_EVALUATIONS = 1000000;
const int MAX_NOT_IMPROVEMENT = 100;

//===================================
// operator for vector





//=====================================





bool Swarm::checkFitnessVarianceTermination(){
    double objective_avg, objective_var;
    objective_avg = 0.0;
    
    for (int i = 0; i < (this->Pop_size); i++) objective_avg += (double)(this->Pop)[i].best_fitness;
    objective_avg /= (double)(this->Pop_size);

    objective_var = 0.0;
    for (int i = 0; i < (this->Pop_size); i++) {
        double objective_fitness = (this->Pop[i]).best_fitness;
        objective_var += (double)(objective_fitness - objective_avg)*(double)(objective_fitness - objective_avg);
    } 

    objective_var /= (double)this->Pop_size;
    if (objective_var < 1e-5) return true;
    return false;
}





Swarm::Swarm(){
    (this->number_of_evaluations) = 0;
}



Swarm::Swarm(int Pop_size,int dim,int maximum_number_of_gen,int type_fitness,int type_topology,int type_termination,int seed){
    (this->Pop_size)    = Pop_size;
    (this->dim)         = dim;
    (this->maximum_number_of_gen) = maximum_number_of_gen;
    (this->type_fitness) = type_fitness;
    (this->type_topology) = type_topology;
    (this->number_of_evaluations) = 0;
    (this->seed) = seed;
    (this->type_termination) = type_termination;
    (this->number_of_gen) = 0;
    (this->number_of_improvement) = 0;
    //(this->mutation_rate) = 0.0;
    Random::mt_gen.seed(this->seed);
}

Swarm::Swarm(const Swarm& other){
    (this->seed)            = other.seed;
    (this->Pop)             = other.Pop;
    (this->Pop_size)        = other.Pop_size;
    (this->dim)     = other.dim;
    (this->type_fitness)    = other.type_fitness;
    (this->type_topology)  = other.type_topology;
    (this->type_termination)    = other.type_termination;
    (this->best_particle) = other.best_particle;
    (this->number_of_evaluations) = other.number_of_evaluations;
    (this->maximum_number_of_gen) = other.maximum_number_of_gen;
    (this->number_of_gen) = other.number_of_gen;
    (this->number_of_improvement) = other.number_of_improvement;
}

Swarm& Swarm::operator=(const Swarm& other){
    if (this != &other){
        (this->seed)            = other.seed;
        (this->Pop)             = other.Pop;
        (this->Pop_size)        = other.Pop_size;
        (this->dim)     = other.dim;
        (this->type_fitness)    = other.type_fitness;
        (this->type_topology)  = other.type_topology;
        (this->type_termination)    = other.type_termination;
        (this->best_particle) = other.best_particle;
        (this->number_of_evaluations) = other.number_of_evaluations;
        (this->maximum_number_of_gen) = other.maximum_number_of_gen;
        (this->number_of_gen) = other.number_of_gen;
        (this->number_of_improvement) = other.number_of_improvement;
    }
    return *this;
}

// Init Swarm
void Swarm::InitSwarm(){
    for (int iter = 0; iter < (this->Pop_size); iter++){
        (this->Pop).push_back(particle(this->dim,this->type_fitness));
        //std::cout << (this->Pop).back().best_par << ' ';
        (this->number_of_evaluations)++;
    }
}

//=================== Topology =========================
// return index of best particle in Topology
int Swarm::Topology(int idx){
    if (this->type_topology == 0) return StarTopo(idx);
    return RingTopo(idx);
}

// StarTopology
int Swarm::StarTopo(int idx){
    double BestStarFitness = Pop[idx].best_fitness;
    int indexBestStar = idx;
    for (int i = 0; i < (this->Pop_size); i++)
        if ((this->Pop[i]).best_fitness <= BestStarFitness){
            indexBestStar = i;
            BestStarFitness = (this->Pop[i]).best_fitness;
        }
    return indexBestStar;
}

// RingTopology
int Swarm::RingTopo(int idx){
    double BestStarFitness = Pop[idx].best_fitness;
    int indexBestStar = idx;
    for (int i = -1; i < 2; i++){
        // cur_idx = idx - 1, idx, idx + 1
        int cur_idx = (idx + i + (this->Pop_size)) % (this->Pop_size);
        if ((this->Pop[cur_idx]).best_fitness <= BestStarFitness){
            indexBestStar = cur_idx;
            BestStarFitness = (this->Pop[cur_idx]).best_fitness;
        }
    }
    return indexBestStar;
}

void Swarm::Move(){
    int index_best_generation;
    //if (this->type_topology == 0) index_best_generation = this->StarTopo(0);

    std::vector<std::vector<double>> new_vels(this->Pop_size);
    for (int i = 0; i < (this->Pop_size); i++){
        if (this->type_topology == 1) index_best_generation = this->RingTopo(i);
        else index_best_generation = this->StarTopo(i);
        // calulate new vector vel
        // Inertia
        std::vector<double> Inertia = W*(this->Pop[i]).vel;
        //std::cout << "Inertia: " << Inertia << ' ';
        
        // Cognitive
        std::vector<double> Cognitive = C1*Random::uniform_real()*((this->Pop[i]).best_par - (this->Pop[i]).parameters);
        //std::cout << "Cognitive: " << Cognitive << ' ';
        
        // Social
        std::vector<double> Social = C2*Random::uniform_real()*((this->Pop[index_best_generation]).best_par - (this->Pop[i]).parameters);
        //std::cout << "Social: " << Social << ' ';

        //std::vector<double> new_vel = Inertia + Cognitive + Social;
        new_vels[i] = Inertia + Cognitive + Social;
    }

    for (int i = 0; i < (this->Pop_size); i++){
        //update particle with new_vel
        (this->Pop[i]).update(new_vels[i]);

        // update number of evaluations
        (this->number_of_evaluations)++;
        
        // Check number of evaluations termination condition
        if (CheckNumberOfEvaluationsTerminationCondition()) break;
    }
}


//================== Termination Condition ==================
bool Swarm::CheckNumberOfEvaluationsTerminationCondition(){
    if (this->type_termination == 0) return false;
    return (this->number_of_evaluations > MAX_NUMBER_OF_EVALUATIONS);
}

bool Swarm::CheckNumberOfGenerationsTerminationCondition(){
    if (this->type_termination == 1) return false;
    return (this->number_of_gen >= this->maximum_number_of_gen);
}

bool Swarm::CheckNumberOfImprovementTerminationCondition(){
    return (this->number_of_improvement >= MAX_NOT_IMPROVEMENT);
};

bool Swarm::CheckTerminationCondition(){
    //if (this->CheckNumberOfImprovementTerminationCondition()) return true;
    if (this->type_termination == 0) return this->CheckNumberOfGenerationsTerminationCondition();
    return this->CheckNumberOfEvaluationsTerminationCondition();
}




void Swarm::UpdateBestParticle(){
    // Find index of best particle in Swarm 
    double BestFitness = best_particle.best_fitness;
    int index_best = -1;
    for (int i = 0; i < (this->Pop_size); i++)
        if ((this->Pop[i]).best_fitness < BestFitness){
            BestFitness = (this->Pop[i]).best_fitness;
            index_best = i;
        }

    //Update best particle
    if (index_best > 0) {
        best_particle = (this->Pop[index_best]);
        this->number_of_improvement = 0;
    } else (this->number_of_improvement)++; 
}

void Swarm::PrintGeneration(int generation_th){
    std::cout << "******************************************\n";
    std::cout << "*           Generation: " << generation_th << "                *\n";
    std::cout << "******************************************\n";
    /*
    std::cout << "---------- Swarm --------------------\n";
    for (int i = 0; i < (this->Pop_size); i++){
        std::cout << '\t';
        //for (int x: (this->Pop)[i].best_par) std::cout << x;
        std::cout << (this->Pop[i]).best_par;
        std::cout << '\t' << "Fitness:\t" << (this->Pop)[i].best_fitness << '\n';
    }
    */
    std::cout << "---------- Best Solution ------------------" << "\n\n";
    //std::cout << '\t';
    //for (int x: (this->best_particle).best_par) std::cout << x;
    //std::cout << (this->best_particle).best_par;
    std::cout << '\t' << "Fitness:\t" << (this->best_particle).best_fitness << '\n';
    std::cout << '\v';
    
}

void Swarm::Evolution(){
    this->InitSwarm();
    this->UpdateBestParticle();
    //int generation_th = 0;
    this->PrintGeneration(this->number_of_gen);
    while (!(this->CheckTerminationCondition())){
        // Move on landscapes
        this->Move();
        
        //Update best particle
        this->UpdateBestParticle();
        // Print generation_th
        this->number_of_gen++;
        this->PrintGeneration(this->number_of_gen);
    }

    this->UpdateBestParticle();
}



Swarm::~Swarm(){}





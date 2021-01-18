#include "../lib/population.hpp"
#include "../lib/myrandom.hpp"
#include "../lib/chromosome.hpp"
#include <utility>
#include <iostream>

/*
bool Population::checkFitnessVarianceTermination(){
    double objective_avg, objective_var;
    objective_avg = 0.0;
    
    for (int i = 0; i < (this->Pop_size); i++) objective_avg += (double)(this->Pop)[i].self_fitness;
    objective_avg /= (double)(this->Pop_size);

    objective_var = 0.0;
    for (int i = 0; i < (this->Pop_size); i++) {
        double objective_fitness = (this->Pop[i]).self_fitness;
        objective_var += (double)(objective_fitness - objective_avg)*(double)(objective_fitness - objective_avg);
    } 

    objective_var /= (double)this->Pop_size;
    if (objective_var < 1e-3) return true;
    return false;
}
*/

bool Population::CheckNumberOfEvaluationsTerminationCondition(){
    // In this problem, we use Number of Evaluations is 1.
    for (int i = 1; i < (this->Pop_size); i++)
        if ((this->Pop)[i].chromo != (this->Pop)[0].chromo) return false;    
    return true;
}


Population::Population(){
    (this->number_of_evaluations) = 0;
    (this->crossover_rate) = 1.0;
}



Population::Population(int Pop_size,int chromo_size,int tournament_size,int type_fitness,int type_crossover,int seed){
    (this->Pop_size)  = Pop_size;
    (this->chromo_size) = chromo_size;
    (this->tournament_size) = tournament_size;
    (this->type_fitness) = type_fitness;
    (this->type_crossover) = type_crossover;
    (this->seed) = seed;
    (this->number_of_evaluations) = 0;
    (this->crossover_rate) = 1.0;
    //(this->mutation_rate) = 0.0;
    Random::mt_gen.seed(this->seed);
}

Population::Population(const Population& other){
    (this->crossover_rate)  = other.crossover_rate;
    (this->mutation_rate)   = other.mutation_rate;
    (this->seed)            = other.seed;
    (this->tournament_size) = other.tournament_size;
    (this->Pop)             = other.Pop;
    (this->Pop_size)        = other.Pop_size;
    (this->chromo_size)     = other.chromo_size;
    (this->type_fitness)    = other.type_fitness;
    (this->type_crossover)  = other.type_crossover;
    (this->best_chromosome) = other.best_chromosome;
    (this->Pool)            = other.Pool;
    (this->number_of_evaluations) = other.number_of_evaluations;
}

Population& Population::operator=(const Population& other){
     if (this != &other){
        (this->crossover_rate) = other.crossover_rate;
        (this->mutation_rate) = other.mutation_rate;
        (this->seed) = other.seed;
        (this->tournament_size) = other.tournament_size;
        (this->Pop) = other.Pop;
        (this->Pop_size) = other.Pop_size;
        (this->chromo_size) = other.chromo_size;
        (this->type_fitness) = other.type_fitness;
        (this->type_crossover) = other.type_crossover;
        (this->best_chromosome) = other.best_chromosome;
        (this->Pool)  = other.Pool;
        (this->number_of_evaluations) = other.number_of_evaluations;
    }
    return *this;
}

// Init Population
void Population::InitPopulation(){
    std::vector<std::vector<int>> table = Random::random_table(this->Pop_size,this->chromo_size);
    for (std::vector<int> chromo: table){
        (this->Pop).push_back(chromosome(chromo,this->type_fitness));
        (this->number_of_evaluations)++;
        //(this->Pop).back().get_fitness(this->type_fitness);
    }
}

// Uniform crossover
std::pair<chromosome,chromosome> Population::UX(const chromosome& parent1,const chromosome& parent2){
    double r = Random::uniform_real();
    if (r >= (this->crossover_rate)) return std::make_pair(parent1,parent2);
    std::vector<int> child1 = parent1.chromo;
    std::vector<int> child2 = parent2.chromo;

    // uniform 
    for (int iter = 0; iter < (this->chromo_size); ++iter){
        r = Random::uniform_real();
        if (r < 0.5) std::swap(child1[iter],child2[iter]);
    }
    (this->number_of_evaluations) += 2;

    // return two children
    return std::make_pair(chromosome(child1,this->type_fitness),chromosome(child2,this->type_fitness));
}

// One point crossover
std::pair<chromosome,chromosome> Population::OX(const chromosome& parent1,const chromosome& parent2){
    double r = Random::uniform_real();
    if (r >= (this->crossover_rate)) return std::make_pair(parent1,parent2);
    std::vector<int> child1 = parent1.chromo;
    std::vector<int> child2 = parent2.chromo;

    int break_point = Random::uniform_int(1,(this->chromo_size) - 1);
    for (int iter = break_point; iter < this->chromo_size; ++iter) 
        std::swap(child1[iter],child2[iter]);
    
    (this->number_of_evaluations) += 2;

    // return two children
    return std::make_pair(chromosome(child1,this->type_fitness),chromosome(child2,this->type_fitness));
}

void Population::Gene_Pool(){
    Pool = Pop;
    std::vector<int> order = Random::permutation_random(this->Pop_size);
    
    for (int iter = 0; iter < (this->Pop_size) - 1; ++iter){
        std::pair<chromosome,chromosome> child;
        if (this->type_crossover == 0)
            child = OX(Pool[order[iter]],Pool[order[iter + 1]]);
        else child = UX(Pool[order[iter]],Pool[order[iter + 1]]);
        Pool.push_back(child.first);
        Pool.push_back(child.second);
    }
}   

void Population::Tourament_Selection(){
    std::vector<int> order = Random::permutation_random((this->Pool).size());

    std::vector<chromosome> selection(this->Pop_size);
    int from = 0, to = (this->tournament_size) - 1;
    int selection_size = selection.size();
    int Pool_size = (this->Pool).size();

    for (int i = 0; i < selection_size; i++){
        int index_best = from;
        for (int j = from + 1; j <= to; j++)
            if (Pool[order[index_best]].self_fitness <= Pool[order[j % Pool_size]].self_fitness){
                index_best = j % Pool_size;
            }
        
        selection[i] = Pool[order[index_best]];
        
        from += (this->tournament_size);
        to   += (this->tournament_size);
        if (to >= Pool_size){
            Random::permutation_random(order);
            from = 0;
            to = (this->tournament_size) - 1;
        }
    }
    Pop = selection;
}

bool Population::CheckTerminationCondition(){
    //if (this->checkFitnessVarianceTermination()) return true;
    if (this->CheckNumberOfEvaluationsTerminationCondition()) return true;
    return false;
}

void Population::UpdateBestPrevGenSolution(){
    int index_best = 0;
    for (int i= 1; i < (this->Pop_size); i++)
        if (Pop[i].self_fitness >= Pop[index_best].self_fitness) index_best = i;
    (this->best_chromosome) = Pop[index_best];
}

void Population::PrintGeneration(int generation_th){
    std::cout << "******************************************\n";
    std::cout << "*           Generation: " << generation_th << "                *\n";
    std::cout << "******************************************\n";
    std::cout << "---------- Population --------------------\n";
    for (int i = 0; i < (this->Pop_size); i++){
        std::cout << '\t';
        for (int x: (this->Pop)[i].chromo) std::cout << x;
        std::cout << '\t' << "Fitness:\t" << (this->Pop)[i].self_fitness << '\n';
    }
    std::cout << "---------- Best Solution ------------------" << "\n\n";
    std::cout << '\t';
    for (int x: (this->best_chromosome).chromo) std::cout << x;
    std::cout << '\t' << "Fitness:\t" << (this->best_chromosome).self_fitness << '\n';
    std::cout << '\v';
}

void Population::Evolution(){
    this->InitPopulation();
    this->UpdateBestPrevGenSolution();
    //int generation_th = 0;
    //this->PrintGeneration(generation_th);
    while (!(this->CheckTerminationCondition())){
        this->Gene_Pool();
        this->Tourament_Selection();
        this->UpdateBestPrevGenSolution();
        // Print generation_th
        //generation_th++;
        //this->PrintGeneration(generation_th);
    }
}



Population::~Population(){}





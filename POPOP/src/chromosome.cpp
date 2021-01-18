#include "../lib/chromosome.hpp"
#include "../lib/fitness.hpp"

chromosome::chromosome(){}

// Calculate self fitness
void chromosome::get_fitness(){
    if (type_fitness == 0) (this->self_fitness) = fitness::Onemax(this->chromo);
    else (this->self_fitness) = fitness::TrapKTightEncoding(this->chromo);
} 

// Costructor: init chromosome with chromo_size
chromosome::chromosome(int chromo_size,int type_fitness){
    this->chromo_size = chromo_size;
    this->type_fitness = type_fitness;
    this->get_fitness();
}

// Constructor: init chromosome with vector other_chromo
chromosome::chromosome(std::vector<int> other_chromo,int type_fitness){
    this->chromo_size = (int)other_chromo.size();
    this->chromo = other_chromo;
    this->type_fitness = type_fitness;
    this->get_fitness();
}

// Copy Constructor
chromosome::chromosome(const chromosome& other){
    this->chromo_size = other.chromo_size;
    this->self_fitness = other.self_fitness;
    this->chromo = other.chromo;
    this->type_fitness = other.type_fitness;
}

// Operations = 
chromosome& chromosome::operator=(const chromosome& other){
    if (this != &other){
        this->chromo_size = other.chromo_size;
        this->self_fitness = other.self_fitness;
        this->chromo = other.chromo;
        this->type_fitness = other.type_fitness;
    }
    return *this;
}


// Operations < for sorting
bool chromosome::operator<(const chromosome& other){
    return this->self_fitness > other.self_fitness;
}




// Deconstructor
chromosome::~chromosome(){} 


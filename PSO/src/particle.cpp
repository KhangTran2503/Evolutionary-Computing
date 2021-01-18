#include "../lib/particle.hpp"
#include "../lib/fitness.hpp"
#include "../lib/mathfunctions.hpp"
#include "../lib/myrandom.hpp"
#include "../lib/operator.hpp"
#include <limits>
#include <iostream>

particle::particle(){
    this->best_fitness = std::numeric_limits<double>::max()/10.0; 
}

// Calculate self fitness
void particle::get_fitness(){
    (this->self_fitness) = fitness::EvalFunc(this->parameters,this->type_fitness);
} 

// Costructor: init particle with dimentions
particle::particle(int dim,int type_fitness){
    this->dim = dim;
    this->type_fitness = type_fitness;
    
    // Random parameter
    std::pair<double,double> dom = Math::Constrains(type_fitness);
    //std::cout << dom.first << ' ' << dom.second << '\n';
    this->parameters = Random::random_vector(dim,dom.first,dom.second);
    (this->vel).assign(dim,0);
    //(this->vel) = 0.5*(Random::random_vector(dim,dom.first,dom.second) - (this->parameters));
    // Calculate fitness 
    this->get_fitness();

    this->best_par = (this->parameters);
    this->best_fitness = this->self_fitness;

}

// Constructor: init particle with vector other_particle
particle::particle(std::vector<double> other_particle,int type_fitness){
    this->dim = (int)other_particle.size();
    this->parameters = other_particle;
    this->type_fitness = type_fitness;
    (this->vel).assign(dim,0);
    this->get_fitness();
    this->best_fitness = this->self_fitness;
    this->best_par = this->parameters; 
}

// Copy Constructor
particle::particle(const particle& other){
    this->dim = other.dim;
    this->self_fitness = other.self_fitness;
    this->parameters = other.parameters;
    this->type_fitness = other.type_fitness;
    this->best_fitness = other.best_fitness;
    this->vel = other.vel;
    this->best_par = other.best_par;
}

// Operations = 
particle& particle::operator=(const particle& other){
    if (this != &other){
        this->dim = other.dim;
        this->self_fitness = other.self_fitness;
        this->parameters = other.parameters;
        this->type_fitness = other.type_fitness;
        this->best_fitness = other.best_fitness;
        this->best_par = other.best_par;
        this->vel = other.vel;
    }
    return *this;
}

// update velocity 
void particle::update(std::vector<double> new_vel){
    this->vel = new_vel;
    
    // add paramters 
    for (int i = 0; i < (this->dim); i++) (this->parameters)[i] += new_vel[i];

    // adjust velocity
    std::pair<double,double> dom = Math::Constrains(this->type_fitness);
    for (int i = 0; i < (this->dim); i++){
        if ((this->parameters)[i] < dom.first){
            (this->parameters)[i] = dom.first;
            //(this->vel)[i] = 0;
        }

        if ((this->parameters)[i] > dom.second){
            (this->parameters)[i] = dom.second;
            //(this->vel)[i] = 0;
        }
    }

    // calculate fitness
    this->get_fitness();

    // update best parameters
    if (this->self_fitness < this->best_fitness){
        this->best_fitness = this->self_fitness;
        this->best_par = this->parameters;
    }
}

// Operations < for sorting
bool particle::operator<(const particle& other){
    return this->best_fitness < other.best_fitness;
}




// Deconstructor
particle::~particle(){} 


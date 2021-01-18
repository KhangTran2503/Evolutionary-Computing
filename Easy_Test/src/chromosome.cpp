#include "../lib/choromosome.h"

chromosome::chromosome(std::string chro){
    this->chromomosome = chro;
    this->get_fitness();
}

chromosome::chromosome(int len){
    // random uniform int distribution
    std::random_devive rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0,126);
    //---------------------------------------------

    this->chromo = '';
    // Random gen
    for (int i = 0; i < len; i++){
        int num = distrib(gen);
        (this->chromo).push_back(char(num));
    }

    this->get_fitness();
}

chromosome::chromosome(const chromosome& other){
    this->chromo = other.chromo;
    this->fitness = other.fitness;
}

chromesome& chromosome::opreator=(const chromosome& other){
    if (this == &other) return *this;
    this->chromo = other.chromo;
    this->fitness = other.fitness;
    return *this;
}

void get_fitness(){
    int diff = 0;
    for (int i = 0; i < (this->chromo).size(); i++)
        if ((this->chromo)[i] != target[i]) diff++;
    
    this->fitness = diff; 
}

chromosome::~chromosome(){}





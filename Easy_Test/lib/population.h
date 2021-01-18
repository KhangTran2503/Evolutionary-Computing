#ifndef POPULATION_H
#define POPULATION_H
#include "chromosome.h"
#include <vector>
using namespace std;

class population
{
private:
    int pop_size;          // number of indivial in population
    double mutation_rate;  // mutation rate
    double crossover_rate; // crossover rate
    int elitism;           // number of elitism 
    vector<chromosome> P;  // population
public:
    population();
    

    ~population();

}
#endif // !POPULATION_H

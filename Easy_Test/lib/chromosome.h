#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <string>
#include <utility>


class chromosome
{
private:
    /* data */
    std::string chromo;      // chromosome or individual (solution)
    void get_fitness();  // function evaluation fitness
public:
    int fitness;
    chromosome(int len);             // Constructor
    chromosome(std::string chro);
    chromosome(const chromosome& other); // Copy Contructor
    chromosome& operator=(const chromosome& other); // 
    ~chromosome();
};




#endif // !

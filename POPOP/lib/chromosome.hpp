#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <vector>
#include <utility>

class chromosome{
    private:
        void get_fitness();
        int type_fitness;
    public:
        int chromo_size;
        std::vector<int> chromo;
        int self_fitness;
        chromosome();
        chromosome(int chromo_size,int type_fitness);
        chromosome(std::vector<int> other_chromo,int type_fitness);
        chromosome(const chromosome& other);
        chromosome& operator=(const chromosome& other);
        bool operator < (const chromosome& other);
        ~chromosome();
};

#endif // !
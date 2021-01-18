#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>
#include <utility>

class particle{
    private:
        void get_fitness();
        int type_fitness;
    public:
        int dim;
        
        std::vector<double> parameters;
        std::vector<double> vel;
        std::vector<double> best_par;
        double best_fitness;
        double self_fitness;
        particle();
        particle(int dim,int type_fitness);
        particle(std::vector<double> other_particle,int type_fitness);
        particle(const particle& other);
        particle& operator=(const particle& other);
        bool operator < (const particle& other);
        void update(std::vector<double> new_vel);
        ~particle();
};

#endif // !
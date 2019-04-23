#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "cromossome.hpp"

class Population {
private:
    vector<Cromossome> pool;
    int id_best;
public:
    Population();

    void addCromossome(Cromossome c);

    Cromossome getCromossome(int id);

    int getIdBest();

    void reset();
};

#endif
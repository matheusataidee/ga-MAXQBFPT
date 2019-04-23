#include "population.hpp"

Population::Population() {
    id_best = -1;
}

void Population::addCromossome(Cromossome c) {
    pool.push_back(c);
    if (id_best == -1 || c.getScore() > pool[id_best].getScore()) {
        id_best = pool.size() - 1;
    }
}

Cromossome Population::getCromossome(int id) {
    return pool[id];
}

int Population::getIdBest() {
    return id_best;
}

void Population::reset() {
    id_best = -1;
    pool.clear();
}
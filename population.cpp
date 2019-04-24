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

void Population::removeWorst() {
    double mini = pool[0].getScore();
    int id = 0;
    for (int i = 1; i < pool.size(); i++) {
        if (pool[i].getScore() < mini) {
            mini = pool[i].getScore();
            id = i;
        }
    }
    swap(pool[id], pool[pool.size() - 1]);
    pool.pop_back();
    double maxi = pool[0].getScore();
    id_best = 0;
    for (int i = 1; i < pool.size(); i++) {
        if (pool[i].getScore() > maxi) {
            maxi = pool[i].getScore();
            id_best = i;
        }
    }
}

void Population::reset() {
    id_best = -1;
    pool.clear();
}
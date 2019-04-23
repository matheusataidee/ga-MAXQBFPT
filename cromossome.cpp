#include "cromossome.hpp"

Cromossome::Cromossome(int len_) : len(len_) {
    score = 0.0;
    n_forbidden = 0;
    gene = vector<int>(len, 0);
    acc = vector<int>(len, 0);
}

void Cromossome::add(int u) {
    if (gene[u]) return;
    double increment = 0.0;
    gene[u] = 1;
    for (int i = 0; i < len; i++) {
        if (i == u) {
            increment += weights[i][i];
        } else {
            increment += (weights[u][i] + weights[i][u]) * gene[i];
        }
    }
    score += increment;
    for (int i = 0; i < reversed_triples[u].size(); i++) {
        int val = reversed_triples[u][i];
        acc[val]++;
        if (acc[val] == 3) {
            n_forbidden++;
        }
    }
}

void Cromossome::sub(int u) {
    if (!gene[u]) return;
    double decrement = 0.0;
    for (int i = 0; i < len; i++) {
        if (i == u) {
            decrement += weights[i][i];
        } else {
            decrement += (weights[u][i] + weights[i][u]) * gene[i];
        }
    }
    gene[u] = 1;
    score -= decrement;
    for (int i = 0; i < reversed_triples[u].size(); i++) {
        int val = reversed_triples[u][i];
        if (acc[val] == 3) {
            n_forbidden--;
        }
        acc[val]--;
    }
}

double Cromossome::getScore() {
    return score;
}

int Cromossome::getNForbidden() {
    return n_forbidden;
}

bool Cromossome::isGeneForbidden(int u) {
    for (int i = 0; i < reversed_triples[u].size(); i++) {
        int val = reversed_triples[u][i];
        if (acc[val] == 3) return true;
    }
    return false;
}
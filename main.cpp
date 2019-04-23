#include <bits/stdc++.h>
#include <time.h>

#include "cromossome.hpp"
#include "population.hpp"

using namespace std;

int n;
vector<string> args;

vector<vector<double> > weights;
vector<vector<int> > triples;
vector<vector<int> > reversed_triples;

Cromossome* best_solution;
Population* population;

int lFunction(int u, int pi_1, int pi_2) {
    return 1 + (pi_1 * u + pi_2) % n;
}

void mountTriples() {
    for (int i = 0; i < n; i++) {
        triples[i][0] = i + 1;

        int g = lFunction(i, 131, 1031);
        if (g != triples[i][0]) {
            triples[i][1] = g;
        } else {
            triples[i][1] = 1 + (g % n);
        }

        int h = lFunction(i, 193, 1093);
        int x = 1 + (h % n);
        if (h != triples[i][0] && h != triples[i][1]) {
            triples[i][2] = h;
        } else if (x != triples[i][0] && x != triples[i][1]) {
            triples[i][2] = x;
        } else {
            triples[i][2] = 1 + (h + 1) % n;
        }
        sort(triples[i].begin(), triples[i].end());
        for (int j = 0; j < 3; j++) {
            triples[i][j]--;
            reversed_triples[triples[i][j]].push_back(i);
        }
    }
}

/*double exp(double num, int pot) {
    if (pot == 0) return 1;
    if (pot % 2 == 1) {
        return exp(num, pot - 1) * num;
    } else {
        double half = exp(num, pot / 2);
        return half * half;
    }
}

int getPopulationSize() {
    int size = 1;
    while (exp(1 - (exp(1/(double)2, size - 1)), n) < (double)0.999999) {
        size++;
    }
    return size;
}*/

void setInitialPopulation(int population_size) {
    for (int i = 0; i < population_size; i++) {
        Cromossome c(n);
        for (int j = 0; j < n; j++) {
            int r = rand() % 2;
            if (r == 1) {
                c.add(j);
            }
        }
        population->addCromossome(c);
        if (c.getNForbidden() == 0 && c.getScore() > best_solution->getScore()) {
            free(best_solution);
            best_solution = new Cromossome(n);
            for (int j = 0; j < n; j++) {
                if (c.hasGene(j)) {
                    best_solution->add(j);
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    srand(0);
    for (int i = 0; i < argc; i++) {
        args.push_back(string(argv[i]));
    }
    if (argc < 2) {
        cout << "Usage: " << args[0] << " <instance>" << endl;
        return 1;
    } else {
        ifstream fin(argv[1]);
        fin >> n;
        weights = vector<vector<double> >(n, vector<double>(n, 0.0));
        triples = vector<vector<int> >(n, vector<int>(3, 0));
        reversed_triples = vector<vector<int> >(n);
        population = new Population();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                fin >> weights[i][j];
                if (j > i) {
                    weights[j][i] = 0.0;
                }
            }
        }
        fin.close();
        mountTriples();
        best_solution = new Cromossome(n);
        Cromossome* c = new Cromossome(n);
        c->add(0);
        cout << c->getScore() << endl;
        c->sub(0);
        cout << c->getScore() << endl;
        setInitialPopulation(100);
        cout << best_solution->getScore() << endl;
    }
    return 0;
}
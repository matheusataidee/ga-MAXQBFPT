#include <bits/stdc++.h>
#include <ctime>

#include "cromossome.hpp"
#include "population.hpp"

using namespace std;

int n;

vector<vector<double> > weights;
vector<vector<int> > triples;
vector<vector<int> > reversed_triples;

Cromossome* best_solution;
Population* population;
Population* parents;
Population* offspring;
Population* mutants;

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

void updateBestSolution(Cromossome c) {
    best_solution->reset();
    free(best_solution);
    best_solution = new Cromossome(n);
    for (int j = 0; j < n; j++) {
        if (c.hasGene(j)) {
            best_solution->add(j);
        }
    }
}

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
            updateBestSolution(c);
        }
    }
}

void selectParents(int population_size, int steady_step) {
    parents = new Population();
    int total = 0;
    while (total < steady_step) {
        int a = rand() % population_size;
        int b = rand() % population_size;

        Cromossome parent1 = population->getCromossome(a);
        Cromossome parent2 = population->getCromossome(b);
        if (parent1.getScore() > parent2.getScore()) {
            parents->addCromossome(parent1);
        } else {
            parents->addCromossome(parent2);
        }
        total++;
    }
}

void crossover(int population_size) {
    offspring = new Population();
    for (int i = 0; i < population_size; i+=2) {
        Cromossome parent1 = parents->getCromossome(i);
        Cromossome parent2 = parents->getCromossome(i+1);

        int crosspoint1 = rand() % n;
        int crosspoint2 = rand() % (n - crosspoint1);

        Cromossome child1(n);
        Cromossome child2(n);
        for (int j = 0; j < n; j++) {
            if (j >= crosspoint1 && j < crosspoint2) {
                if (parent1.hasGene(j)) child1.add(j);
                if (parent2.hasGene(j)) child2.add(j);
            } else {
                if (parent2.hasGene(j)) child1.add(j);
                if (parent1.hasGene(j)) child2.add(j);
            }
        }
        offspring->addCromossome(child1);
        offspring->addCromossome(child2);
    }
}

void crossoverForDiversity(int population_size) {
    offspring = new Population();
    for (int i = 0; i < population_size; i+=2) {
        Cromossome parent1 = parents->getCromossome(i);
        Cromossome parent2 = parents->getCromossome(i+1);

        int it = 0;
        bool is_same = true;
        int crosspoint1;
        int crosspoint2;
        while (it++ < 5 && is_same) {
            crosspoint1 = rand() % n;
            crosspoint2 = rand() % (n - crosspoint1);
            for (int j = crosspoint1; is_same && j < crosspoint2; j++) {
                if (parent1.hasGene(j) != parent2.hasGene(j)) 
                    is_same = false;
            }
        }

        Cromossome child1(n);
        Cromossome child2(n);
        for (int j = 0; j < n; j++) {
            if (j >= crosspoint1 && j < crosspoint2) {
                if (parent1.hasGene(j)) child1.add(j);
                if (parent2.hasGene(j)) child2.add(j);
            } else {
                if (parent2.hasGene(j)) child1.add(j);
                if (parent1.hasGene(j)) child2.add(j);
            }
        }
        offspring->addCromossome(child1);
        offspring->addCromossome(child2);
    }
}

void mutate(int population_size, double fac) {
    mutants = new Population();
    for (int i = 0; i < population_size; i++) {
        Cromossome c = offspring->getCromossome(i);
        Cromossome mutant(n);
        for (int j = 0; j < n; j++) {
            int r;
            if (c.isGeneForbidden(j)) {
                r = rand() % 3;
            } else {
                r = rand() % (int)((double)n / fac);
            }
            int x = c.hasGene(j) ? 1 : 0;
            if (r == 0) x = 1 - x;
            if (x) {
                mutant.add(j);
            }
        }
        mutants->addCromossome(mutant);
    }
}

void fixSteadyState(int population_size) {
    for (int i = 0; i < population_size; i++) {
        mutants->addCromossome(population->getCromossome(i));
    }
    mutants->removeWorst();
    mutants->removeWorst();
}

void reset() {
    vector<vector<double> > weights;
    vector<vector<int> > triples;
    vector<vector<int> > reversed_triples;
    for (int i = 0; i < weights.size(); i++) {
        weights[i].clear();
    }
    weights.clear();
    for (int i = 0; i < triples.size(); i++) {
        triples[i].clear();
    }
    triples.clear();
    for (int i = 0; i < reversed_triples.size(); i++) {
        reversed_triples[i].clear();
    }
    reversed_triples.clear();
}

int main(int argc, char** argv) {
    string instances[7] = {".\\instances\\qbf020", ".\\instances\\qbf040", ".\\instances\\qbf060", 
                            ".\\instances\\qbf080", ".\\instances\\qbf100", ".\\instances\\qbf200", ".\\instances\\qbf400", };
    string method = "Default";
    int pop_sizes[1] = {100};
    double mutation_rate[1] = {1.0};
    for (int k = 0; k < 1; k++) {
        for (int s = 0; s < 7; s++) {
            int pop_size = pop_sizes[k];
            srand(0);
            ifstream fin(instances[s].c_str());
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
            setInitialPopulation(pop_size);
            int generation = 0, best_gen = 0;
            cout << "Instance: " << instances[s] << "\tPopulation size: " << pop_size 
                    << "\tMutation rate: " << mutation_rate[k] << "\tMethod: " << method  << endl;

            std::clock_t start;
            double duration;

            start = std::clock();


            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;


            while (generation < 11234 && (( std::clock() - start ) / (double) CLOCKS_PER_SEC) < 1800) {
                //cout << "generation: " << generation << endl;
                if (method == "Steady-state") {
                    selectParents(pop_size, 2);
                    crossover(2);
                    mutate(2, mutation_rate[k]);
                    fixSteadyState(pop_size);
                } else if (method == "Diversity") {
                    selectParents(pop_size, pop_size);
                    crossoverForDiversity(pop_size);
                    mutate(pop_size, mutation_rate[k]);
                } else {
                    selectParents(pop_size, pop_size);
                    crossover(pop_size);
                    mutate(pop_size, mutation_rate[k]);
                }

                population->reset();
                free(population);
                population = new Population(); 
                for (int i = 0; i < pop_size; i++) {
                    Cromossome c = mutants->getCromossome(i);
                    if (c.getNForbidden() == 0 && c.getScore() > best_solution->getScore()) {
                        updateBestSolution(c);
                        best_gen = generation;
                    }
                    population->addCromossome(c);
                }
                parents->reset();
                offspring->reset();
                mutants->reset();
                free(parents);
                free(offspring);
                free(mutants);
                generation++;
            }
            cout << best_solution->getScore() << endl;
            for (int i = 0; i < n; i++) {
                if (best_solution->hasGene(i)) {
                    cout << i << " ";
                }
            }
            cout << endl;
            cout << "Best gen: " << best_gen << "\tTotal Number of generations: " << generation << endl << endl;
            best_solution->reset();
            free(best_solution);
            population->reset();
            free(population);
            reset();
        }
    }
    return 0;
}
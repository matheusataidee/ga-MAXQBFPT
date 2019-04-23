#ifndef _CROMOSSOME_H_
#define _CROMOSSOME_H_

#include <vector>
#include <functional>

using namespace std;

extern vector<vector<double> > weights;
extern vector<vector<int> > triples;
extern vector<vector<int> > reversed_triples;

class Cromossome {
    private:
        double score;
        int n_forbidden;
        vector<int> gene;
        vector<int> acc;
        int len;
    public:
        Cromossome(int len_);

        void add(int u);

        void sub(int u);

        double getScore();

        int getNForbidden();

        bool isGeneForbidden(int u);

        bool hasGene(int u);
};

#endif /* _CROMOSSOME_H_ */
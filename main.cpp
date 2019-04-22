#include <bits/stdc++.h>

using namespace std;

int n;
vector<string> args;
vector<vector<double> > weights;
vector<vector<int> > triples;
vector<vector<int> > reversed_triples;

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
        
        cout << triples[i][0] << " " << triples[i][1] << " " << triples[i][2] << endl;
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < reversed_triples[i].size(); j++) {
            cout << reversed_triples[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
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
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                fin >> weights[i][j];
            }
        }
        mountTriples();
    }
    return 0;
}
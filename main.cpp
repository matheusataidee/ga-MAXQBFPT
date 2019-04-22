#include <bits/stdc++.h>

using namespace std;

int n;
vector<string> args;
vector<vector<double> > weights;

int main(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        args.push_back(string(argv[i]));
    }
    if (argc < 2) {
        cout << "Usage: " << args[0] << " <instance>" << endl;
    } else {
        ifstream fin(argv[1]);
        fin >> n;
        cout << n << endl;
        weights = vector<vector<double> >(n, vector<double>(n, 0.0));
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                fin >> weights[i][j];
                cout << weights[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
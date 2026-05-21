#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

void Bord_method(int n, int k, const vector<string>& names, const vector<vector<int>>& votes) {
    vector<int> scores(n, 0);

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            int candidateIdx = votes[i][j];
            scores[candidateIdx] += (n - 1 - j);
        }
    }

    cout << "--- Bord method ---" << endl;
    int maxScore = -1;
    for (int i = 0; i < n; ++i) {
        cout << names[i] << ": " << scores[i] << " Points" << endl;
        if (scores[i] > maxScore) maxScore = scores[i];
    }

    cout << "Bord's winner: ";
    for (int i = 0; i < n; ++i) {
        if (scores[i] == maxScore) cout << names[i] << " ";
    }
    cout << endl << endl;
}

void Kondorce_method(int n, int k, const vector<string>& names, const vector<vector<int>>& votes) {
    vector<vector<int>> wins(n, vector<int>(n, 0));

    for (int v = 0; v < k; ++v) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int sup = votes[v][i];
                int inf = votes[v][j];
                wins[sup][inf]++;
            }
        }
    }

    cout << "--- Kondorce method ---" << endl;
    int winnerIdx = -1;

    for (int i = 0; i < n; ++i) {
        bool isKondorceWinner = true;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (wins[i][j] <= wins[j][i]) {
                isKondorceWinner = false;
                break;
            }
        }
        if (isKondorceWinner) {
            winnerIdx = i;
            break;
        }
    }

    if (winnerIdx != -1) {
        cout << "Kondorce's winner: " << names[winnerIdx] << endl;
    } else {
        cout << "There's no Kondorce's winner..." << endl;
    }
}

int main() {
    int n, k;
    cout << "Type in amount of candidates... : ";
    cin >> n;
    vector<string> names(n);
    map<string, int> nameToIndex;

    cout << "Write candidates' names:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> names[i];
        nameToIndex[names[i]] = i;
    }

    cout << "Type in amount of voters: ";
    cin >> k;

    vector<vector<int>> votes(k, vector<int>(n));

    cout << "Type in voter priority (name-chain):" << endl;
    for (int i = 0; i < k; ++i) {
        cout << "Voter " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            string name;
            cin >> name;
            votes[i][j] = nameToIndex[name];
        }
    }

    cout << endl;
    Bord_method(n, k, names, votes);
    Kondorce_method(n, k, names, votes);

    return 0;
}
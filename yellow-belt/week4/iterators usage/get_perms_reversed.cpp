#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> GetRange(int n) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = i + 1;
    }
    return res;
}

template<typename T>
void PrintVector(const vector<T>& v) {
    for (const auto& x: v) {
        cout << x << " ";
    }
}

void PrintAllPerms(int n) {
    auto range = GetRange(n);
    vector<vector<int>> perms;

    do {
        perms.push_back(range);
    } while (next_permutation(range.begin(), range.end()));

    reverse(perms.begin(), perms.end());

    for (const auto& perm: perms) {
        PrintVector(perm);
        cout << endl;
    }
}
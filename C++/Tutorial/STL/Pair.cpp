#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    pair<int, int> a = {1, 2};
    int c = a.first;
    pair<int, pair<int, int>> f = {3, {4, 5}};
    vector<pair<int, int>> vp;
    vp.push_back({1, 3});
    vp.emplace_back(4, 5);
    cout << "Pair Vector: " << vp[0].first << " " << vp[1].second << endl;
}
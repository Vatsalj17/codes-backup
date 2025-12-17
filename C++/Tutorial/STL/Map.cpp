#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    map<int, int> mp;
    mp[3] = 78;
    mp.emplace(5, 23);
    mp.insert({2, 89});
    for (auto it : mp)
    {
        cout << it.first << " " << it.second << endl;
    }
    cout << "Map of pairs: " << endl;
    map<pair<int, int>, int> mpp;
    mpp[{2, 5}] = 3;
    mpp.insert({{78, 4}, 9});
    mpp.emplace(std::make_pair(1, 34), 29);
    for (auto it : mpp)
    {
        cout << it.first.first << " " << it.first.second << "   " << it.second << endl;
    }
}


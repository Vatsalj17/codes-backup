#include <bits/stdc++.h>
using namespace std;

void print_set(set<int> s)
{
    for (auto it = s.begin(); it != s.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

int main(void)
{
    set<int> st;
    st.insert(45);
    st.emplace(67);
    st.insert(12); // 12, 45, 67
    print_set(st);
    auto f = st.find(12); // Finds the iterator of 12
    st.insert(72);
    st.insert(1); // 1, 12, 45, 67, 72
    print_set(st);
    st.erase(st.find(12), st.find(67)); // 1, 67, 72
    print_set(st);
    cout << st.count(88); // 0
}

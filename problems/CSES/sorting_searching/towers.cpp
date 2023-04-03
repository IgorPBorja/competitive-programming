#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

template <typename ForwardIterator>
void read(ForwardIterator itr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> *itr;
        ++itr;
    }
}
template <typename ForwardIterator>
void print(ForwardIterator itr, int n, string sep=" ")
{
    for (int i = 0; i < n; i++)
    {
        cout << *itr << sep;
        ++itr;
    }
}
template <typename ForwardIterator, typename T>
void setval(ForwardIterator itr, int n, T v)
{
    for (int i = 0; i < n; i++)
    {
        *itr = v;
        ++itr;
    }
}

int main(){
    fastio;
    // greedy: always choose min(x | x > new value)
    // to be on top of another cube, new cube must be SMALLER (<, STRICT inequality)
    // so we need set::upper_bound

    // there can be repetitions (e.g 5 5 3 4) so we must use multiset
    multiset<int> tops;
    int n;
    cin >> n;
    int a[n];
    read(a, n);

    int towers = 0;
    for (int i = 0; i < n; i++){
        multiset<int>::iterator lb = tops.upper_bound(a[i]); // O(log n)
        if (lb != tops.end()){
            tops.erase(lb);
            tops.insert(a[i]); // this is the new top of that tower
        } else {
            tops.insert(a[i]); // new tower
            ++towers;
        }
    }
    cout << towers;
    // O(n log n) total
}

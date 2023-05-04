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
#define endl '\n'

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

template <typename ForwardIterator>
void read_pairs(ForwardIterator itr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> itr->first >> itr->second;
        ++itr;
    }
}

int n;
long long x;
vi moves_down;

int main(){
    fastio;
    cin >> n >> x;
    char c;
    for (int i = 0; i < n; i++){
        cin >> c;
        if (c == 'U'){
            if (moves_down.size() > 0)
                moves_down.pop_back();
            else 
                x = x / (2ll);
        } else {
            moves_down.emplace_back(c);
        }
    }
    for (char c : moves_down){
        if (c == 'L'){
            x = 2ll * x;
        } else {
            x = 2ll * x + 1ll;
        }
    }
    cout << x;
}
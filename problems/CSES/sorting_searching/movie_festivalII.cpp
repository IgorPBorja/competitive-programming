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

/**
strategy: parallel greedy (k simultaneous "threads")
* start ending time SET E
* Sort movies by ending time first, then start time if tie
* For each movie:
*     Check if there is some element in E less than its start time
*     If true, remove max(x in E | x <= start time) (i.e the closest)
*     and insert the end time --> uses set's lower bound method
*     Else, if that's false but the set has less than k elements, add the end time to the set
*
* Note that max(x in E | x <= start) = min(-x | x in E and -x >= -start)
* = lower bound of start in the set "-E" = {-x | x in E}
* Complexity: O(nlogn + nlogk)
 */

int main(){
    fastio;
    int n, k;
    cin >> n >> k;
    pii movies[n];
    multiset<int> ends;
    read_pairs(movies, n);
    sort(movies, movies + n, [](pii p1, pii p2){
        return (p1.second < p2.second) || (p1.second == p2.second && p1.first < p2.first);
    });

    // binary search for
    int cnt = 0;
    for (int i = 0; i < n; i++){
        if (
            (int)ends.size() == 0 ||
            (ends.lower_bound(-movies[i].first) == ends.end() && (int)ends.size() < k)
            ){
            ++cnt;
            ends.insert(-movies[i].second);
        } else if (ends.lower_bound(-movies[i].first) != ends.end()){
            ++cnt;
            ends.erase(ends.lower_bound(-movies[i].first));
            ends.insert(-movies[i].second);
        }
    }
    cout << cnt;


}

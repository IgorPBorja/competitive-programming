#include <bits/stdc++.h>
using namespace std;
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define i64 int64_t
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;


template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}


int main()
{
    // save pos[i] = position of value i
    // each time pos[i + 1] < pos[i] means reset

    i64 n;
    cin >> n;
    i64 a[n], pos[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        --a[i];
        pos[a[i]] = i;
    }
    i64 rounds = 1;
    for (i64 i = 1; i < n; i++){
        if (pos[i] < pos[i - 1]){
            ++rounds;  // reset
        }
    }
    cout << rounds << endl;
}

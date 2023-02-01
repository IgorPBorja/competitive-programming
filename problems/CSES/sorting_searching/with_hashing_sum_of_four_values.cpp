#include <bits/stdc++.h>
using namespace std;

unordered_map<long long, vector<pair<int, int>>> M;

int main(){
  int n;
  long long x;
  cin >> n >> x;
  long long a[n];
  for (int i = 0; i < n; i++){
    cin >> a[i];
  }

  for (int i = 0; i < n; i++){
    for (int j = i + 1; j < n; j++){
      M[a[i]+a[j]].emplace_back(make_pair(i, j));
    }
  }

  for (int i = 0; i < n; i++){
    for (int j = i + 1; j < n; j++){
      pair<int, int> p = make_pair(i, j);
      long long rem = x - a[i] - a[j];
      if (M[rem].size() > 0){
        for (pair<int, int> q: M[rem]){
          // within the pairs, the coordinates are already different
          if (p.first != q.first && p.first != q.second && 
              p.second != q.first && p.second != q.second){
            // the +1 compensates the 1-indexing
            cout << p.first + 1 << ' ' << p.second + 1 << ' ' << q.first + 1 << ' ' << q.second + 1;
            return 0;
          }
        }
      }
    }
  }
  cout << "IMPOSSIBLE";
}
#include <bits/stdc++.h>
using namespace std;

int main(){
  int n, m, k;
  cin >> n >> m >> k;
  int a[n];
  for (int i = 0; i < n; i++){
    cin >> a[i];
  }
  sort(a, a + n); // important

  multiset<int> b;
  int x;
  for (int i = 0; i < m; i++){
    cin >> x;
    b.insert(x);
  }

  int cnt = 0;
  for (int i = 0; i < n; i++){
    multiset<int>::iterator it = b.lower_bound(a[i] - k);
    if (it != b.end() && *it <= a[i] + k){
      // remove it
      ++cnt;
      b.erase(it);
    }
  }
  cout << cnt;
}
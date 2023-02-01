#include <bits/stdc++.h>
using namespace std;

int bsearch(long long a[], int n, long long x,
          int l = 0){
  int lo = l, hi = n - 1;
  while (lo <= hi){
    int mid = lo + (hi - lo)/2;
    if (a[mid] == x){
      return mid;
    } else if (x < a[mid]){
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  return -1;
}

pair<int, int> twosum(long long sorted[], int l, int n, int x){
  // range l to n-1 (inclusive)
  for (int i = l; i < n; i++){
    int query_res = bsearch(sorted, n, x - sorted[i], i + 1);   
    if (query_res != -1){
      return make_pair(i, query_res); // query_res > i if not -1
    }
  }
  return make_pair(-1, -1);
}

int main(){
  int n; long long x;
  cin >> n >> x;
  long long a[n], sorted[n];
  for (int i = 0; i < n; i++){
    cin >> a[i];
    sorted[i] = a[i];
  }
  sort(sorted, sorted + n);

  int i, j, k, l; // we need the final state of i,j,k,l (right before the goto)
  for (i = 0; i < n; i++){ 
    for (j = i + 1; j < n; j++){
      pair<int, int> _ = twosum(sorted, j + 1, n, x - sorted[i] - sorted[j]);
      k = _.first, l = _.second;
      if (k != -1 && l != -1){
        goto reindex;
      }
    }
  }
  //fails
  cout << "IMPOSSIBLE";
  return 0;
  
  reindex:
    int new_i = -1, new_j = -1, new_k = -1, new_l = -1;
    for (int index = 0; index < n; index++){
      if (a[index] == sorted[i]){
        new_i = index;
      }
    }
    for (int index = 0; index < n; index++){
      if (a[index] == sorted[j] && index != new_i){
        new_j = index;
      }
    }
    for (int index = 0; index < n; index++){
      if (a[index] == sorted[k] && index != new_i && index != new_j){
        new_k = index;
      }
    }
    for (int index = 0; index < n; index++){
      if (a[index] == sorted[l] && index != new_i && index != new_j && index != new_k){
        new_l = index;
      }
    }

    cout << new_i + 1 << ' ' << new_j + 1 << ' ' << new_k + 1 << ' ' << new_l + 1;
    /* Analysis
    foursum(n) = O(sum(i)sum(j > i) twosum(n - j)) = O(sum(j)sum(i < j)twosum(n - j))
    Since twosum(k) = O(k log k) we have 
    foursum(n) = O(sum(j)j(n-j)log(n-j)) = O(n^3logn)
    */
}
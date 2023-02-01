#include <bits/stdc++.h>
using namespace std;

int bsearch(int a[], int n, int x){
  // n <= 2e5
  // x <= 1e9
  int lo = 0, hi = n - 1;
  while (lo <= hi){
    int mid = lo + (hi - lo)/2;
    if (a[mid] == x){
      return mid;
    } else if (a[mid] < x){
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return -1;
}

int lsearch(int a[], int n, int x){
  for (int i = 0; i < n; i++){
    if (a[i] == x) return i;
  }
  return -1;
}

int rsearch(int a[], int n, int x){
  for (int i = n - 1; i >= 0; i--){
    if (a[i] == x) return i;
  }
  return -1;
}

int main(){
  int n, x;
  cin >> n >> x;
  int a[n], sorted[n];
  for (int i = 0; i < n; i++){
    cin >> a[i];
    sorted[i] = a[i];
  }
  sort(sorted, sorted + n); // makes binary search possible

  for (int i = 0; i < n; i++){
    int j = bsearch(sorted, n, x - sorted[i]);
    if (j != -1 && j != i){
      // translate to positions in a[]
      int new_i = lsearch(a, n, sorted[i]), new_j = rsearch(a, n, sorted[j]);
      // the use of lsearch/rsearch is to avoid finding the same positions when sorted[i] == sorted[j]
      // (when this happens, new_i will be the first and new_j the last occurence of the value)
      // which are guaranteed to be different since they were taken from 2 different pos of the sorted permutation
      cout << min(new_i, new_j) + 1 << ' ' << max(new_i, new_j) + 1; // the +1 compensates for 1-indexing
      return 0;
    }
  }
  cout << "IMPOSSIBLE";
}
#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll dev(ll a[], ll n, ll x){
  ll s = 0;
  for (ll i = 0; i < n; i++){
    s += max(x - a[i], a[i] - x);
  }
  return s;
}

int main(){
  ll n;
  cin >> n;
  ll a[n];
  for (ll i = 0; i < n; i++){
    cin >> a[i];
  }
  sort(a, a + n);
  ll median = (a[n/2] + a[(n-1)/2])/2;
  cout << min(dev(a, n, median), dev(a, n, median + 1)); // floor or ceil of median
}
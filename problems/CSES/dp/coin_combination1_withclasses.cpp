#include <bits/stdc++.h>
using namespace std;
#define MOD (long long)(1e9 + 7)

template <typename N>
struct Modular{
    N mod;
    N num;
    Modular operator+(Modular other){
      return Modular{this->mod, (this->num + other.num) % this->mod};
    }
    Modular operator-(Modular other){
      return Modular{this->mod, (this->num - other.num) % this->mod};
    }
    Modular operator*(Modular other){
      return Modular{this->mod, (this->num * other.num) % this->mod};
    }
    Modular& operator+=(Modular& other){
      this->num = (this->num + other.num) % this->mod;
      return *this;
    }
};

int main(){
  /*
  Bottom up dp:
  dp[k] = sum(1 <= i <= n : c[i] <= k)dp[k - c[j]]
  dp[0] = 1;
  */
  int n, x;
  cin >> n >> x;
  int c[n];
  for (int i = 0; i < n; i++){
    cin >> c[i];
  }
  sort(c, c + n);

  Modular<long long> dp[x + 1];
  for (int i = 0; i < x + 1; i++){
    dp[i] = {Modular<long long>{.mod = MOD, .num = 0}};
  }
  dp[0].num = 1;

  for (int i = 0; i < x + 1; i++){
    for (int j = 0; j < n && c[j] <= i; j++){
      dp[i] += dp[i - c[j]];
    }
  }
  cout << dp[x].num;
}
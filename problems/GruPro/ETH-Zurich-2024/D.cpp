// #define TESTCASES
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'

void solve(){
    i64 _n, _m, k;
    cin >> _n >> _m >> k;
    i64 f[_m];
    long double n = (long double)_n, m = (long double)_m;
    long double fbar = 0.0L, fl = 0.0L, fr = 0.0L;

    for (i64 i = 0; i < _m; i++){
        cin >> f[i];
    }
    for (i64 i = 0; i < _m; i++){
        fbar += (long double)f[i];
    }
    fbar /= m;
    i64 _lo = 0, _hi = 0;
    for (i64 i = 0; i < _m; i++){
        if ((long double)f[i] < fbar){
            ++_lo;
            fl += (long double)f[i];
        } else if ((long double)f[i] >= fbar){
            ++_hi;
            fr += (long double)f[i];
        }
    }
    fl /= (long double)_lo;
    fr /= (long double)_hi;
    long double lo = (long double)_lo, hi = (long double)_hi;

    i64 v[_n];
    // Ql: expected amount of below-average dice
    // Qr: expected amount of above-average dice
    // El: expected sum of below-average dice
    // Er: expected sum of above-average dice
    // E: expected global sum
    long double E[k + 1], Ql[k + 1], Qr[k + 1], El[k + 1], Er[k + 1];
    E[0] = 0.0L; Ql[0] = 0.0L; Qr[0] = 0.0L; El[0] = 0.0L; Er[0] = 0.0L;
    for (i64 i = 0; i < _n; i++){
        cin >> v[i];
        E[0] += (long double)(v[i]);
        if ((long double)v[i] < fbar){
            Ql[0] += 1.0L;
            El[0] += (long double)v[i];
        } else {
            Qr[0] += 1.0L;
            Er[0] += (long double)v[i];
        }
    }

    for (i64 i = 1; i <= k; i++){
        if (i % 2 == 1){
            // Alice's turn / maximization
            El[i] = Ql[i - 1] * (lo / m) * fl;
            Er[i] = Er[i - 1] + Ql[i - 1] * (hi / m) * fr;
            Ql[i] = Ql[i - 1] * (lo / m);
            Qr[i] = Qr[i - 1] + Ql[i - 1] * (hi / m);
        } else {
            // Bob's turn / minimization
            El[i] = El[i - 1] + Qr[i - 1] * (lo / m) * fl;
            Er[i] = Qr[i - 1] * (hi / m) * fr;
            Ql[i] = Ql[i - 1] + Qr[i - 1] * (lo / m);
            Qr[i] = Qr[i - 1] * (hi / m);
        }
        E[i] = El[i] + Er[i];
        // cerr << fixed << setprecision(12) << "E[" << i << "]=" << E[i] << endl;
        // cerr << fixed << setprecision(12) << "Ql[" << i << "]=" << Ql[i] << endl;
        // cerr << fixed << setprecision(12) << "Qr[" << i << "]=" << Qr[i] << endl;
    }
    cout << fixed << setprecision(12) << E[k] << endl;
}

signed main(){
    i64 t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    for (i64 _ = 0; _ < t; _++){
        solve();
    }
}
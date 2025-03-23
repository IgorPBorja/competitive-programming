

> [!z-function-def] Definição (função Z)
> Dada uma string $s = s_0\dotsc s_{n - 1}$, a função $z$ para essa dada string é definida por, para todo $0 \leq i < n$:
> $$z[i] = \max\{0 \leq j \leq n - i : z[0..j-1] = z[i..i+j-1]\}$$
> Em particular, para toda string de tamanho $n$, $z[0] = n$.

## Algoritmo:

```c++
vector<int> zfunc(string& s){
	int l = 1, r = 0;
	const int n = s.size();
	vector<int> z(n);
	z[0] = n;
	for (int i = 1; i < n; i++){
		// s[i-l]...s[r-l] = s[i]...s[r] (I)
		// but if z[i-l] = k then also
		// s[0]...s[k-1] = s[i-l]...s[i-l+k-1]
		// so if k <= r-i then because of the maximality of z[i-l], s[0..k-1] = s[i...i+k-1] and s[k] != (s[i-l+k] = s[i+k])
        // where the equality follows from (I) since i+k <= r
		// which means we can't expand prefix/prefix pair and z[i] = z[i-l]
		// Otherwise, if k > r-i, this means s[0...r-i] == s[i-l...r-l] == s[i...r]
        // so we reset the interval from [l,r] to [i,r] and try to expand it
		if (i > r){
			// outside interval, reset to empty closed interval
			l = i;
			r = i - 1;
		}
		if (z[i - l] <= r - i){
			z[i] = z[i - l];
		} else {
            l = i;
			while (r + 1 < n && s[r + 1] == s[r + 1 - i]){
				++r;
			}
			z[i] = r - i + 1;
		}
	}
	return z;
}
```
# Problems (TODO)

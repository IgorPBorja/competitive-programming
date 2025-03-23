
# Small to large - geral

*  Utiliza a mesma ideia de merge do DSU porém **mantemos as listas contendo os sets**
*  Complexidade: $O(\log N)$ amortizada -  ou seja, $O(N \log N)$ para uma sequência de merges que resulta em um único conjunto.

```c++
struct DSU{
	vector<int> p;
	vector<vector<int>> elements;

	DSU(int n){
		p.resize(n);
		iota(p.begin(), p.end());
		elements.resize(n);
		for (int i = 0; i < n; i++){
			elements[i].emplace_back(i);
		}
	}
	int find(int x){
		if (p[p[x]] != p[x]) p[x] = find(p[x]);
		return p[x];
	}
	
	void merge(int x, int y){
		x = find(x), y = find(y);
		if (x == y) return;
		if (elements[x].size() < elements[y].size()) swap(x, y);
	
		for (int z: elements[y]){
			elements[x].emplace_back(z);
		}
		p[y] = x;
	}
}

```


## Exemplo: 

Link: [CodeforcesEDU - DSU - Step1C. Experience](https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/C)

* Montamos uma DSU mantendo um `lazy` tal que `lazy[find(x)]` é quanto deve ser adicionado a todos os elementos do set que contém `x` .
* No merge, **atualizamos os valores do set menor de acordo com seu lazy** 
	* Entretanto, devemos **subtrair o valor do lazy do set maior, pois esse incremento foi feito antes do merge**  e não deve ser aplicado a essa nova parte mergeada.

```c++
void merge(int x, int y){
	x = find(x), y = find(y);
	if (x == y) return;
	if (elements[x].size() < elements[y].size()) swap(x, y);

	for (int z: elements[y]){
		val[z] += lazy[y];  // commits the pending update
		val[z] -= lazy[x];  // avoids adding lazy[x] which was an update that happened before this z was added to this set
		elements[x].emplace_back(z);
	}
	parent[y] = x;
}

int get(int x){
	return val[find(x)] + lazy[find(x)];
}
```


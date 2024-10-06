* Forma de subir rapidamente em uma árvore ou em uma floresta **direcionada/enraizada**

Mais formalmente:


> [!NOTE] Teorema 1
> Dada uma função $f: \{1, \dotsc, n\}: \to \{1, \dotsc n\}$, podemos pre-computar
> $f^{2^j}(i)$ para cada $i=1\dotsc n$ e para todo $j$ tal que $2^j \leq M$ em $O(n \log M)$.


> [!NOTE] Algoritmo 1: computamos a matriz de _lifting_ por nó na ordem induzida pela DFS tree - ou seja, em **pré-ordem**.

```cpp
const int N = 2e5, LOGN = 20;
int lift[N][LOGN + 1];

void dfs(int u, const vector<int> &p){
	lift[u][0] = p[u];
	for (int i = 1; i <= LOGN; i++){
		lift[u][i] = lift[lift[u][i - 1]][i - 1]
	}
	for (int v: adj[u]){
		dfs(v);
	}
}

void binary_lifting(const vector<vector<int>> &forest){
	const int n = forest.size();
	vector<int> parent(n, -1);
	vector<int> indegree(n, 0); // entry degree of tree vertex
	for (int u = 0; u < n; u++){
		for (int v: forest[u]){
			parent[v] = u;
			++indegree[v];
		}
	}
	for (int u = 0; u < n; u++){
		if (indegree[u] == 0){
			dfs(u, parent);
		}
	}
}
```

> [!alg-2] Algoritmo 2: computamos a matriz de lifting para cada expoente $j$ fixado, e para cada nó.

```cpp
const int N = 2e5, LOGN = 20;
int lift[LOGN + 1][N];

void binary_lifting(const vector<vector<int>> &forest){
	const int n = forest.size();
	vector<int> parent(n, -1);
	for (int u = 0; u < n; u++){
		for (int v: forest[u]){
			parent[v] = u;
		}
	}
	for (int u = 0; u < n; u++){
		lift[0][u] = parent[u];
	}
	for (int k = 1; i <= LOGN; i++){
		for (int u = 0; u < n; u++){
			lift[k][u] = lift[k - 1][lift[k - 1][u]];
		}
	}
}
```


> [!NOTE] Teorema 2
> Com a estrutura pré-computada anterior, podemos calcular $f^{m}(x)$ para todo $0 \leq m \leq M$ em $O(\log M)$.

Prova: seja $m = \sum_{k = 0\dotsc B-1} 2^{i_k}$ com $B = O(\log M)$ a quantidade de bits ativos de $m$, e $i_0 < i_1 < \dotsc < i_k \leq \log M$. Então

$$f^m(x) = f^{2^{i_0}} \circ f^{2^{i_1}} \circ \dotsc \circ f^{2^{i_k}} (x)$$
e cada $f^{2^x}$ já foi pré-computada para todo $x \leq \log M$ e em cima de todo valor $1 \leq y \leq n$, e portanto cada uso ocorre em $O(1)$. Como são $B = O(\log M)$ composições, então o algoritmo executa em $O(\log M)$. Mais precisamente, sempre são feitas no máximo $\lfloor \log M \rfloor + 1$ operações, uma vez que essa é a quantidade de bits necessária para expressar $M$. 
* Algoritmo:

```cpp
int jump(int u, int k){
	for (int i = 0; i <= LOGN; i++){
		if ((k >> i) & 1){
			u = lift[i][u];
		}
	}
	return u;
}
```


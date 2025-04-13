
> [!scc-def] Uma componente fortemente conexa em um grafo direcionado $G$ é um conjunto maximal de vértices $C$ tal que, para todos $u$ e $v$ em $C$, existe um $(u,v)$ caminho e também existe um $(v, u)$ caminho.

## Algoritmo trivial

* 1. Para cada vértice $u$, realizamos uma DFS começando de $v$
* 2. Obtemos uma matriz $reachable[u][v]$ que diz se conseguimos alcançar $v$ a partir de $u$
* 3. Para cada vértice $u$, se ele ainda não foi utilizado iteramos sobre todos os vértices $v$ adicionando na componente fortemente conexa de $u$ tais que $reachable[u][v] \land reachable[v][u]$.

```c++
void dfs(int u, vector<vector<int>> &G, vector<int> &vis){
	vis[u] = true;
	for (int v: G[u]){
		if (!vis[v]) dfs(v, G, vis);
	}
}

vector<vector<int>> scc(vector<vector<int>> &G){
	vector<vector<int>> reachable;
	// O(N^2)
	for (int u = 0; u < n; u++){
		vector<bool> vis(n, false);
		dfs(u, G, vis);
		reachable.emplace_back(vis);
	}

	// O(N * |SCC(G)|) = O(N^2)
	vector<bool> used(n, false);
	for (int u = 0; u < n; u++){
		if (used[u]) continue;
		vector<int> c;
		used[u] = true;
		for (int v = 0; v < n; v++){
			if (reachable[u][v] && reachable[v][u]){
				c.emplace_back(v);
				used[v] = true;
			}
		}
		components.emplace_back(c);
	}
	return components;
}
```

## Kosaraju

* 1. Para cada vértice não visitado, executamos uma DFS
	* A cada iteração marcamos $u$ como visitado, visitamos todos os seus vizinhos ainda não visitados e por fim colocamos $u$ em uma pilha
	* Essa pilha no final é a **post-order da DFS tree**
	* Invertemos essa pilha
* 2. Marcamos todos os vértices como não visitados
* 3. Para cada vértice na pilha, se ele não foi visitado fazemos uma DFS no grafo transposto $G^T$: **os vértices visitados serão um componente fortemente conexo**

Complexidade: $O(N + M)$: de fato, duas DFSs são feitas 

```c++
struct Kosaraju {
public:
	vector<vector<int>> scc(vector<vector<int>> &G){
		// forward DFS
		const int n = G.size();
		vector<bool> vis(n, false);
		for (int u = 0; u < n; u++){
			if (!vis[u]) {
				forwards_dfs(G, vis, u);
			}
		}
		reverse(stack.begin(), stack.end());
	
		// backwards DFS
		fill(vis.begin(), vis.end(), false);
		vector<vector<int>> H = transpose(G);
		vector<vector<int>> scc_components;
		for (int u: stack){
			if (!vis[u]){
				vector<int> component;
				backwards_dfs(H, vis, u, component);
				scc_components.emplace_back(component);
			}
		}
		return scc_components;
	}

	Kosaraju(){}
private:
	vector<int> stack;

	vector<vector<int>> transpose(const vector<vector<int>> G){
		const int n = G.size();
		vector<vector<int>> H(n);
		for (int i = 0; i < n; i++){
			for (int j: G[i]){
				H[j].emplace_back(i);
			}
		}
		return H;
	}

	void forwards_dfs(vector<vector<int>> &G, vector<bool> &vis, int u){
		vis[u] = true;
		for (int v: G[u]){
			if (!vis[v]) forwards_dfs(G, vis, v);
		}
		stack.emplace_back(u);
	}
	void backwards_dfs(vector<vector<int>> &G, vector<bool> &vis, int u, vector<int> &component){
		vis[u] = true;
		components.emplace_back(u);
		for (int v: G[u]){
			if (!vis[v]) backwards_dfs(G, vis, v, component);
		}
	}
}
```

## Tarjan

(TODO)

## Contração de vértices

* Estar em uma mesma fortemente conexa é uma relação de equivalência

> [!quotient-graph-is-dag] Teorema 1
> * Contraindo os vértices pela relação de SCC o grafo "quociente" $G/SCC$ é uma **grafo direcionado acíclico (DAG)**

^dbfbaa

* De fato, se o grafo quociente possuísse um ciclo $C_1, \dotsc, C_n$, em que cada $C_i$ é uma componente fortemente conexa,  então para todos vértices $u \in C_i$ e $v \in C_j$ existe um caminho $(u,v)$ e um caminho $(v, u)$,  e  portanto o subgrafo induzido por $C_1 \cup \dotsc \cup C_n$ é fortemente conexo. Isso contradiz a maximalidade de cada componente fortemente conexa!
	* Segue que o grafo quociente é acíclico.
# Fazendo LCA com binary lifting

## Requisitos (binary lifiting) (ver [[Binary lifting]])

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

int jump(int u, int k){
	for (int i = 0; i <= LOGN; i++){
		if ((k >> i) & 1){
			u = lift[i][u];
		}
	}
	return u;
}
```

## LCA:

```cpp
int LCA(int u, int v, const vector<int> &level, const vector<int> &parent){
	// invariant: level[u] <= level[v]
	if (level[v] < level[u]) swap(u, v);
	v = jump(v, level[v] - level[u]);

	if (u == v){
		return u;
	}

	// loop invariant: u and v are distinct (we have not reached a common ancestor yet)
	for (int i = LOGN; i >= 0; i--){
		if (lift[i][u] != lift[i][v]){
			// keeps loop invariant -> greedily take it!
			u = lift[i][u];
			v = lift[i][v];
		}
	}

	// at the end of the invariant we must be just one level below the LCA
	// otherwise we could have jumped more
	return parent[u];
}
```


> [!lca-blift-correct] Teorema: o algoritmo acima está correto

Prova: seja $L[1\dotsc N]$ o vetor de níveis (alturas na árvore) e $P[1\dotsc N]$ o vetor de pais dos vértices. Seja $h = L[LCA(u, v)]$ e considere a representação binária de $L[u] - h - 1$ 
$$L[u] - h - 1 = \sum_{B \geq i \geq 0}b_i \cdot 2^i$$ 
(com $B = \lceil \log N \rceil$).

A linha `v = jump(v, level[v] - level[u])` garante que, a partir de então, estamos tentando encontrar o LCA de dois vértices $u, v'$ de mesmo nível $L[u]$, e vamos assumir isso a partir de agora.

Seja $u_i, v_i$ os valores dos vértices depois da $i$-ésima iteração do loop $i=B, B-1, \dotsc 0$.

>  **Invariante de loop**: $u_i = P^{\sum\limits_{B \geq j \geq i}b_j 2^j}(u)$ e $v_i = P^{\sum\limits_{B \geq j \geq i}b_j 2^j}(v')$ 

Note que, para todo $i \leq L[u]$, temos que
$$L[P^i(u)] = L[u] - x$$
em que $P^i(u)$ é o $i$-ésimo ancestral de $u$.

Provamos por indução (reversa) com o caso base $i = B$.

De fato, se $b_B$ = 0, então $L[u] - h - 1 < 2^B$, ou seja,
$$h \geq L[u] - 2^B$$
e portanto $lift[B][u] = lift[B][v]$, pois já alcançamos ou passamos do LCA, e dessa forma não entramos no `if`. Do contrário, não alcançamos ainda o LCA e portanto entramos no `if` . Portanto $u_B = P^{b_B 2^B}(u)$ e $v_B = P^{b_B 2^B}(v')$.

Suponha então que a afirmação vale para um certo $i + 1 > 0$. Então, se $b_i = 0$, 
$$\begin{align*}
L[u] - h - 1 < \sum_{B \geq j > i}b_j 2^j + 2^i
\iff
h \geq L[u] - \sum_{B \geq j > i}b_j 2^j - 2^i = L[P^{2^i}(b_{i + 1})]
\end{align*}
$$
de onde segue que $lift[i][u] = lift[i][v]$, pois já alcançamos ou passamos do LCA. Por outro lado, se $b_i = 1$, então vale a desigualdade oposta:
$$\begin{align*}
L[u] - h - 1 \geq \sum_{B \geq j > i}b_j2^j + 2^i \iff h < L[u] - \sum_{B \geq j > i}b_j 2^j + 2^i
\end{align*}$$
mostrando que ainda não chegamos no LCA, e portanto $lift[i][u] \neq lift[i][v]$ e entramos no `if`. Concluímos que 
$$u_i = P^{b_i 2^i}(u_{i + 1}) = P^{\sum_{B \geq j \geq i}b_j 2^j}(u)$$
e a afirmação análoga para $v_i$.
$$\tag*{$\blacksquare$}$$
Portanto ao final do loop temos os valores $u_0 = P^{\sum_{B \geq j \geq 0}b_j 2^j}(u) = P^{L[u] - h - 1}(u)$  e $v_0 = P^{L[u] - h - 1}(v') = P^{L[v'] - h - 1}(v')$.

Concluímos então que $P(u_0) = P(v_0) = LCA(u, v)$.
$$\tag*{$\blacksquare$}$$
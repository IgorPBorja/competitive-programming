
## Link crucial

https://robert1003.github.io/2020/01/16/centroid-decomposition.html

## Definições
 

> [!centroid-def] Centróide
> Um vértice $u$ é um centróide de uma árvore de $n$ vértices se, ao remover $u$, todas as subárvores resultantes tem tamanho **menor ou igual a $\frac{n}{2}$**

## Algoritmo:

* Escolhe-se uma **raiz arbitrária (ex.: nó 1)** e calcula-se o tamanho da subárvore enraizada em $u$, $s[u]$, tendo essa raiz específica (usando DFS + DP em árvores). 
* Usa-se uma DFS simples:

```c++
centroid(u, G, size){
	for (v: G[u]){
		if (v is parent of u){
			continue;
		}
		if (size[v] > n / 2){
			// u não é centroide, pois ao remover u
			// a subárvore contendo v tem tamanho maior que n/2
			return centroid(v, G, size);
		}
	}
	// u é centroide
	return u;
}
```

Note a seguinte invariante:

> [!centroid-decomp-prop1] Invariante 1:
> Se a DFS é chamada no vértice $u$, então a subárvore acima de $u$ tem tamanho menor ou igual a $\frac{n}{2}$
> ^centroid-decomp-prop1

Prova: isso é trivialmente válido para a raiz, pois não há nada acima dela.

Suponha então que foi chamada a DFS em $u$, vinda de um vértice $p$, seu pai na subárvore enraizada em $1$. Então $p$ não é centroide, e mais especificamente temos que $size[u] > \frac{n}{2}$. Assim, a subárvore acima de $u$ tem tamanho $n - size[u] < \frac{n}{2}$




> [!centroid-decomp-correctness] Corretude
> O algoritmo acima sempre encontra um centróide.

Prova: é óbvio que o algoritmo termina, pois em particular a profundidade do próximo vértice no qual a DFS é chamada é igual à profundidade do vértice atual, mais 1.

Da [[ICPC/Trees/Centroid decomposition/Teoria#^centroid-decomp-prop1|invariante 1]] segue que a subárvore acima sempre tem tamanho menor que $\frac{n}{2}$, e quando a função retorna de fato então significa que todas as subárvores enraizadas no vértice $u$ também tem tamanho menor ou igual a $\frac{n}{2}$ (desconsiderando $u$). Dessa forma, o vértice $u$ é um centroide.
## Centroid decomposition


> [!NOTE] Centroid decomposition
> Uma centroid decomposition de $T$ é uma árvore enraizada $T'$ (chamada de _centroid tree_) tal que:
> * A raiz de $T'$ é um centroide de $T$
> * As subárvores conectadas à raiz são as centroid decompositions das subárvores obtidas removendo o centroide de $T$

### Algoritmo:

```
centroid_decomp(T) {
	find a centroid u of T
	partition T into the subtrees obtained deleting u
	call centroid_decomposition on those subtrees
	merge result
}
```

A complexidade disso é $O(n \cdot d)$, em que $d$ é a profundidade da árvore de centroides, uma vez que a cada nível são feitas várias DFSs (uma em cada partição) que ao final cobrem a árvore quase toda.

Podemos **simular o particionamento e marcando certos vértices como bloqueados (removidos)**

Na implementação abaixo, $blocked[v]$ significa que qualquer aresta envolvendo $v$ está bloqueada. Isso permite atuar nas subárvores de um vértice $v$ sem visitar a parte acima de $v$.

```c++
namespace CentroidDecomposition {
    int subtree_size(int u, const vector<vector<int>>& adj, vector<int>& s, vector<int>& blocked, int p = -1){
        s[u] = 1;
        for (int v: adj[u]){
            if (v == p) continue;
            if (blocked[v]) continue;
            s[u] += subtree_size(v, adj, s, blocked, u);
        }
        return s[u];
    }

    // find centroid of subtree
    // total size is not n, since DFS is restricted 
    int find_centroid(int u, const vector<vector<int>>& adj, vector<int>& s, vector<int>& blocked, int total_size, int p = -1){
        for (int v: adj[u]){
            if (v == p) continue;
            if (blocked[v]) continue;
            if (2 * s[v] >= total_size){
                return find_centroid(v, adj, s, blocked, total_size, u); // there can be only one such vertex
            }
        }
        return u;
    }

    // total_size = size of subtree rooted at root (considering deletions)
    // @return centroid subtree root
    int _build_centroid_tree(
        const vector<vector<int>>& adj,
        vector<int>& blocked,
        vector<vector<int>>& centroid_adj,
        vector<int>& sz,
        int total_size,
        int root = 0
    ){
        subtree_size(root, adj, sz, blocked);
        int c = find_centroid(root, adj, sz, blocked, total_size);
        blocked[c] = true;
        for (int v: adj[c]){
            if (blocked[v]) continue;
            // build centroid subtree on partition and get its root
            int c2 = _build_centroid_tree(adj, blocked, centroid_adj, sz, sz[v], v);
            centroid_adj[c].emplace_back(c2);
        }
        return c;
    }

    // @return pair (centroid tree root, directed centroid tree)
    pair<int, vector<vector<int>>> centroid_tree(const vector<vector<int>>& adj){
        const int n = adj.size();
        vector<int> blocked(n, false), sz(n);
        vector<vector<int>> centroid_adj(n);
        int master_centroid = _build_centroid_tree(
            adj, blocked, centroid_adj, sz, n
        );
        return {master_centroid, centroid_adj};
    }
}
```

# Propriedades

![[Pasted image 20250606143039.png]]
^picture-centroid-tree

> [!NOTE] Teorema 1
> A profundidade de uma centroid tree é no máximo $\log_2 N + 1 = O(\log N)$

Prova: provamos por indução em $N$, sendo o caso $N = 1$ trivial.

Defina por $d(T)$ a profundidade da centroid tree da árvore $T$, e $d^*(N)$ a maior profundidade de centroid trees obtidas a partir de árvores com **até** $n$ vértices. Queremos mostrar que $d^*(N) \leq \log_2 N + 1$ por indução (isso implica no teorema enunciado).

Seja então $T$ uma árvore com $N$ nós e $g$ um centroide. Então tomando $g$ como raiz obtemos $k$ subárvores $T_1, \dotsc, T_k$ com $|T_i| \leq \frac{N}{2}$. Dessa forma, como por definição a centroid tree de $T$ é a árvore com raiz $g$ e subárvores sendo as centroid trees de $T_1, \dotsc, T_k$, então: 

$$d(T) = 1 + \max_{1 \leq i \leq k}d(T_i) \leq 1 + \max_{1 \leq i \leq k}d^*(|T_i|) \leq 1 + d^*\left(\frac{N}{2}\right) \leq 1 + \log_2\left(\frac{N}{2}\right) + 1 = 1 + \log_2(N)$$
(usando a hipótese indutiva em $\frac{N}{2}$).

Logo, como isso vale para toda árvore de $N$ vértices, e usando a hipótese indutiva $d^*(N - 1) \leq \log_2(N - 1) + 1 < \log_2(N) + 1$ , então:

$$d^*(N) = \max(d^*(N-1), \max \{d(T): T \text { é uma árvore com } |T| = N\}) \leq 1 + \log_2(N)$$

como queríamos demonstrar.


> [!NOTE] Observação útil!
> Dessa forma, a centroid decomposition divide a árvore em $O(\log N)$ níveis!



> [!NOTE] Teorema 2
> Dada uma árvore $T$ com centroid tree $G$, o caminho em $T$ entre quaisquer dois vértices $u$ e $v$ pode ser decomposto em dois caminhos de $u$ a $w$ e $w$ a $v$, ainda na árvore $T$, com 
> $$w = LCA_{G}(u, v)$$
> Em outras palavras, sempre passamos pelo LCA (na centroid tree) dos pontos inicial e final
 
Prova:

Seja $u$ um vértice na centroid tree. Defina como o **componente de $u$** (denotado por $C(u)$) a seguinte subárvore de $T$:
* A própria árvore completa, se $u$ é a raiz da centroid tree
* Do contrário, sendo $p$ pai de $u$, na centroid tree, remove-se $p$ do componente $C(p)$ e toma-se a subárvore restante que contém $u$.

Note que os vértices de $C(u)$ são exatamente os vértices da subárvore de $u$ na centroid tree $G$ (remeta a [[ICPC/Trees/Centroid decomposition/Teoria#^picture-centroid-tree|imagem da centroid tree]]).


Seja $\ell$ o LCA desses dois vértices na árvore de centroides. Isso significa que $u,v$ estão ambos no componente de $\ell$, porém pela minimalidade de $\ell$ não existe nenhum vértice filho de $\ell$ na centroide tree que seja ancestral comum, isto é, tal que $u$ e $v$ estejam no componente desse filho.

Dessa forma, ao olhar para o componente de $\ell$ (que contém o caminho $(u,v)$) e remover $\ell$, os vértices $u$ e $v$ ficam desconectados! Logo o caminho de $u$ para $v$ passa por $\ell$.


> [!NOTE] Corolário 2
> Se $u,v$ são dois vértices de $T$ que estão, na centroid tree, na subárvore de $\ell$, então o caminho de $u$ a $v$ em $T$ contém apenas vértices da subárvore de $\ell$ na centroid tree
> (só que em ordens possivelmente arbitrárias)
>

Prova:
**Segue do fato da construção da centroid tree via remoção de vértices**: sabemos que $u$ e $v$ estão no componente de $\ell$ pelo Teorema anterior, só que esse componente só contém vértices que, por construção, vão ser postos na subárvore de $\ell$ ao montar a centroid tree.
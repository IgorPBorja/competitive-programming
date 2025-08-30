#flow 
# Definindo um corte (_cut_)

Um corte (_cut_) em um grafo direcionado com pesos com _source_ $s$ e _sink_ $t$ é uma partição dos vértices em dois conjuntos disjuntos $S$ e $T$, de forma que $s \in S$ e $t \in T$.

A **capacidade** de um corte é a soma dos pesos as arestas $uv$ que atravessam da partição da esquerda, $S$ para a partição da direita, $T$ - isto é, com $u \in S$ e $v \in T$. O **min-cut é um corte com capacidade mínima**.

Min-cuts são importantes por conta da seguinte propriedade:

> **Teorema 0: As arestas do min-cut é o conjunto de arestas de menor peso que, quando removido, desconecta $s$ de $t$ no grafo**

Intuição/Prova: ora, todo conjunto de arestas **minimal** que desconecta $s$ de $t$ é o conjunto de arestas de um corte (**minimal no sentido de que não pode ser reduzido: se recolocar uma aresta reconecta a source à sink**).

De fato, após desconectar, coloque o componente fortemente conexo (SCC) de $s$ na partição $S$, o componente fortemente conexo de $t$ na partição $T$, e atribua os outros componentes fortemente conexos a $S$ ou $T$ de forma que as arestas removidas fluam apenas de $S$ para $T$. Isso é possível porque, se você designou de forma que alguma das arestas removidas vai de $T$ para $S$, então você pode voltar e recolocar essas arestas que ainda vão estar $s$ e $t$ desconexos. Isso contradiz a minimalidade do nosso conjunto de arestas desconectantes.

E vice-versa: um corte define um conjunto de arestas que desconecta _source_ e _sink_.

Então o peso mínimo de um conjunto de arestas que desconecta _source_ e _sink_, já que gulosamente sempre vamos querer um conjunto de arestas minimal, é o peso mínimo de um corte do grafo!

O teorema fundamental sobre min-cut é que ele é **igual ao max-flow**.

> **Teorema (min-cut max-flow) O min-cut é igual ao max-flow.
>
> Além disso, as arestas do min-cut são as arestas entre os vértices alcançáveis e não-alcançáveis (nessa ordem) a partir de $s$ no grafo residual final, depois da execução do algoritmo de max-flow**

# Provando o teorema do min-cut max-flow

Algumas definições breves:

> **Definição 1**: definimos por $E^+(A)$ as arestas que saem de um conjunto de vértices $A$ (_outgoing edges_): $E^+(A) = \{uv: u \in A, v \text{ qualquer }\}$ - inclusive que tem como destino vértices do próprio $A$. Analogamente definimos $E^{-}(A)$ (_incoming edges_) como as arestas que chegam em $A$
> 
> Denotamos para um único vértice $v$ o conjunto $E^{+}(\{v\})$ como $E^{+}(v)$ e $E^{-}(\{v\})$ como $E^{-}(v)$.
### Conservação de flow

Chame de **nó de conservação** qualquer $u \neq s,t$, ou seja, vértice para o qual vale a regra de conservação de fluxo.

> **Teorema 1** (Conservação de fluxo) Seja $S \subseteq V$ um conjunto de vértices com $s \in S$ e $t \not\in S$, e $f$ um $(s,t)$-fluxo . Então
>
> $$|f| = \sum_{e \in E^{+}(S)}f(e) - \sum_{e \in E^{-}(S)}f(e)$$
Em particular,
> $$|f| = \sum_{u \in S, v \not\in S}f(uv) - \sum_{v \not\in S, u \in S}f(vu)$$
Ou seja, para qualquer conjunto que contém a source e não contém a sink, o valor do fluxo é o _outgoing flow_ menos o _incoming flow_ desse conjunto.

Intuição: **como todos os nós em $S$ exceto $s$ são nós de conservação, que não interagem com o meio externo, podemos colapsar todo o conjunto para um ponto que, da perspectiva do meio externo, se comporta igual a $s$.**

Prova: o valor do fluxo é a quantidade de matéria "extra" que entra pela _source_, ou seja

$$|f| = \sum_{e \in E^{+}(s)}f(e) - \sum_{e \in E^{-}(s)}f(e)$$
Como todo nó em $S \setminus \{s\}$ é nó de conservação então o fluxo que sai dele é igual ao fluxo que entra, e portanto

$$\sum_{u \in S \setminus \{s\}}\left(\sum_{e \in E^{+}(u)}f(e) - \sum_{e \in E^{-}(u)}f(e)\right) = 0$$
Somando essa equação com a anterior, obtemos a primeira equação do teorema. Para eliminar as arestas internas, perceba que intuitivamente é óbvio que as arestas internas a $S$ precisam somar $0$ no fluxo extra - afinal, $S$ internamente conserva o fluxo, e o vazamento/entrada ocorre apenas com o meio externo (que precisa envolver a sink $t$, o único outro vértice que interage com o meio externo).

Formalmente,
$$
\begin{align*}
|f|
&= \sum_{e \in E^{+}(S)}f(e) - \sum_{e \in E^{-}(S)}f(e)
\\
&= \sum_{u \in S}\left(\sum_{v \in S}f(uv) + \sum_{v \not \in S}f(uv) - \sum_{v \in S}f(vu) - \sum_{v \not \in S}f(vu)\right)
\\
&= \sum_{u \in S}\left(\sum_{v \in S}f(uv) - \sum_{v \in S}f(vu)\right) + \sum_{u \in S, v \not \in S}f(uv) - \sum_{u \in S, v \not \in S}f(vu)
\end{align*}
$$

em que a primeira soma é claramente igual a 0, porque cada aresta aparece uma sinal com o sinal positivo e uma vez com o sinal negativo. Obtivemos então a segunda equação do teorema.


> **Teorema 2**: para todo $(s, t)$-fluxo $f$ e para todo $(s,t)$-corte $(S, T)$, temos que 
> $$|f| \leq \mathrm{cap}(S, T)$$
Ou seja, o valor de qualquer fluxo é menor ou igual à capacidade de qualquer corte. **Em particular, isso significa que se um fluxo tem valor igual à capacidade de um corte, então esse fluxo é um max-flow e esse corte é um min-cut**

Intuição: a capacidade de um corte é apenas o outgoing flow da primeira partição, sem subtrair o incoming flow, e portanto tem que ser maior ou igual à subtração dos dois, que vai ser o valor do fluxo pela conservação.

Prova:

Utilizando a conservação de fluxo em $S$, e que $(S, T)$ é uma partição dos conjuntos de vértices, obtemos que:

$$
\begin{align*}
|f| = \sum_{u \in S, v \in T}f(uv) - \sum_{u \in S, v \in T}f(vu)
\leq \sum_{u \in S, v \in T}f(uv) = \mathrm{cap}(S, T)
\end{align*}
$$
e está provado o teorema.

Note que esse teorema serve para mostrar que $\mathrm{maxflow(G)} \leq \mathrm{mincut(G)}$.

> **Teorema 3**: 
>Existe um corte com capacidade igual ao maximum flow da rede. Pelo teorema anterior, esse corte será o min-cut.

Prova: 
Considere um maximum flow $f$ (pode haver mais de um, à princípio) obtido pelo algoritmo de Ford-Fulkerson (ou qualquer algoritmo guloso que envolva encontrar paths no grafo residual $G_f$). **Assumimos aqui a corretude desses algoritmos**.

Como o algoritmo terminou de executar, então não existem mais $(s,t)$-augmenting paths  no grafo residual (caminhos da _source_ à _sink_ em que todas as arestas tem capacidades positivas, isto é, uma diferença de fluxo válida). Ou seja, ao menos um vértice, a _sink_ $t$, não é alcançável a partir de $s$ no grafo residual.

Logo, considere $S$ o conjunto de vértices alcançáveis a partir de $s$ no grafo residual, o $T$ o conjunto de vértices não alcançáveis. Então $s \in S$, $t \in T$ e $S\cap T = \emptyset$ - ou seja, é um corte válido. Assim, pelo teorema da conservação de fluxo aplicado a $S$ (Teorema 1):

$$\mathrm{maxflow}(G) = |f| = \sum_{u \in S, v \in T}f(uv) - \sum_{v \in T, u \in S}f(vu)$$
Porém, se existe algum fluxo positivo de um vértice $v \in T$ para um $u \in S$, então no grafo residual existe a aresta $uv$ com capacidade $f(vu) > 0$, necessária para permitir desfazer o consumo desse fluxo nessa direção $v \to u$. Assim, podemos tomar no grafo residual o caminho de $s$ até $u$ e depois a aresta $uv$, que tem capacidade positiva, que teremos um caminho válido de $s$ a $v$, uma contradição (pois $v$ não é alcançável)!

Logo a segunda soma é igual a $0$ e:

$$\mathrm{maxflow}(G) = \sum_{u \in S, v \in T}f(uv) = \mathrm{cap}(S, T)$$

Com isso, obtemos também **qual é o min-cut do grafo / quais são suas arestas**.


> **Min-cut**: um possível min-cut do grafo é definido respectivamente pelo conjunto de vértices alcançáveis e não-alcançáveis a partir da source ao finalizar de executar o algoritmo de Max Flow.
>
> Dessa forma, temos um algoritmo para encontrar o min-cut:
> 1. Execute Dinic/Ford-Fulkerson/Edmonds-Karp (qualquer um funciona)
> 2. Realize BFS no grafo residual a partir de $s$ e considerando apenas as arestas de capacidade positiva para marcar quais são os vértices visitados (alcançáveis) ou não. 
> 3. Esses dois conjuntos serão a partição do min-cut, e as arestas $uv$ com $u$ alcançável e $v$

# CSES: Police Chase

Link: [CSES - Graph Algorithms - Police Chase](https://cses.fi/problemset/task/1695/)

Queremos o menor conjunto de arestas que desconecta esse grafo não-direcionado. Para isso, transformamos ele em direcionado com todas as arestas de peso $1$, e encontramos o min-cut.

Ou seja, adicionamos ambas arestas $uv$ e $vu$ com capacidade $1$ (isso pode levar a múltiplas edges entre um mesmo par no grafo residual, mas isso não é um problema para algoritmos de fluxo)

```c++
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define int long long

/*
Dinic (overview):
// make residual graph (edges and backedges)
// then on each iteration
// do bfs to make layer graph
// do dfs to find blocking flow
*/

const int INF = (int)2e18;
struct Edge {
    int u, v;
    int c, f;
    int other(int x){
        return (x == u ? v : u);
    }
    int cap_from(int x){
        if (x == u){
            return c - f;
        } else {
            return f;
        }
    }

    void add_flow(int from, int dF){
        if (from == u) { // consume flow
            f += dF;
        } else { // undo flow
            f -= dF;
        }
    }
    Edge(int from, int to, int cap) : u(from), v(to), c(cap), f(0) {}
};

struct Dinic {
    int n, s, t;
    vector<vector<Edge*>> adj;  // [cap, to] pairs

    void add_edge(int u, int v, int c){
        // must be heap-allocated, or else will disappear when leaving function
        Edge* e = new Edge(u, v, c);   
        adj[u].emplace_back(e);
        adj[v].emplace_back(e);
    }

    Dinic(const vector<vector<pair<int, int>>> g, int s, int t)
        : n(g.size()), s(s), t(t) {
        adj.resize(n);
        for (int u = 0; u < n; u++){
            for (auto[c, v]: g[u]){
                add_edge(u, v, c);
            }
        }
    }

    // dag adj list, level vector
    pair<vector<vector<Edge*>>, vector<int>> make_dag(){
        vector<vector<Edge*>> dag(n);
        vector<int> level(n, INF);
        queue<int> q;
        q.emplace(s);
        level[s] = 0;
        vector<int> vis(n, false);
        while (!q.empty()){
            int u = q.front();
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (Edge* e: adj[u]){
                if (e->cap_from(u) == 0) continue;  // edge does not exist
                int v = e->other(u);
                if (!vis[v]){
                    level[v] = level[u] + 1;
                    dag[u].emplace_back(e);
                    q.emplace(v);
                }
            }
        }
        return {dag, level};
    }

    // push_flow on layer dag of residual graph 
    int push_flow(int u, vector<int>& blocked, vector<int>& level, int dF = INF){
        if (u == t){
            return dF;  // already at sink
        }
        bool all_neighbors_blocked = true;
        int pushedF = 0;
        for (Edge* e: adj[u]){
            if (dF == 0) break;
            int v = e->other(u);
            if (level[v] != level[u] + 1) continue;  // not dag edge
            if (e->cap_from(u) == 0 || blocked[v]) continue;
            
            // NOTE: this push_flow might block v!
            int delta = push_flow(v, blocked, level, min(e->cap_from(u), dF));
            e->add_flow(u, delta);
            dF -= delta;
            pushedF += delta;

            if (e->cap_from(u) > 0 && !blocked[v]){  // still valid after pushing
                all_neighbors_blocked = false;
            }
        }
        if (all_neighbors_blocked) blocked[u] = true;
        return pushedF;
    }

    int maxflow(){
        while (true){
            auto[dag, level] = make_dag();
            // can't assume anyone is blocked, since we might try to unblock by undoing flow
            if (level[t] == INF) break;  // no more augmenting paths
            vector<int> blocked(n, false);  // indicates that vertex is blocked: can't push flow from it
            push_flow(s, blocked, level);
        }
        int maxFlow = 0;
        for (Edge* e: adj[s]){
            if (s == e->u){  // is origin vertex: forward edge
                maxFlow += e->f;
            } else {  // backward edge
                maxFlow -= e->f; 
            }
        }
        return maxFlow;
    }

    // assumes dinic was called first
    vector<int> mincut(){
        auto[_, level] = make_dag();
        vector<int> partition_num(n);
        for (int u = 0; u < n; u++){
            if (level[u] < INF){
                partition_num[u] = 0;
            } else {
                partition_num[u] = 1;
            }
        }
        return partition_num;
    }
};

signed main(){
	fastio;
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;  // already 1-indexed
        adj[u].emplace_back(1, v);
        adj[v].emplace_back(1, u);
        edges.emplace_back(u, v);
    }
    adj[0].emplace_back(INF, 1);  // source to start vertex

    Dinic d(adj, 0, n);
    int maxflow = d.maxflow();
    int mincut_value = maxflow;
    vector<int> mincut_partition = d.mincut();
    vector<pair<int, int>> cut_edges;
    for (auto[u, v]: edges){
        // edges are undirected so if u,v are in different partitions then
        // there is the edge from the one on partition 0 to the on on partition 1
        if (mincut_partition[u] == 0 && mincut_partition[v] == 1){
            cut_edges.emplace_back(u, v);
        } else if (mincut_partition[u] == 1 && mincut_partition[v] == 0){
            cut_edges.emplace_back(v, u);
        }
    }

    cout << mincut_value << endl;
    for (auto[u, v]: cut_edges) cout << u << " " << v << endl;
}
```

# Referências

- [Vídeo: Proof of Max-Flow Min-Cut Theorem and Ford Fulkerson Correctness](https://www.youtube.com/watch?v=YD3heMex_uw)


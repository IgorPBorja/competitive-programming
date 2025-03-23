
* Resolve fluxo em $O(V^2E)$ independente dos pesos das arestas
# Links


> [!cf-blog-flow] Blog do CF com ótima explicação
> https://codeforces.com/blog/entry/104960?mobile=true


# Ideia principal

## Definições


> [!NOTE] Layered network
> Uma rede de camadas de um grafo $G$ em relação ao source $s$ e às capacidades $C = \{c_{uv}:\ (u, v) \in E\}$ é obtida
> * Rodando BFS no grafo $G'$ obtido desconsiderando arestas exauridas (capacidade $0$) a partir de $s$, calculando $level[u] := d(u, s)$ para todo vértice $u$
> * Mantendo apenas as arestas $(u,v)$ tal que $level[v] = level[u] + 1$, com mesmas capacidades da rede original.

Note que a layered network de $G$ é sempre acíclico, pois o `level` aumenta estritamente em um caminho.


> [!NOTE] Algoritmo de Dinic
> O algoritmo de Dinic consiste em repetidamente:
> * Construir a layered network $G^{layered}$ da rede residual de $G$ (ou seja, transformar a rede residual em um DAG) em relação ao fluxo $F$ atual
> * Encontrar um blocking flow / fluxo $F'$ que satura $G^{layered}$ (e fazer $F \gets F'$)
>   
>   O algoritmo termina quando não é possível encontrar blocking flow - ou seja, quando não é possível chegar ao sink partindo da source.


### Implementação

Ver link https://pastebin.com/rCiZwAwR para implementação do blog do CF citado acima.

```c++
using CAP_T = long long;
using Graph = vector<vector<pair<int, CAP_T>>>;  // u -> v, capacity
const CAP_T INF = 2e9; // TODO change this infinity value according to the problem

struct EdgePair {  // u->v edge pair in residual network
    CAP_T cap, flow;
    int from, to;

    EdgePair(int from, int to, CAP_T cap, CAP_T flow = 0) : from(from), to(to), cap(cap), flow(flow) {}

    int other(int u){
        return (u == from) ? to : from;
    }

    CAP_T cap_from(int u){  // capacity at u -> other(u)
        if (u == from){
            return cap - flow;
        } else {
            return flow;
        }
    }

    void add_flow(int u, CAP_T df){
        if (u == from){
            flow += df;
        } else {
            flow -= df;  // undo flow
        }
    }

    bool exists(int u){
        return cap_from(u) > 0;
    }
};

struct ResidualGraph {   // with layer information
    // NOTE this MUST be shared memory (ptrs), else:
    // 1. edges will be inconsistent with adj
    // 2. update on an edge pair (u->v) will only reflect on adj[u], NOT on adj[v]
    vector<vector<EdgePair*>> adj;
    vector<EdgePair*> edges;  
    vector<int> level;
    int s, t;

    ResidualGraph(const Graph& input_adj, int s, int t) : s(s), t(t) {
        const int n = input_adj.size();
        adj.resize(n);

        for (int u = 0; u < n; u++){
            for (auto[v, c]: input_adj[u]){
                // add edge 
                EdgePair* e = new EdgePair(u, v, c, 0);  // heap-allocated
                if (u != v){  // don't add self-loops
                    adj[u].emplace_back(e);
                    adj[v].emplace_back(e);  // since there is back-edge v->u
                }
                edges.emplace_back(e);
            }
        }

        update_layers();
    }

    // uses BFS to build layered network of residual network (positive capacity edges only)
    void update_layers(){
        level.assign(adj.size(), INF);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()){
            int u = q.front();
            q.pop();
            for (auto e: adj[u]){
                if (!e->exists(u)) continue;
                if (level[e->other(u)] == INF){
                    // undiscovered
                    level[e->other(u)] = level[u] + 1;
                    q.push(e->other(u));
                }
            }
        }
    }

    bool is_reachable(int u){
        return level[u] != INF;
    }
};

namespace MaxFlow {
    // dfs to find blocking flow
    CAP_T push_flow(
        ResidualGraph& G,
        int u,
        vector<int>& blocked,
        CAP_T push_limit = INF
    ){
        if (u == G.t){ // already there!
            return push_limit;
        }
        bool all_neighbors_blocked = true;
        CAP_T pushed = 0;
        for (auto& e: G.adj[u]){
            if (push_limit == 0) break;
            int v = e->other(u);
            if (G.level[v] != G.level[u] + 1) continue;  // not in dag
            if (!e->exists(u) || blocked[v]) continue;  // no edge or can't push nonzero flow through vertex

            // push something (nonzero) through u->v edge
            CAP_T dF = push_flow(G, v, blocked, min(e->cap_from(u), push_limit));
            e->add_flow(u, dF);
            push_limit -= dF;
            pushed += dF;

            // NOTE: this if has to come after previous if, since v might be blocked in this process
            if (e->exists(u) && !blocked[v]){
                // can still use it now
                all_neighbors_blocked = false;
            }
            // NOTE even if capacities are all equal to 1, can't break here (might need to undo some flows later)
        }
        if (all_neighbors_blocked){
            blocked[u] = true;
        }
        return pushed;
    }

    CAP_T dinic(Graph& G, int source, int sink){  // no flow registered
        const int n = G.size();

        ResidualGraph RES_G(G, source, sink);

        while (RES_G.is_reachable(sink)){
            // can't assume anyone is blocked, since we might try to unblock by undoing flow
            vector<int> blocked(n, false);  // 1 if blocked, else 0
            // NOTE: can't just sum dF for maxFlow, these updates might undo flow
            CAP_T dF = push_flow(RES_G, source, blocked);
            RES_G.update_layers();
        }

        CAP_T max_flow = 0;
        for (auto e: RES_G.adj[source]){
            if (e->from == source){
                // forward edge
                max_flow += e->flow;
            } else {
                // backward edge
                max_flow -= e->flow;
            }
        }

        return max_flow;
    }
}
```


> [!NOTE] Sobre a corretude da implementação
> Essa implementação foi testada no problema [CSES - Distinct Routes](https://cses.fi/problemset/task/1711/), ver submissão https://cses.fi/problemset/result/12425653/


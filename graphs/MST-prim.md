# Algoritmo de Prim para minimum spanning tree (MST)

## Pseudo-código
```
bool vis[] = {false, ..., false}
set<Edge> S = empty  // (ordered by edge cost)
F = empty tree

vis[0] = true
for (edge 0 -> v of cost w){
    add Edge(0, v, w) to S
}
while (there is a unvisited vertex or S is not empty){
    let e = (u, v, w) be the minimum edge from S
    S.remove(e)
    add e to F
    vis[v] = true
    // remove ingoing edges to v, recently added
    for (edge u' -> v of cost w'){
        remove Edge(u', v, w') from S
    }
    // add outgoing edges to v, recently added
    for (edge v -> v' of cost w'' such that vis[v'] = false){
        add Edge(v, v', w'') to S
    }
}
if (S is empty but there is unvisited vertex){
    return IMPOSSIBLE
} else {
    return F
}
```

Como cada aresta é, no máximo, adicionada uma vez e removida uma vez do set $S$ (cujo tamanho máximo é $m$), e como o loop `while` acima roda no máximo $n$ iterações (pois cada iteração adiciona um vértice novo na MST), temos que a complexidade do algoritmo é $O(n + m\log m)$.

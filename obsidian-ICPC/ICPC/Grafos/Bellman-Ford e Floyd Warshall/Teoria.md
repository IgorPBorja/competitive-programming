# Bellman Ford

* Complexidade: $O(nm)$
* Funciona em grafos com pesos negativos 
  - Encontra ciclos negativos
  
* Ideia
  - Set all dists to +INF 
  - Processar pelas arestas 
    - Para cada aresta $(u, v, c)$, relaxamos a arestas:
    - **Caso não-direcionado**
      - $w(u) = \min(w(u), w(v) + c)$ 
      - $w(v) = \min(w(v), w(u) + c)$
    - **Caso direcionado**
      - $w(v) = \min(w(v), w(u) + c)$ apenas 
      
* Complexidade $O(nm)$
  Ideia de demonstração: em um grafo sem ciclos negativos, todo caminho possui no máximo $m - 1$ arestas ($m := |E|$). Cada passada do Bellman-Ford aumenta em pelo menos uma aresta os menores caminhos ainda incompletos, e portanto  
  
* Afirmação 1: se $G$ não possui ciclos negativos, então em $m-1$ iterações encontramos todos os menores caminhos 

* Afirmação: $G$ possui ciclos negativos se e só na $m$-ésima iteração de Bellman Ford encontram-se ainda arestas que podem ser relaxadas (é possível minimizar ainda um peso) 

## Contando caminhos com k arestas em $O(n, k)$

* Set vetor inicial de distâncias como $(0, \dotsc, 1, \dotsc, 0)$
* Para cada iteração 

# Floyd-Warshall

* Encontrar a menor distância entre cada par $(u, v)$ do grafo em $O(n^3)$
* Note que, se o grafo não possui pesos negativos, então 
  1. Realizar $n$ Dijkstras (uma vez para cada ponto inicial é $O(n (n + m)\log n)) = O(n^3\logn)$ pois  
  
* Implementação
- Utilizar representação em matriz de adjacência $M \in \operatorname{Mat}_{n, n}(\mathbb{R} \cup \{+\infty\})$, em que o $+\infty$ é utilizado para indicar que não há arestas entre esses dois vértices.
- Convencionamos que a matriz $M$ possui diagonal igual a $0$ (i.e adicionamos um self loop de custo $0$). 
- No caso de grafos não direcionados, a matriz $M$ é simétrica. 
```
let dist[n][n] 
for i=1...n
    for j=1...n
        set dist[i][j] = +INFTY
for k=1...n
    for i=1...n
        for j=1...n
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
```

- Ou seja, para cada $k$ tentamos utilizar ele como um intermediário entre cada par $(i, j)$
- Invariante de loop: na iteração $k$ determinamos todos os caminhos $i \to a_1 \to \dotsc \to a_{m_1} \to k \to b_1 \to \dotsc \to b_{m_2} \to j$, com $a_1, \dotsc, a_{m_1}, b_1, \dotsc, b_{m_2} \in \{0,\dotsc, k-1\}$. 
Prova:

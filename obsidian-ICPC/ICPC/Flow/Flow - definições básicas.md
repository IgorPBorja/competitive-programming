

> [!NOTE] Flow network
> 
> Uma rede de fluxo / flow network é um grafo direcionado $G(V, E)$ com uma função (**capacidade**) $c: E \to \mathbb{R}_{\geq 0}$
> 
> Denotamos por  $\delta^{+}(v)$ ou $out(v)$ o conjunto de arestas que saem de $v$ e $\delta^{-}(v)$ ou $in(v)$ o conjunto de arestas que entram em $v$



> [!NOTE] Flow
> Um fluxo / flow em relação à source $s$ e à sink $t$ é uma função $f: E \to \mathbb{R}$ tal que:
> 
> * Para toda aresta $e \in E$, vale que $0 \leq f(e) \leq c(e)$
> * (Conservação de fluxo: o fluxo que entra é aquele que sai) para todo vértice $v$, **exceto $s, t$**:
> $$\sum_{e \in \delta^{+}(v)}f(e) = \sum_{e \in \delta^{-}(v)}f(e)$$


O valor do fluxo com source $s$ e sink $t$ é definido por

$$val(f) := \sum_{e \in out(s)}f(e) - \sum_{e \in in(s)}f(e) = -\left(\sum_{e \in out(t)}f(e) - \sum_{e \in in(t)}f(e)\right) $$ 
Esse é o fluxo "extra", criado do nada / que **sai** de $s$ vindo de **fontes externas**. Equivalentemente, é o fluxo que **chega** em $t$ vindo de fontes externas. Ou seja, é o **volume total (global) no sistema**.



> [!NOTE] Max flow
> O problema do fluxo máximo é encontrar um fluxo $f$ que maximiza $val(f)$


> [!NOTE] Rede residual
> Dado um grafo $G = (V, E)$ com capacidades associadas $c_{uv},  (u, v) \in E$, o grafo residual relativo ao sistema de fluxos $F= \{f_{uv}: (u, v) \in E\}$ é o grafo $G^R$ de mesmos vértices no qual, para cada aresta $(u, v) \in E$, adicionamos ambas as arestas 
> * $(u, v)$ com capacidade $c_{uv}^R = c_{uv} - f_{uv}$ (consumimos o fluxo)
> * $(v, u)$ com capacidade $c_{vu}^R = f_{uv}$ (possibilitamos o _undo_ do consumo do fluxo)


> [!NOTE] Blocking flow
> Um blocking flow é um fluxo $F = \{f_{uv}: (u, v) \in E\}$ (ou seja, com $0 \leq f_{uv} \leq c_{uv}$ para todo $(u, v) \in E$) tal que **ao menos uma aresta é saturada**.
> 
> Ou seja, existe $(u_0, v_0)$ tal que $f_{u_0 v_0} = c_{u_0 v_0}$.


# Algoritmos de fluxo: essência  / visão geral

# Preliminares

Os algoritmos de fluxo são **gulosos** em essência.

Porém um guloso puro é ruim (escolhas iniciais bloqueiam caminhos, arruinando escolhas futuras). Por isso queremos um guloso que **não bloqueie escolhas futuras**.

Note que se $f$ e $f'$ são dois fluxos, então $f' - f$ é **quase como um fluxo**: a soma da função sobre as arestas que chegam em $v$ é igual à soma das arestas que saem de $v$, e ele satisfaz a regra ligeiramente modificada que

$$-f(e) \leq f'(e) - f(e) \leq c(e) - f(e)$$

> [!NOTE] Flow difference
> Dado um grafo $G$ e um fluxo $f$, uma função $g$ que satisfaz
> * $-f(e) \leq g(e) \leq c(e) - f(e)$ para toda aresta $e \in E$
> * Para todo vértice $v$,
> * $$\sum_{e \in out(v)}g(e) = \sum_{e \in in(v)}g(e)$$
> é chamada de flow difference.


> [!NOTE] TEOREMA 1:
> Se $f$ é um fluxo e $g$ é uma diferença de fluxo / flow difference **em relação a $f$**, então $f + g$ é um fluxo.
> 
> Além disso, qualquer fluxo $f'$ pode ser obtido aplicando uma diferença de fluxo sobre $f$.

Prova: a primeira parte é trivial. Para a segunda, basta observar que $f' - f$ é uma diferença de fluxo.

**As diferenças de fluxo são as mudanças que podemos aplicar a $f$**: podemos "roubar" até $f(e)$ da aresta $e$, ou colocar até no máximo $c(e) - f(e)$ de fluxo a mais naquela aresta - porém a regra da conservação precisa continuar valendo.



> [!NOTE] TEOREMA 2
> Dado um fluxo $f$, existe uma bijeção natural entre as diferenças de fluxo em cima de $f$ e os fluxos na rede residual $G_f$.

Isso explica **porque construir o grafo residual na implementação de Dinic: encontrar fluxos máximos nesse grafo é nossa forma de encontrar diferenças de fluxo ótimas para serem aplicadas sobre o fluxo $f$ atual**.

## Implementação (genérica)

```
function find_blocking_flow(G (rede), c (capacidades), s (source), t (sink)):
	...

function max_flow(G (rede), c (capacidades), s (source), t (sink)):
	f = [0 for each edge e]
	while t é alcançável a partir de s:
		calcula G_f
		df = find_blocking_flow(Gf, c, s, t)
		f <- f + df
```


## Implementação (Ford-Fulkerson)


```
function find_blocking_flow(G, c, s, t):
	executa DFS para encontrar um caminho qualquer s =: u_0, u_1, ..., u_n := t com capacidades positivas
	return min(c[u_0], ..., c[u_n]) 
```

**Complexidade total do Ford-Fulkerson: $O(VE^2)$**

## Implementação (Edmonds-Karp)

```
function find_blocking_flow(G, c, s, t):
	executa BFS para encontrar um caminho s =: u_0, u_1, ..., u_n := t de tamanho MÍNIMO com capacidades positivas
	return min(c[u_0], ..., c[u_n]) 
```

**Complexidade total do Edmonds-Karp: $O(VE^2)$

## Implementação (Dinic)

```
function find_blocking_flow(G, c, s, t):
	monta a layered network D de G usando BFS (note que D é um DAG)
	encontra um blocking flow df em D usando DFS
	return df
```

**Complexidade total do Dinic: $O(V^2E)$**

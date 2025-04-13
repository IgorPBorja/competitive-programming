> [!NOTE] PONTO DE ARTICULAÇÃO
> Ponto de articulação é um **vértice que, se removido, aumenta a quantidade de componentes conexos**


> [!NOTE] PONTE
>  Ponte é uma **aresta que, se removida, aumenta a quantidade de componentes conexos**


# Algoritmo de Tarjan


> [!NOTE] Definimos:
> $discovery(u):=$ índice da iteração que visita $u$ pela primeira vez
> $low(u) :=$ menor $discovery(v)$ para cada $v$ na **spanning subtree** da DFS começando em $u$ (**incluindo as back-edges, na orientação que são visitadas, EXCETO back-edges para o parent**).


> [!Thm1] Teorema: $u$ é ponto de articulação se e só se
> $$\min_{v \in N(u)} low(v) >= discovery(u)$$ 

Prova: 
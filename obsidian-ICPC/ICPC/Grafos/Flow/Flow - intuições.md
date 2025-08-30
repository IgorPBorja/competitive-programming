Refira a [[Flow - definições básicas]] para definições mais formais

# 1. A quantidade de fluxo que entra por fontes externas é a quantidade de fluxo que sai do sistema

Em outras palavras, para source $s$ e sink $t$

$$
\operatorname{val}(f) = \sum_{e \in \delta^+(s)}f(e) - \sum_{e \in \delta^-(s)}f(e) = \sum_{e \in \delta^-(t)}f(e) - \sum_{e \in \delta^+(t)}f(e)
$$

em outras palavras

$$F^{+}(s) - F^{-}(s) = F^{-}(t) - F^{+}(t)$$
em que $F^{+}$ é fluxo total de saída (outgoing) e $F^{-}$ é fluxo total de entrada.

É fácil observar que, como $F^{+}(u) = F^{-}(u)$ por definição para todo nó $u \neq s,t$ (nó que não se liga para fora do sistema), então

$$
F^{+}(s) - F^{-}(s) = \sum_{u \neq t}(F^{+}(u) - F^{-}(u)) = \sum_{u}(F^{+}(u) - F^{-}(u))  - (F^{+}(t) - F^{-}(t)) = F^{-}(t) - F^{+}(t)
$$
Essa soma final é 0 intuitivamente porque **todo o fluxo que entra no sistema de fontes externas precisa sair do sistema** , ou seja, por uma propriedade da física mesmo.

# 2. Insights sobre grafo residual

### 2.1 Fluxos na rede residual tem correspondência 1-para-1 com diferenças de fluxos

**O valor no fluxo $g$ na rede residual sobre uma aresta para frente/_forward edge_ $e$ é quanto da capacidade foi consumida, e o seu valor na _back edge_ $\overleftarrow{e}$ é quanto do consumo de $f$ foi desfeito**.

> [!important] 
> Dessa forma, é evidente que $g$ é uma diferença de fluxo: se consumimos $g(e)$ da capacidade deixada por $f$, e depois desfazemos $g(\overleftarrow{e})$ do consumo realizado por $f$, então foi feita uma mudança no fluxo que mantém a invariante de conservação de vazão, e dessa forma $g$ é uma **transição válida / uma diferença de fluxo**.


Uma diferença de fluxo é como se fosse uma **transição entre estados (fluxos diferentes)** -  e de fato, quaisquer dois fluxos estão ligados por uma diferença de fluxos. Dessa forma, encontrar um blocking flow no grafo residual corresponde a 

### 2.1 - Prova formal da correspondência

Formalmente: 
O consumo resultante da capacidade residual (residual = deixada pelo fluxo $f$) por $g$ é **um fluxo no grafo original $G$ definido por $g'(e) = g(e) - g(\overleftarrow{e})$.

Como $0 \leq g(e) \leq c(e) - f(e)$ e $0 \leq g(\overleftarrow{e}) \leq f(e)$ então $-f(e) \leq g'(e) \leq c(e) - f(e)$.

Note que, pela definição de rede residual, as arestas que **saem** de $u$ no grafo residual são as arestas que saem de $u$ no grafo original, mais os reversos das arestas que chegam em $u$ no grafo original - ou seja, 

$$\delta^{+}_{G_f}(u) = \delta^{+}_G(u) \cup \{\overleftarrow{e}: e \in \delta^{-}_G(u)\}$$
e vale o oposto para as arestas que **chegam** a $u$ no grafo residual, por simetria. Dessa forma:

$$
\begin{align*}
\sum_{e \in \delta^{-}_{G}(u)}g'(e) - \sum_{e \in \delta^{+}_G(u)}g'(e)
&=
\sum_{e \in \delta^{-}_{G}(u)}g(e) - \sum_{e \in \delta^{-}_{G}(u)} g(\overleftarrow{e})
- \sum_{e \in \delta^{+}_{G}(u)}g(e) + \sum_{e \in \delta^{+}_{G}(u)} g(\overleftarrow{e})
\\
&= \left(\sum_{e \in \delta^{-}_{G}(u)}g(e) + \sum_{e \in \delta^{+}_{G}(u)} g(\overleftarrow{e})\right)
- \left(\sum_{e \in \delta^{+}_{G}(u)}g(e) + \sum_{e \in \delta^{-}_{G}(u)} g(\overleftarrow{e})\right)
\\
&=
\sum_{e \in \delta^{-}_{G_f}(u)}g(e) - \sum_{e \in \delta^{+}_{G_f}(u)}g(e) = 0
\end{align*}
$$

pois $g$ é um fluxo no grafo residual. Logo $g'$ é uma diferença de fluxo no grafo original.

Reciprocamente, se temos uma diferença de fluxo $g'$ no grafo original, podemos obter um fluxo $g$ no grafo residual colocando

* sobre as forward edges $e$, quanto a diferença de fluxo consome da capacidade residual: ou seja: $\max(0, g'(e))$
* sobre as back edges $\overleftarrow{e}$, quanto a diferença de fluxo devolve à capacidade residual: ou seja: $\max(0, -g'(e))$

Note que o primeiro equivalente a: $g(e) = 0$ se $g'(e) < 0$ (isto é, se foi devolvida capacidade nessa aresta) ou $g(e) = g'(e)$ do contrário (quanto foi consumido). Analogamente, 

Logo

$$
\begin{align*}
\sum_{e \in \delta^{-}_{G_f}(u)}g(e)
&= \sum_{e \in \delta^{-}_G(u)}g(e) + \sum_{e \in \delta^{+}_G(u)}g(\overleftarrow{e})
\\
&= \sum_{e \in \delta^{-}_G(u), g'(e) > 0}g'(e) - \sum_{e \in \delta^{+}_G(u), g'(e) < 0}g'(e)
\\
&\overset{\text{conservação de vazão sobre $g'$}}{=}
-\sum_{e \in \delta^{-}_G(u), g'(e) < 0}g'(e) + \sum_{e \in \delta^{+}_G(u), g'(e) > 0}g'(e)
\\
&= - \sum_{e \in \delta^{+}_G(u)}g(\overleftarrow{e}) + \sum_{e \in \delta^{+}_G(u)}g(e) = \sum_{e \in \delta^{+}_{G_f}(u)}g(e)
\end{align*}
$$

mostrando que $g$ é um fluxo sobre a rede residual.
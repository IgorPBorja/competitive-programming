#strings 

Ver [[Suffix array]] antes desse tópico.

Referência: 

![[computing-longest-common-substrings-via-suffix-arrays.pdf]]

Consideraremos a seguinte generalização do problema, que chamaremos aqui de $K$-LCS.

> Dada uma coleção de $N$ strings $A = \{\alpha_1, \dotsc, \alpha_n\}$, encontre a maior string $\beta$ que é uma substring de ao menos $K$ delas

Assim, o problema do LCS clássico é obtido restringindo $N = K = 2$.

## Notação

Considere a string $\alpha = \alpha_1\$_1 \dotsc \alpha_N \$_N$ , obtida da concatenação de cada palavra seguida de um **caractere sentinela diferente** (isto é, $\$_i \neq \$_j$ para $i\neq j$).

Dizemos que uma posição $1 \leq i \leq |\alpha|$ é **essencial** se ela pertence a alguma string $\alpha_j$, e não-essencial se ela é algum dos caracteres sentinelas. Em especial, se $i$ é uma posição que pertence à string $\alpha_j$ dizemos que ela é do tipo $j$.

> Teorema 1: Diga que um conjunto $P$ de posições é _$K$-diverso_ se possui ao menos $K$ posições essenciais de tipos distintos.
> Então $\operatorname{K-LCS}(\alpha_1, \dotsc, \alpha_N)$ é igual a
> $$\max_{P = \{p_1, \dotsc, p_m\}, P \text{ é $K$-diverso}} \operatorname{lcp}(\alpha[p_1...], \dotsc, \alpha[p_m...])$$
> (em que LCP é o _longest common prefix_ - ver [[Suffix array]])

Prova (sketch):

Ora, toda substring é um prefixo de algum sufixo, o que explica que tomar o LCP sobre todos os conjuntos de sufixos seja exaustivo. Além disso, $P$ ser $K$-diverso é a nossa forma de garantir que estamos pegando substrings de pelo menos $K$ strings distintas de nossa coleção.
$$\tag*{$\blacksquare$}$$

Seja $\sigma$ uma permutação de $P$ tal que $rank(p_{\sigma(1)}) < rank(p_{\sigma(2)}) < \dotsc < rank(p_{\sigma(m)})$. Temos então pelo teorema de LCP sobre ranges em [[Suffix array]], porém estendido agora para $m$ termos (o que não é difícil) que, abusando um pouco da notação:

$$\begin{align*}

\operatorname{lcp}(p_{\sigma(1)}, \dotsc, p_{\sigma(m)})
&= \min(\operatorname{lcp}(p_{\sigma(1)}, p_{\sigma(2)}), \operatorname{lcp}(p_{\sigma(2)}, \dotsc, p_{\sigma(m)}))
\\
&= \dotsc = \min_{1 \leq i < m}\operatorname{lcp}(p_{\sigma(i)}, p_{\sigma(i + 1)})
\\
&= \min_{1 \leq i < m}\min_{rank(p_{\sigma(i)}) \leq k < rank(p_{\sigma(i + 1)})}A_{LCP}[k]
\\
&= \min_{R^{-} \leq k < R^{+}}A_{LCP}[k]
\end{align*}
$$
em que $R^{-} = \min rank(p_i)$ e $R^{+} = \max rank(p_i)$.

Ou seja, **sempre temos um intervalo no array de LCP**, para qualquer conjunto de posições que tomemos.

Dessa forma, se estendermos a definição para dizer que um intervalo contíguo $\Delta = [\Delta^{-}, \Delta^{+}]$ de $[1,L]$ com $L := |\alpha|$ é _$K$-diverso_ se contém posições se ao menos $K$ strings diferentes, então é fácil derivar o seguinte:

> Teorema 2: O $K$-LCS é
> $$\max_{\Delta \text{ é $K$-diverso}} \min_{\Delta^{-} \leq i < \Delta^{+}}A_{LCP}[i]$$

Note que, pela monotonicidade do mínimo, contrair o range é tão bom quanto ou menor: se temos um intervalo $\Delta$ que é $K$-diverso com um subintervalo $\tilde{\Delta}$ que continua $K$-diverso, então o seu "_score_" é maior ou igual:

$$\min_{\tilde{\Delta}^{-} \leq i < \tilde{\Delta}^{+}}A_{LCP}[i] \geq \min_{\Delta^{-} \leq i < \Delta^{+}}A_{LCP}[i]$$

Dessa forma, se fixarmos que a primeira posição escolhida começará na posição $1 \leq i \leq L$, então podemos assumir que, considerando que **não existam strings vazias**, a última posição será o menor $i < j \leq L$ tal que no conjunto $[SA[i], \dotsc, SA[j]]$ existam posições vindas de pelo menos $K$ strings diferentes dentre o conjunto $\{\alpha_1, \dotsc, \alpha_N\}$, e o valor de K-LCS associado à essa opção será de $\min_{i \leq p < j}A_{LCP}[p]$.

Note que podemos determinar à qual uma string uma posição em $\alpha$ pertence via busca binária e computando prefix-sums, uma vez que a string $\alpha_i$ tem como range de posições desde $s_i = \sum_{j=1}^{i-1}(|\alpha_j| + 1)$ a $e_i = \sum_{j=1}^{i}(\alpha_j + 1) - 1$ (**considerando posições 0-indexadas**). O $+1$ é devido ao caractere de sentinela que vem depois de cada string $\alpha_j$.

Logo, **podemos resolver o problema utilizando uma janela deslizante (TWO-POINTERS) e busca binária em um total de $O(L \log L)$ com $L = \sum |\alpha_i|$.**


> [!tip] Mantendo a quantidade de posições pertencentes à cada string
> Para saber quantas posições de cada string em uma janela deslizante $[l, r]$, podemos manter:
>
> * $n$ filas $Q_1, \dotsc, Q_N$ com as posições da janela pertencentes a $\alpha_1, \dotsc, \alpha_N$, em ordem de chegada
> * um contador $C$ de quantas filas diferentes não estão vazias (em quantas strings diferentes encontramos posições vindas dessa janela deslizante)
>
> Ao ler uma nova posição na expansão da borda direita da janela, calculamos via busca binária a que string ela pertence e acrescentando à respectiva fila. Se ela estava vazia antes disso, incrementamos o contador $C$.
>
> Ao remover uma posição (contração da borda esquerda da janela), calculamos via busca binária a que string ela pertence e removemos o primeiro elemento da respectiva fila (**isso funciona, já que filas são FIFO e janelas deslizantes também**). Se ela se tornou vazia depois disso, decrementamos o contador $C$.
>
> Se o contador $C$ satisfaz $C \geq K$, então calculamos $\min_{l \leq i < r}A_{LCP}[i]$ utilizando SegTree em $O(\log L)$ ou RMQ em $O(1)$ amortizado e maximizamos a resposta atual conforme esse valor.


> [!tip] LCS clássico ($N=K=2$)
Para o LCS clássico, podemos iterar apenas sobre os pares $SA[i], SA[i+1]$ que pertençam a strings diferentes, e tomar o mínimo entre $A_{LCP}[i]$ para esses valores.

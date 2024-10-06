# Links


> [!cp-algorithms-sat] 2-SAT: artigo em CP-algorithms
> [2SAT em cp-algorithms.com](https://cp-algorithms.com/graph/2SAT.html)

## Definição

O problema de 2-SAT (SAT = satisfatibilidade booleana) é o problema de determinar se fórmulas na CNF (forma normal conjuntiva) em que as **disjunções internas possuem apenas DOIS literais** são satisfatíveis. Esse formato é chamado de **2-CNF**.

Ou seja, fórmulas no formato
$$\phi = \bigwedge_{1 \leq i \leq n}(a_i \lor b_i)$$
em que cada $a_i, b_i$ são literais: variáveis ou negação de uma variável. Isto é, $a_i = x$ ou $a_i = \lnot x$ para alguma variável $x$,  e o mesmo para $b_i$.

## Abordagem via SCCs

Note que podemos escrever
$$(a_i \lor b_i) \equiv (\lnot a_i \implies b_i) \equiv (\lnot b_i \implies a_i)$$

> [!implication-graph] *Implication graph*
> Seja $V = var(\phi)$ o conjunto de variáveis utilizadas em $\phi$. Então montamos um grafo **direcionado** $G(\phi)$ com vértices em $V \cup \lnot V$ e arestas $(\lnot a_i, b_i)$ e $(\lnot b_i, a_i)$ para todo $1 \leq i \leq n$.




> [!sat-scc-theorem] Teorema 1:
> A fórmula $\phi$ em 2-CNF é satisfatível se e só se, para todo literal $x \in V \cup \lnot V$, os vértices $x$ e $\lnot x$ não estão no mesmo componente fortemente conexo em $G$.
>
^sat-scc-theorem

Prova:
($\implies$ / é condição necessária para satisfatibilidade) Suponha que $x$ e $\lnot x$ estão no mesmo componente fortemente conexo: então existe um caminho $x \implies u_1 \implies \dotsc \implies u_{k_1} \implies \lnot x \implies v_1 \implies \dotsc \implies v_{k_2} \implies x$ (com $k_1, k_2 \geq 0$), e portanto pela transitividade da implicação temos que $x \implies \lnot x$ e $\lnot x \implies x$, uma conjunção que é equivalente a $x \land \lnot x$, contradição! 

($\impliedby$/ é condição suficiente para satisfatibilidade) Seja $H = G(\phi) / SCC$  o grafo direcionado quociente obtido contraindo cada componente fortemente conexo de $G(\phi)$ para um único vértice. É fácil ver que $H$ é um DAG (veja a demonstração em [[SCC#^dbfbaa]]).

Sejam $C_1, \dotsc, C_n$ os vértices de $H$, **ordenados conforme uma ordenação topológica**, cada um representando um componente fortemente conexo, e para cada literal $a \in V \cup \lnot V$ seja $f(a) \in \{1, \dotsc, n\}$ o índice do componente fortemente conexo em que $a$ aparece. Considere a seguinte valoração $\nu$ : para cada variável $x \in V$,
$$\nu(x) = \begin{cases}1 \text{ se } f(x) < f(\lnot x) \\ 0 \text{ se } f(\lnot x) < f(x)\end{cases}$$
Note que essa função está bem definida devido à restrição do grafo, que garante que um literal e sua negação não estão no mesmo componente fortemente conexo. Essa é a valoração "natural" pensando na ordenação topológica.

Vamos inverter essa valoração: pensar em $\lnot \nu(x)$. Por quê? Porque sabemos que se existe um $(a, \lnot a)$ caminho, então $a$ aparece antes na ordenação topológica do grafo contraído (já que estão em componentes distintos),  porém (pelo mesmo argumento feito na "ida" da demonstração) vale que $a \implies \lnot a$, o que é equivalente a $\lnot a \lor \lnot a \equiv \lnot a$. Ou seja, devemos tornar **falsos** os literais que aparecem **na ordem da ordenação topológica**.

De fato, para todo $1 \leq i \leq n$, como existe uma aresta $(\lnot a_i, b_i)$ e uma aresta $(\lnot b_i, a_i)$, então temos que 
$$
\begin{align*}
f(\lnot a_i) \leq f(b_i)
\\
f(\lnot b_i) \leq f(a_i)
\end{align*}
$$
em que a igualdade ocorre se o par estiver na mesma componente fortemente conexa. Dessa forma, suponha que a valoração $\lnot v$ não satisfaz a disjunção $a_i \lor b_i$. Então vale (**pela restrição do grafo**) que $v(a_i) \land v(b_i)$, isto é, $f(a_i) < f(\lnot a_i)$ e $f(b_i) < f(\lnot b_i)$. Juntando essas desigualdades temos que:
$$
f(a_i) < f(\lnot a_i) \leq f(b_i) < f(\lnot b_i) \leq f(a_i)
$$

contradição! Ou seja, **a valoração construída satisfaz cada disjunção** $a_i \lor b_i$, e portanto $(\lnot v)(\phi) = \bigwedge\limits_{1 \leq i \leq n}(\lnot v)(a_i \lor b_i)$ é verdadeira, pois todas as disjunções são satisfeitas!
$$\tag*{$\blacksquare$}$$


> [!2-sat-verification] Observação:
> Note que, de posse da valoração desejada $\lnot v$ (que considera o reverso da ordenação topológica), podemos **verificar sua validade** apenas avaliando a fórmula $\phi$ em $O(m)$, em que $m$ é a quantidade de cláusulas.



> [!2-sat-complexity] Teorema 2 
> A complexidade de $2-SAT$ é $O(n + m)$, em que $n$ é a quantidade de variáveis e $m$ a quantidade de cláusulas. ^2-sat-complexity


> [!2sat-corollary-1] Corolário 1
> Se $\phi$ é uma fórmula em 2-CNF satisfatível então
>1. Para todos dois literais $a, b \in V \cup \lnot V$, não existe um caminho em $G(\phi)$ que visite $\lnot a, a, b, \lnot b$ nessa ordem (possivelmente com vértices adicionais entre cada um, evidentemente).

Prova: Queremos mostrar que $\phi$ ser satisfatível implica essa restrição no grafo $G(\phi)$ - procedemos por contradição. Ou seja, suponha que existem dois literais $a, b \in V$ e um caminho $P$ que visita $\lnot a, a, b, \lnot b$ nessa ordem. Então
*  Existem inteiros não-negativos $k_1, k_2, k_3$ e vértices $u_{1}^{(i)}, \dotsc, u_{k_i}^{(i)}$ ($i=1,2,3$) tais que $$P = \lnot a \implies u_{1}^{(1)} \implies \dotsc u_{k_2}^{(1)} \implies a \implies u_{1}^{(2)} \implies \dotsc u_{k_2}^{(2)} \implies b \implies u_{1}^{(3)} \implies \dotsc u_{k_3}^{(3)} \implies \lnot b$$
e portanto pela transitividade da implicação $(\lnot a \implies a) \land (a \implies b) \land (b \implies \lnot b)$. Porém:
$$\begin{align*}
(\lnot a \implies a) \land (a \implies b) \land (b \implies \lnot b)
&\equiv (a \lor a) \land (\lnot a \lor b) \land (\lnot b \lor \lnot b)
\\
&\equiv a \land (\lnot a \lor b) \land \lnot b
\\
&\equiv \lnot (\lnot a \lor b) \land (\lnot a \lor b) \equiv \bot
\end{align*}$$

contradição! Portanto a restrição no grafo vale.



## Implementação (com Kosaraju)

* Representamos as variáveis como números de $0$ a $n-1$ e a negação de $i$ é $n + i$ .
* Depende do seguinte Teorema (para poder fazer apenas Kosaraju, sem aplicar ordenação topológica em cima do resultado nem montar de fato o grafo quociente)


> [!kosaraju-topological-order] Teorema 2
> O algoritmo de Kosaraju gera os números dos componentes fortemente conexos em ordenação topológica.


```c++
namespace SAT2 {
    vector<vector<i64>> build_graph(const vector<pair<i64, i64>> &clauses, i64 n){
        vector<vector<i64>> g(2 * n);
        for (auto[x, y]: clauses){
            // (x or y) clause = (~x => y) clause and (~y => x) clause
            g[(x + n) % (2 * n)].emplace_back(y);
            g[(y + n) % (2 * n)].emplace_back(x);
        }
        return g;
    }
    vector<vector<i64>> transpose(vector<vector<i64>> &g){
        vector<vector<i64>> gt(g.size());
        for (i64 u = 0; u < g.size(); u++){
            for (i64 v: g[u]){
                gt[v].emplace_back(u);
            }
        }
        return gt;
    }

    void forward_dfs(const i64 u, vector<vector<i64>> &g, vector<bool> &vis, vector<i64> &stack){
        vis[u] = true;
        for (i64 v: g[u]){
            if (!vis[v]){
                forward_dfs(v, g, vis, stack);
            }
        }
        stack.emplace_back(u);
    }

    void backward_dfs(const i64 u, vector<vector<i64>> &g, vector<bool> &vis, vector<i64> &comp, i64 c = 0){
        vis[u] = true;
        comp[u] = c;
        for (i64 v: g[u]){
            if (!vis[v]){
                backward_dfs(v, g, vis, comp, c);
            }
        }
    }

    pair<vector<i64>, i64> scc(const vector<pair<i64, i64>> &clauses, i64 n){
        vector<vector<i64>> g = build_graph(clauses, n);
        vector<vector<i64>> gt = transpose(g);

        const i64 s = g.size();
        vector<i64> stack, comp(s);
        vector<bool> vis(s, false);
        for (i64 u = 0; u < s; u++){
            if (!vis[u]){
                forward_dfs(u, g, vis, stack);
            }
        }
        reverse(stack.begin(), stack.end());
        fill(vis.begin(), vis.end(), false);
        i64 c = 0;
        for (i64 u: stack){
            if (!vis[u]){
                backward_dfs(u, gt, vis, comp, c);
                ++c;
            }
        }
        return {comp, c};
    }

    pair<vector<bool>, bool> solve(const vector<pair<i64, i64>>& clauses, i64 n){
        // run scc (Kosaraju)
        auto[comp, num_comps] = scc(clauses, n);

        // build valuation: mark as true the first one that appears
        vector<bool> valuation(n);
        for (i64 u = 0; u < n; u++){
            if (comp[u] < comp[u + n]){
                valuation[u] = false;
            } else {
                valuation[u] = true;
            }
        }

        // check valuation
        bool ok = true;
        for (auto[x, y]: clauses){
            bool left = ((x < n) ? valuation[x] : !valuation[x - n]);
            bool right = ((y < n) ? valuation[y] : !valuation[y - n]);
            ok &= left | right;
        }
        return {valuation, ok};
    }
};

```
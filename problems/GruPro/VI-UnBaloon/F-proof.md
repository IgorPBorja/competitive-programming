Esse blog é a solução e explicação completa da [questão F da VI UnBalloon](https://codeforces.com/gym/105900/problem/F).

> Problema: dados $1 \leq a, b \leq 10^9 + 9$ e $1 \leq M \leq 10^9 + 9$, calcule $F_{a^b} \mod M$, em que $F_n$ é o $n$-ésimo número de Fibonacci.

Observe que a sequência de Fibonacci é uma recorrência linear, e portanto é governada pela matriz de transição
$$Q = \begin{pmatrix}1 & 1 \\ 1 & 0\end{pmatrix}$$
de forma que, pondo $F_0 = 0$ e $F_1 = 1$ temos que

$$Q^k = \begin{pmatrix} F_{k + 1} & F_k \\ F_k & F_{k - 1}\end{pmatrix}$$

Observe que, como a sequência é totalmente determinada por um par de números adjacentes, e existem apenas $O(M^2)$ pares possíveis, em algum momento a sequência mod $M$ vai começar a se repetir. De fato, temos um resultado ainda mais forte: ela vai voltar para os dois termos iniciais $0, 1$, em vez de ciclar a partir de um ponto qualquer. Isso permite definir um período $\pi(M)$, que é o tamanho desse ciclo, e calcular $F_k$ como $F_{k \mod \pi(M)}$ e mais geralmente $Q^k$ como $Q^{k \mod \pi(M)}$, que será nossa estratégia para esse problema. **De fato, **encontrar o período exato não é necessário, basta um múltiplo $k$ do período**. Dessa forma, de forma análoga à aplicação do Pequeno Teorema de Fermat ou do Teorema de Euler, teremos que $Q^{a^b} = Q^{a^b \mod k} \mod M$, e poderemos realizar a exponenciação binária $a^b \mod k$ para em seguida realizar a exponenciação binária da matriz, em $O(\log k + \log M)$. 

> Lema 1: Seja $k$ o menor inteiro tal que existe um $j < k$ com $F_j = F_k$ e $F_{j + 1} = F_{k + 1}$, ou seja, $k$ é a primeira ocorrência de uma repetição de pares. Então $F_k = 0$ e $F_{k + 1} = 1$.

Prova: suponha que na primeira ocorrência de repetição temos $(F_k, F_{k + 1}) = (F_j, F_{j + 1})$ com $j > 0$. Então $F_{j - 1} = F_{j + 1} - F_j = F_{k + 1} - F_k = F_{k - 1}$ e assim $(F_{k - 1}, F_k) = (F_{j - 1}, F_j)$, contradizendo a minimalidade do $k$.

> Nota: o Lema 1 também pode ser provado a partir do fato que a matriz de transição é invertível mod $n$, para todo $n$, por possuir determinante $-1$.

Vamos mostrar que a periodicidade pode ser quebrada conforme os fatores primos de $M$. Assim, podemos fatorar $M = p_1^{\alpha_1} \dotsc p_\ell^{\alpha_\ell}$ em $O(\sqrt M)$ e encontrar um múltiplo de cada um dos períodos mod $p_i^{\alpha_i}$. 

> Teorema 1: Dados dois inteiros $m,n$ primos entre si, $\pi(mn) = \mathrm{lcm}(\pi(m), \pi(n))$

Prova: temos que $F_{k + \pi(mn)} \equiv F_k \mod mn$ para todos $k \geq 0$. Então eles também são congruentes mod $m$ e $n$, isto é, $\pi(n) | \pi(mn)$ e $\pi(m) | \pi(mn)$. Se $m, n$ são coprimos, vale o sentido contrário da relação de divisibilidade: de fato, se $p = \mathrm{lcm}(\pi(m), \pi(n))$, isto é $m$ e $n$ dividem $F_{k + p} - F_k$ para todo $k$, então como $\mathrm{gcd}(m,n) = 1$ (e logo $\mathrm{lcm}(m,n) = mn$) concluímos que $mn$ divide $F_{k + p} - F_k$ e que, logo, $\pi(mn) | \mathrm{lcm}(\pi(m), \pi(n))$, de onde segue a igualdade.


Dessa forma, segue que

$$\pi(M) = \mathrm{lcm}(\pi(p_1^{\alpha_1}), \dotsc, \pi(p_\ell^{\alpha_ell}))$$


Precisamos agora analisar os períodos mod uma potência de um primo, isto é, $p^k$.

> Teorema 2: Para todo primo $p$, $\pi(p^k)$ divide $p^{k-1} \cdot \pi(p)$

Prova: sabemos que $Q^{\pi(p)} \equiv I \mod p$. Dessa forma, $Q^{\pi(p)} = I + pM$ onde $M$ é uma matriz $2 \times 2$ qualquer. Assim,

$$Q^{\pi(p) \cdot p^{k - 1}} = I + \sum_{j = 1}^{p^{k - 1}}\binom{p^{k - 1}}{j}p^jM^j$$

Observe que, pela [fórmula de Legendre](https://en.wikipedia.org/wiki/Legendre%27s_formula):

$$
v_p\left(\binom{p^{k - 1}}{j}) = v_p(p^{k-1}!) - v_p(j!) - v_p((p^{k - 1} - j)!\right) = \sum_{\ell = 1}^{k-1}\left(
\left\lfloor \dfrac{p^{k - 1}}{p^\ell} \right\rfloor
- \left\lfloor \dfrac{j}{p^\ell} \right\rfloor
- \left\lfloor \dfrac{p^{k - 1} - j}{p^\ell} \right\rfloor
\right)
$$

Quando $p^\ell \nmid k$, ou seja $j = qp^\ell + r$ com $r > 0$, então $\left\lfloor \dfrac{j}{p^\ell} \right\rfloor = q$ e $\left\lfloor \dfrac{p^{k - 1} - j}{p^\ell} \right\rfloor = p^{k - 1 - \ell} - q - 1$, de forma que a soma resulta em $1$ unidade a menos que $p^{k - 1 - \ell}$. Assim, cada termo na soma é $0$, se $p^\ell$ divide $j$, e $1$ do contrário, de onde segue que $v_p(\binom{p^{k - 1}}{j}) = k - 1 - v_p(j)$ (demonstração retirada [desse post no MathStackExchange](https://math.stackexchange.com/questions/4901805/p-adic-valuation-of-a-binomial-coefficient)). Logo, na expansão de $Q^{\pi(p) \cdot p^{k-1}}$, cada termo $\binom{p^{k - 1}}{j}p^j$ com $j > 0$ tem como maior potência de $p$ que o divide aquele com expoente $k - 1 - v_p(j) + j \geq k$, e portanto é $0 \mod p^k$. Logo $Q^{\pi(p) \cdot p^{k-1}} \equiv I \mod p^k$ e $\pi(p^k) | p^{k-1}\pi(p)$. 

> Teorema 3: Para todo primo $p \neq 2, 5$, $\pi(p)$ divide $p^2 - 1$

Seja $\phi$ uma raiz do polinômio característico da recorrência de Fibonacci, $f(x) = x^2 - x - 1$. Então

$$\phi^n = \phi^{n - 1} + \phi^{n - 2}$$
de onde segue por indução que $\phi^n = F_n \phi + F_{n - 1}$. Assim, sendo $\phi_1 = \frac{1 + \sqrt{5}}{2}$ e $\phi_2 = \frac{1 - \sqrt{5}}{2}$ suas duas raízes, segue que $\phi_1^n - \phi_2^n = (\phi_1 - \phi_2)F_n$ e:

$$F_n = \dfrac{\phi_1^n - \phi_2^n}{\phi_1 - \phi_2}$$

Note que a condição $p \neq 2,5$ é importante para $2$ ser invertível $\mod p$ e não podermos ter $0$ como raiz quadrada de $5$ em $\mathbb{F}_p$.

Portanto, como a menor extensão de $\mathbb{F}_p$ que contém as raízes $\phi_1$ e $\phi_2$ é aquele obtido adicionando $\sqrt{5}$ a $\mathbb{F}_p$, denotado por $\mathbb{F}_p[\sqrt{5}]$. Sabemos pelo [teorema de Lagrange](https://en.wikipedia.org/wiki/Lagrange%27s_theorem_%28group_theory%29) que a ordem de cada elemento do grupo multiplicativo dessa extensão &mdash; incluindo $\phi_1$ e $\phi_2$ &mdash; divide a ordem desse grupo, que vai ser a cardinalidade da extensão, menos $1$, isto é, $|\mathbb{F}_p[\sqrt{5}]| - 1$. Consequentemente, os valores de $F_n$ ciclam a cada $|\mathbb{F}_p[\sqrt{5}]| - 1$ iterações, e $\pi(p) | (|\mathbb{F}_p[\sqrt{5}]| - 1)$. Temos então dois casos:

* Já existe uma raiz quadrada de $5$ em $\mathbb{F}_p$, isto é, $5$ é resíduo quadrático $\mod p$. Nesse caso, $\mathbb{F}_p[\sqrt{5}] = F_p$ e portanto $\pi(p) | (p - 1)$.
* Não existe uma raiz quadrada de $5$ em $\mathbb{F}_p$, e dessa forma cada par $a + b\sqrt{5}$ com $ 0 \leq a,b < p$ é um elemento distinto da extensão, que tem cardinalidade $p^2$. Logo, $\pi(p) | (p^2 - 1)$.

Isso já prova o teorema.

> Extra: não é necessário para resolver a questão, mais temos que
> Pelo [teorema da reciprocidade quadrática](https://en.wikipedia.org/wiki/Quadratic_reciprocity), temos que
> $$\left(\dfrac{5}{p}\right) = \left(\dfrac{5}{p}\right)$$
> (essa notação é para [símbolos de Legendre](https://en.wikipedia.org/wiki/Legendre_symbol)), e os únicos resíduos quadráticos mod $5$ são $1$ e $4$. Assim, para todo primo $p \neq 2, 5$:
>
> * Se $p \equiv 1, 4 \mod 5$, então $\pi(p) | (p - 1)$
>
> * Se $p \equiv 2, 3 \mod 5$, então $\pi(p) | (p^2 - 1)$. Porém, segundo [essa seção do artigo da Wikipedia sobre "Pisano Periods"](https://en.wikipedia.org/wiki/Pisano_period#Pisano_periods_of_prime_numbers), vale o resultado mais forte que $\pi(p) | 2(p+1)$ nesse caso.

Assim, sabemos que $(p^2 - 1)p^{k-1} \leq p^{2k}$ é um múltiplo do período mod $p^k$ se $p \neq 2, 5$, e $\pi(2) = 3$ e $\pi(5) = 20$, assim a partir do teorema 1 podemos utilizar o LCM para calcular um $K$ múltiplo do período $\pi(M)$ com $K = O(M^2) \leq 10^{18}$, de forma que podemos utilizar o fato de que $F_{a^b} \equiv F_{a^b \mod K} \mod M$.

Assim, a complexidade final é $O(\sqrt{M})$ para a fatoração e $O(\log K + \log M) = O(\log M)$ para a exponenciação binária de $a^b \mod K$ e $Q^{a^b \mod K} \mod M$, totalizando $O(\sqrt{M} + \log M)$.

Note que, como $K = O(M^2)$, ao utilizá-lo como mod na exponenciação binária $a^b \mod K$, pode ocorrer overflow em `long long`, e dessa forma é necessário utilizar inteiros de 128-bits (é possível via o tipo `__int128_t` no compilador C++20 (GCC 13-64) do Codeforces).

Code:

```c++
#include <bits/stdc++.h>
using namespace std;
 
#define i64 int64_t

// factor a single number in O(sqrt(x))
// return list of pairs (p, p^vp(x))
vector<pair<i64, i64>> factor(i64 x){
    vector<pair<i64, i64>> f;
    for (i64 p = 2; p * p <= x; p++){
        if (x % p == 0){
            i64 pk = 1;
            while (x % p == 0){
                pk *= p;
                x /= p;
            }
            f.emplace_back(p, pk);
        }
    }
    if (x > 1) {  // what remains is a prime
        f.emplace_back(x, x);
    }
    return f;
}

i64 period(const vector<pair<i64, i64>> factorization){
    i64 q = 1;
    for (auto[p, pk]: factorization){
        i64 period_pk;
        if (p == 2){
            period_pk = (pk / 2) * 3;
        } else if (p == 5){
            period_pk = (pk / 5) * 20;
        } else {
            period_pk = (pk / p) * (p * p - 1);
        }
        q = (q / __gcd(q, period_pk)) * period_pk;  // safe lcm (should not overflow long long)
    }
    return q;
}

i64 bexp_period(i64 a, i64 p, i64 period){
    // if b = 2^i1 + ... + 2^ik
    // then we keep squaring 
    // and multiply the base number when we get to some active bit
    __int128_t res = 1;
    __int128_t power = a;
    for (i64 i = 0; i < 32; i++, power = (power * power) % (__int128_t)period){
        if (p & (1ll << i)){
            res = (res * power) % (__int128_t)period;          
        }
    }
    return res;
}

vector<vector<i64>> matmul(
    const vector<vector<i64>>& A, const vector<vector<i64>>& B,
    i64 mod
){
    vector<vector<i64>> C(2, vector<i64>(2));
    for (i64 i = 0; i < 2; i++){
        for (i64 j = 0; j < 2; j++){
            C[i][j] = 0;
            for (i64 k = 0; k < 2; k++){
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}

vector<vector<i64>> mat_bexp(vector<vector<i64>> A, i64 p, i64 mod){
    vector<vector<i64>> Id(2, vector<i64>(2, 0));
    Id[0][0] = Id[1][1] = 1;
    vector<vector<i64>> B = A;
    vector<vector<i64>> C = Id;
    // period might be up to 10^18 <= 2^60
    for (i64 i = 0; i < 63; i++, B = matmul(B, B, mod)){
        if (p & (1ll << i)){
            C = matmul(C, B, mod);
        }
    }
    return C;
}

signed main(){
    i64 a, b, M;
    cin >> a >> b >> M;

    // F^k = ((f[k + 1], f[k]), (f[k], f[k - 1]))
    vector<vector<i64>> F(2, vector<i64>(2, 0));
    F[0][0] = F[0][1] = F[1][0] = 1;
    i64 period_multiple = period(factor(M));
    i64 exp = bexp_period(a, b, period_multiple);
    vector<vector<i64>> Fpow = mat_bexp(F, exp, M);

    cout << Fpow[0][1] << endl;
}
```

# Outras referências

* [Editorial](https://codeforces.com/blog/entry/143004)
# Solução

Para cada $s$ string binária de tamanho $n$, seja $f_s$ o polinômio que calcula a probabilidade de que $s$ apareça
após jogar $n$ moedas com probabilidade $p$ de aparecer um número $1$, em sequência. Então $f_s(p) = p^k(1-p)^{n-k}$ se $s$ possui
$k$ dígitos iguais a $1$, e queremos encontrar dois conjuntos disjuntos $A, B$ de strings binárias de tamanho $n$ com 

$$\sum_{a \in A}f_a(p) = \sum_{b \in B}f_b(p)$$

(em que a igualdade é de polinômios: ocorre para todo $p \in [0, 1]$), e de forma a minimizar a quantidade de strings fora de $A \cup B$. Assim, sendo $a_k$ a quantidade de strings em $A$ de tamanho $k$, e $b_k$ definido analogamente, queremos que

$$\sum_{k=0}^{n}a_k p^k(1-p)^{n-k} = \sum_{k=0}^{n}b_k p^k(1-p)^{n-k}$$

e de forma a minimizar $\sum_{k = 0}^{n}\left(\binom{n}{k} - a_k - b_k\right)$, a quantidade de strings que ficaram de fora.

> Teorema 1: o conjunto $\{q_k(x) = x^k(1-x)^{n-k}:\ 0 \leq k \leq n\}$ é uma base vetorial do espaço de polinômios de grau menor ou igual a $n$.

Prova: 

Suponha que os coeficientes $\alpha_0, \dotsc, \alpha_n$ são tais que $\sum_{k=0}^{n} \alpha_k x^k (1-x)^{n-k} = 0$. Então:

$$
    \begin{align*}
    \sum_{i=0}^{n} \alpha_i x^i (1-x)^{n-i}
    &= \sum_{i = 0}^{n}\alpha_i x^i \sum_{j=0}^{n - i}\binom{n - i}{j}(-1)^j x^j
    \\
    &\overset{k = i + j}{=} \sum_{k = 0}^{n}x^k\left(\sum_{i = 0}^{k}\alpha_i \cdot \binom{n - i}{k - i}(-1)^{k-i}\right)
    \end{align*}
$$

e portanto, como $\{1, x, \dotsc, x^n\}$ é a base canônica do espaço de polinômios, temos que $\sum_{i = 0}^{k}\alpha_i \cdot \binom{n - i}{k - i}(-1)^{k-i}$ para todo $0 \leq k \leq n$. Portanto, temos um sistema de $n + 1$ equações e $n + 1$ variáveis $\mathbf{M} \mathbf{\alpha} = \mathbf{0}$, em que a $k$-ésima linha (com $k=0\dotsc n$) é o vetor $\begin{bmatrix} (-1)^{k}\binom{n}{k} & (-1)^{k - 1}\binom{n - 1}{k - 1} & \dotsc & (-1)^{0} \binom{n-k}{0} & 0 & \dotsc & 0\end{bmatrix}^T$, e portanto $M$ é uma matrix triangular inferior com determinante

$$\det M = \prod_{k=0}^{n}\binom{n - k}{0} = 1 \neq 0$$

e dessa forma existe apenas a solução trivial $\mathbf{\alpha} = \mathbf{0}$, de onde segue que esse conjunto é L.I e, devido a seu tamanho, é base desse espaço.

$$\tag*{$\blacksquare$}$$

Dessa forma, com esse teorema segue que esse conjunto de polinômios é L.I, e dessa forma é necessário que $a_k = b_k$ para todo $k$, e a resposta mínima é

$$T = \sum_{k = 0}^{n}\left(\binom{n}{k} - 2 \left\lfloor \frac{\binom{n}{k}}{2} \right\rfloor\right) = \sum_{k = 0}^{n}\left(\binom{n}{k} \mod 2\right)$$

> Teorema 2: essa soma dos restos mod $2$ dos coeficientes binomiais acima é igual a $2^{b(n)}$, em que $b(n)$ é a quantidade de bits ativos na representação binária de $n$

Prova:

Pela fórmula de Legendre, temos que

$$
v_2\left(\binom{n}{k}\right) = v_2(n!) - v_2(k!) - v_2((n-k)!) = \sum_{p \geq 1}\left(
    \left\lfloor \frac{n}{2^p} \right\rfloor
    - \left\lfloor \frac{k}{2^p} \right\rfloor 
    - \left\lfloor \frac{n - k}{2^p} \right\rfloor 
\right)
$$

Se $n = q2^p + r$ e $k = q'2^p + r'$ então $\left\lfloor \frac{n}{2^p} \right\rfloor = q$, $\left\lfloor \frac{k}{2^p} \right\rfloor = q'$, e

$$
\left\lfloor \frac{n - k}{2^p} \right\rfloor = \begin{cases}
q - q' \text{ se } r' \leq r \\
q - q' - 1 \text{ do contrário }
\end{cases}
$$

Como $\binom{n}{k}$ é ímpar se e somente se $v_2\left(\binom{n}{k}\right) = 0$, então isso acontece para todo $k$ tal que $k \mod 2^p \leq n \mod 2^p$ para todo $p$.

Isso significa que, olhando da direita para a esquerda, a representação binária de $k$ é, **bit a bit**, menor ou igual à representação binária de $n$. Dessa forma, o $i$-ésimo bit de $k$ é $0$ quando o $i$-ésimo bit de $n$ também é $0$, ou é livre se o $i$-ésimo bit de $n$ está ativo. Dessa forma, temos $2^{b(n)}$ opções para $k \in \{0, 1, \dotsc, n\}$ tais que $\binom{n}{k}$ seja ímpar.

$$\tag*{$\blacksquare$}$$

> Isso é um caso especial do teorema de Lucas, que diz que $\binom{n}{m} \equiv \prod \binom{n_i}{m_i} \mod p$, em que $n_i$ é o $i$-ésimo dígito na representação de $n$ na base $p$, e $m_i$ o $i$-ésimo dígito na representação de $m$ na base $p$. Assim, $\binom{n}{k} \equiv 1 \mod 2$ se e só se $\binom{n_i}{k_i} \not\equiv 0 \mod p$, em que $n_i, k_i \in \{0, 1\}$ é o $i$-ésimo bit de $n$ e $k$ respectivamente. Assim, isso ocorre se e só se $k_i \leq n_i$ para todo $i$, e portanto há $2^{b(n)}$ opções de valores de $k$.

## Implementação:

Note o uso de `__builtin_popcountll` em vez de `__builtin_popcount`, uma vez que essa última só funciona com inteiros de 32 bits, e
a primeira funciona com `long long`, que garantidamente possui 64 bits independente da plataforma.

```c++
#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n;
    cin >> n;
    cout << (1ll << __builtin_popcountll(n)) << endl;
}
```

#strings 
## Link:

https://cp-algorithms.com/string/prefix-function.html#compressing-a-string

## Definição

>[!min-period-def] Definição (periodicidade de uma string)
> A periodicidade de uma string $s$ de tamanho $n$ é o **menor** $1 \leq p \leq n$ **divisor de $n$**  tal que existe uma string $t$ de tamanho $p$ com
> $$s = t^{\frac{n}{p}}$$
> Ou seja, é a menor parte que se repete para formar a string. **Paralelamente, é a melhor compressão que conseguimos fazer da string, representando-a por um par $(t, \frac{n}{p})$

## Encontrando a periodicidade de uma string


> [!period-kmp-theorem] Relação com KMP
> Seja $s$ uma string de tamanho $n$ e $\pi$ a função prefixo do algoritmo do KMP, computada sobre $s$. 
> Caso $(n - \pi_n) \mid n$, então a periodicidade é $n - \pi_n$, do contrário é $n$.
> (usando índices 1-indexados) 

### Prova:

#### 1. Se $n - \pi_n \mid n$ então a periodicidade é $n - \pi_n$ 

Suponha que $n = q \cdot (n - \pi_n)$ para algum inteiro $q$. Isto é, $q = \frac{n}{n - \pi_n}$. Vamos mostrar que $\frac{n}{q}$ é o período de $s$

Essa divisibilidade implica que $\pi_n = \dfrac{q - 1}{q} \cdot n$. Como $gcd(q-1, q) = 1$, então $q | n$, e então a string comum (_base_) $b = s[1..\pi_n] = s[n - \pi_n + 1..n]$  de tamanho $\pi_n$ é composta de $q - 1$ partes de tamanho $\frac{n}{q}$ , $b = u_1 \dotsc u_{q - 1}$. Sejam $c, d$ as string que faltam para completar $s$, isto é, definidas de forma que 

$$s = bc = db$$
Então $|c| = |d| = n - \pi_n = \frac{n}{q} = |u_i|$  para todo $1 \leq i \leq q - 1$. Logo temos $q$ blocos de tamanho $\frac{n}{q}$, e podemos comparar as duas representações da mesma string bloco a bloco:

$$s = d u_1 u_2 \dotsc u_{q-1} = u_1u_2\dotsc u_{q - 1}c$$
e portanto $d = u_1,\ u_1 = u_2, \dotsc, u_{q - 2} = u_{q - 1},\ u_{q - 1} = c$. Assim todos os blocos são iguais a uma certa string $t$ e $s = t^{q} = t^{\frac{n}{n - \pi_n}}$ .

Para mostrar a minimalidade de $n - \pi_n$, suponha então que existe $p < n - \pi_n$ e uma string $t$ de tamanho $p$ com $s = t^{\frac{n}{p}}$ . Então $s = t^{\frac{n}{p}} = t^{\frac{n}{p} - 1}t = tt^{\frac{n}{p} - 1}$ e portanto (**lembrando que por definição $\pi_n < n$**)
$$\pi_n \geq |t^{\frac{n}{p} - 1}| =  p \cdot (\frac{n}{p} - 1) = n - p > \pi_n$$ 
contradição! Logo $n - \pi_n$ é o período mínimo.

#### 2. Se $n - \pi_n \nmid n$ não existe compressão e o período é apenas $n$

Suponha que o período não é apenas $n$, isto é, $s = t^{q}$ com $|t| = p$ e $q > 1$. Então

$s = t^{q-1}t = tt^{q - 1}$

e logo $\pi_n \geq (q-1)p$ . Suponha que $\pi_n = (q-1)p + d$ com $0 \leq d < p$. Então

$$s[1..(q-1)p+d] = s[n-(q-1)p-d+1..n]$$
o que significa que temos um desalinhamento nos blocos, e como $q > 1$ (existe mais de uma repetição de $t$):

$$
\begin{align*}
	(s[1] = t[1]) &= (s[n - (q-1)p - (d - 1)] = t[p-d]) \\
	(s[2] = t[2]) &= (s[n - (q-1)p - (d - 2)] = t[p-(d - 1)]) \\
	\dotsc \\
\end{align*}
$$

ou seja, analisando as duas primeiras repetições de $t$ no prefixo com o sufixo correspondente temos:

$$
\begin{align*}
	&t[1] = t[p - d + 1] \\
	&t[2] = t[p - d + 2] \\
	&\dotsc \\
	&t[d] = t[p] \\
	&t[d+1] = t[1] \\
	&\dotsc
	&t[p] = t[p - d] \\
\end{align*}
$$

isto é, $t[i] = t[j]$ se $i - j \equiv d \cdot k \mod p$ para algum $k$. Dessa forma, temos "classes de equivalência" de tamanho igual ao gerado por $d$ em $\mathbb{Z}_p$, que é $\frac{p}{\gcd(d, p)}$. Em outras palavras, temos apenas uma sequência $r$ de $gcd(d, p)$ caracteres distintos em $t$, que se repete:

$$t = r^{\frac{p}{\gcd(d, p)}}$$
e portanto 

$$s = r^{q \cdot \frac{p}{\gcd(d, p)}}$$
Pela maximalidade de $q$ (já que $t$ era a menor parte possível que formava um período de $s$) então $\gcd(d, p) = p$ e $d = 0$. Logo

$$\pi_n = (q - 1)p = n - p \implies p = n - \pi_n$$

e em particular $n - \pi_n \mid n$.

Por contrapositiva, segue que se $n - \pi_n \nmid n$ então o período mínimo é simplesmente $n$.
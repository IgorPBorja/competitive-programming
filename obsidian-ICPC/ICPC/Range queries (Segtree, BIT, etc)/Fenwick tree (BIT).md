

> [!idea-1] Ideia principal:
> O **bit menos significativo** do número representa o tamanho do intervalo a que ele se refere

Ou seja, dado um array $A[1 \dotsc n]$ montamos um array $B[0 \dotsc n]$ com

$$B[i] = \sum_{j=i - 2^\operatorname{lsb}(i) + 1}^{i}A[j]$$

com
$$\operatorname{lsb}(i) = \min \left\{j \geq 0: \frac{i}{2^j} \equiv 1 \mod 2\right\}$$
## Propriedade importante


> [!lemma1] Em sistemas de $B$ bits de complemento de dois, para todo $0 \leq x < 2^{B - 1}$
> $$x \operatorname{AND} (-x) = 2^{\operatorname{lsb}(x)}$$

Prova: seja $i = \operatorname{lsb}(x)$: então temos que
$$x = \overline{b_B\dotsc b_{i+1}10\dotsc 0} = \sum_{B \geq j > i}b_j 2^j + 2^i$$
e portanto, como o complemento de dois consiste em realizar o complemento de 1 e então somar 1, a representação de $-x$ é igual a
$$-x \equiv_{(\mod 2^B)} 2^{B} - x = (2^{B} - 1 - x) + 1 = \left(\sum_{B \geq j > i}(1 - b_j)2^j\right) + 0 + \sum_{i - 1 \geq j \geq 0}2^i + 1 = \left(\sum_{B \geq j > i}(1 - b_j)2^j\right) + 2^i$$
e portanto
$$x \operatorname{AND} -x = \sum_{B \geq j > i}b_j \cdot (1-b_j) 2^j + 2^i = 2^i = 2^{\operatorname{lsb}(x)}$$

## Construção da BIT

* Começamos com uma BIT nula e realizamos $n$ updates
* Complexidade: $O(n \log n)$ (conforme [[Fenwick tree (BIT)#^thm3-update-complexity]])

```cpp
vector<int> BIT(const vector<int> &a){
	int n = a.size();
	vector<int> B(n + 1, 0);

	for (int i = 0; i < n; i++){
		bit_update(B, i, a[i]);  // sum a[i] to position i+1 of the BIT
	}
	return B;
}
```
## Queries


> [!thm1] Para todo $1 \leq i \leq n$ defina $S[i] = \sum_{1 \leq j \leq i}A[j]$. Então
> $$S[i] = B[i] + S[i - 2^{\operatorname{lsb}(i)}] = B[i] + S[i \operatorname{XOR} 2^{\operatorname{lsb(i)}}]$$

Prova: basta notar que
$$B[i] = \sum_{j = i + 2^{\operatorname{lsb}(i)} + 1}^{i}A[j]$$
por definição, e logo a primeira igualdade segue.
Quanto à segunda igualdade, note que se $\operatorname{lsb}(i) = j$, então esse $j$-ésimo bit de $i$ está ativo, e portanto subtrair $2^{\operatorname{lsb}(i)}$ é equivalente a simplesmente desligar esse bit, o que pode ser feito com o XOR. 
$$\tag*{$\blacksquare$}$$

Portanto temos o seguinte algoritmo de queries:
```c++
int get(const vector<int> &BIT, int i){
	int s = 0;
	while (i > 0){
		s += BIT[i];
		// i & -i == 2^lsb(i)
		i = i ^ (i & (-i));
	}
	return s;
}
```

> [!thm2] O algoritmo de queries acima opera em $O(\log n)$

Prova: a cada passo do loop do algoritmo acima desligamos o menor bit ativo do índice atual, e portanto essa operação só pode ser executada um número de vezes menor ou igual ao tamanho, em bits, do número - portanto $O(\log n)$.

## Update

Algoritmo para query de update: **somar $x$ a posição $i$.

```cpp
inline int lsb(int i){
	// implement LSB
}

// sum x to position i (position 0-indexed)
void update(int i, int x, const vector<int> &BIT){
	const int n = BIT.size() - 1;
	++i; // correct to BIT's 1-indexation
	while (i <= n){
		BIT[i] += x;
		i += (1ll << lsb(i));
	}
}
```


* Implementação mais rápida:
```cpp
void update(int i, int x, const vector<int> &BIT){
	const int n = BIT.size() - 1;
	while (i <= n){
		BIT[i] += x;
		i += i & (-i);
	}
}
```



> [!thm3] O algoritmo acima executa em $O(\log n)$
> 
> ^thm3-update-complexity


Prova: basta perceber que $\operatorname{lsb}(i + 2^{\operatorname{lsb}(i)}) > \operatorname{lsb}(i)$ (pois ao somar esse valor cancelamos a sequência mais à direita de bits ativos na representação binária de $i$), e portanto, como obtemos uma sequência estritamente crescente em que todos os elementos são no máximo $O(\log n)$, ela necessariamente tem que ter tamanho $O(\log n)$.


> [!thm4] O algoritmo de update acima está correto.

Prova: seja $1 \leq p \leq n$ o índice que queremos realizar o update.

Então $a[p]$ participa da soma representada por $BIT[i]$ se e somente se
$$i - 2^{\operatorname{lsb}(i)} + 1 \leq p \leq i$$
Portanto, se $p = \overline{b_Bb_{B - 1}\dotsc b_0} = b_B 2^B + b_{B - 1} 2^{B - 1} + \dotsc b_0$ em um sistema de representação binária de $B$ bits, temos os seguintes casos:
1. $i = \overline{b_B\dotsc b_{k + 1}1\dotsc 0}$ de tal forma que também tenhamos $b_{k} = 1$ e $b_{j} = 0$ para $j < k$. Isso só ocorre quando $i = p$.
2. $i = \overline{b_B\dotsc b_{k + 1}10\dotsc 0}$ com $b_{k} = 0$ e $\{b_{k - 1}, \dotsc, b_0\}$ não são todos $0$. Essa segunda condição basicamente significa que não temos $i = p + 2^{k}$ para algum $k < \operatorname{lsb}(p)$.

Note que a segunda condição do caso 2 é, na verdade, irrelevante, uma vez que no nosso loop, somando $2^{\operatorname{lsb}(i)}$ a $i$, e partindo nunca é possível alcançar $p + 2^k$ para algum $k < \operatorname{lsb}(p)$, uma vez que já no primeiro update de $i$ ultrapassamos esses valores.

Afirmamos: 

> [!claim3.1] Afirmação 1:
> Sejam $\operatorname{lsb}(p) < n_1 < \dotsc < n_k \leq B$ os índices dos bits nulos de $p$, e ponha $n_0 := \operatorname{lsb(p)}$ por consistência.
> 
> Então, para todo $0 \leq j \leq k$, após a $j$-ésima iteração do loop, $i = \overline{b_B\dotsc b_{n_j + 1}10\dotsc 0}$.

Prova: provamos por indução.
O caso base segue pelo fato de que $\overline{b_B\dotsc b_{\operatorname{lsb}(p) + 1}10\dotsc 0}$ é simplesmente $p$, que é o estado inicial de $i$.

Para caso base $j = 1$, temos que $i = p = \overline{b_B\dotsc b_{n_1 + 1}01\dotsc 10\dotsc 0}$ em que depois de $b_{n_1}=0$ ocorrem $n_1 - \operatorname{lsb}(p)$ bits iguais a $1$ e $\operatorname{lsb(p)}$ bits iguais a $0$. Dessa forma, após a primeira iteração do loop temos 


Suponha então que após a $j$-ésima iteração do loop (com $1 \leq j < k$) temos que $i = \overline{b_B \dotsc b_{n_j + 1}10\dotsc 0}$. Então segue que
$$i = \overline{b_B\dotsc b_{n_{j + 1} + 1}01\dotsc 10\dotsc 0}$$
em que depois de $b_{n_{j + 1}} = 0$ temos $b_{n_{j  + 1}} - b_{n _j}$ bits $1$ e $b_{n_j}$ bits $0$, e consequentemente
$$\operatorname{lsb}(i) = n_j$$

Portanto, após completarmos a $(j + 1)$-ésima iteração temos
$$
\begin{align*}
	i \gets i + 2^{\operatorname{lsb}(i)}
	&= \sum_{B \geq \ell > n_{j + 1}}b_\ell 2^\ell + \sum_{n_{j + 1} - 1 \geq \ell \geq n_j}2^\ell + 2^{n_j}
	\\
	&= \sum_{B \geq \ell > n_{j + 1}}b_\ell 2^\ell + 2^{n_j}\left(\sum_{n_{j + 1} - 1 - n_j \geq \ell \geq 0}2^\ell + 1\right)
	= \sum_{B \geq \ell > n_{j + 1}}b_\ell 2^\ell + 2^{n_{j + 1}}
	\\
	&= \overline{b_B\dotsc b_{n_1 + 1}10\dotsc 0} 
\end{align*}
$$
provando a afirmação por indução.
$$\tag*{$\blacksquare$}$$
Devido à essa afirmação, segue que esse loop itera exatamente sobre todos aqueles índices $i \leq n$ que satisfazem o caso 1 e 2 acima, provando que o algoritmo de update `update(p, x)` soma $x$ a exatamente todas as posições $1 \leq i \leq n$ das quais $p$ faz parte da soma, isto é, $i - 2^{\operatorname{lsb}(i)} + 1 \leq p \leq i$.
$$\tag*{$\blacksquare$}$$
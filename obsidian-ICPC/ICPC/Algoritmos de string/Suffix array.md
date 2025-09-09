#strings


> [!NOTE] Suffix array - definição
> O suffix array é o array de sufixos da string, ordenada em ordem lexicográfica crescente.
>
> Para ocupar apenas $O(N)$ de memória, são armazenados apenas os índices de início de cada sufixo.

## Passos

#### 1. Acrescentamos um símbolo '$' ao final da string, menor que todos os outros caracteres da string e que não aparece nela!

#### 2. Construímos a matriz de classes de equivalência

Para cada $k=0\dotsc \log N$  denotamos por $A[k][i]$ a **classe de equivalência** das substrings $s[i\dotsc \min(i+2^k, n) - 1]$ (considerando 0-indexado). Ou seja, se essa classe de equivalência é $j$, então a substring de tamanho $2^k$ começando em $i$ é a $j$-ésimo **menor** substring de tamanho $2^k$ que existe dentro de $s$.

Dessa forma, dado $2^k \geq n$, temos que todos as substrings de tamanho $2^k$ chegam ao caractere especial '$', em momentos/índices diferentes, e portanto todas terão classes de equivalência distintas. **Essas classes de equivalência, ou seja, a última linha $A[n][\dotsc]$ da matriz, é o índice de cada sufixo no vetor ordenado de sufixos**.


> [!tip] Para simplificar, podemos considerar a string como cíclica! Assim, não precisamos lidar com $\min$, e podemos apenas pensar nos blocos $s[i\dotsc (i+2^k) \mod n]$


Ou seja, o índice do $j$-ésimo menor sufixo é aquele $i$ tal que $A[n][i] = j$, e o suffix array é a permutação inversa.

Podemos comparar duas substrings de tamanho $2^{k + 1}$ começando em $i$ e $j$ da seguinte forma: 

* Se $A[k][i] < A[k][j]$ ou ($A[k][i] = A[k][j]$ e $A[k][\min(i + 2^k, n)] < A[k][\min(j + 2^k, n)]$ , então a substring em $i$ é menor que a substring em $j$.

Assim, em cada step $k > 0$, podemos começar com o vetor $[0, 1, \dotsc, n-1]$, ordená-los de acordo com o nível $k$, e a posição de $i$ no novo vetor ordenado (**desconsiderando repetições**) será sua nova posição.

Para obter a posição desconsiderando repetições (isto é, a classe de equivalência), podemos começar com um contador `cur_class = 0` e incrementar ele à medida que vermos uma transição que de fato aumenta o valor do par `(classe da primeira metade, classe da segunda metade)`.

```c++
vector<vector<int>> suffix_array(string s){
	s.push_back('$');
	const int n = s.size();
	int ceilLogN = 0;
	while ((1ll << ceilLogN) < n) ++ceilLogN;  // guarantees 2^ceilLogN >= n
	vector<vector<int>> c(ceilLogN + 1);
	for (int i = 0; i <= ceilLogN; i++) c[i].resize(n);
	for (int i = 0; i < n; i++){
		c[0][i] = s[i] - '$';  // uses own ascii code as starting equivalence class
	}
	auto get_pair = [&c, n](int i, int k){
		return make_pair(c[k - 1][i], c[k - 1][(i + (1ll << (k - 1))) % n]);
	};
 
	for (int k = 1; k <= ceilLogN; k++){
		// THIS IS WHERE SORTING HAPPENS
		auto comp = [k, &get_pair](int i, int j){
			pair<int, int> l = get_pair(i, k), r = get_pair(j, k);
			return l < r;
		};
		vector<int> v(n);
		iota(v.begin(), v.end(), 0);
		sort(v.begin(), v.end(), comp);
		
		int cur_class = 0;
		c[k][v[0]] = 0;
		for (int i = 1; i < n; i++){
			if (get_pair(v[i], k) > get_pair(v[i - 1], k)) ++cur_class;
			c[k][v[i]] = cur_class;
		}
	}
	return c;  // last row are final equivalence classes
}
```

Para obter o array de índices dos sufixos em ordem lexicográfica, basta inverter a permutação que é a última linha `c.back()`:

```c++
auto c = suffix_array(s);
const int n = s.size();
vector<int> sorted_suffixes(n + 1);
for (int i = 0; i <= n; i++){
	int cls = c.back()[i];
	sorted_suffixes[cls] = i;
}
```


> [!tip] Complexidade final: $\Theta(N \log^2 N)$
São $\lceil \log N \rceil$ etapas que envolvem uma ordenação, em $\Theta(N \log N)$, e pós-processamento em $\Theta(N)$


## Otimizando suffix array com radix/counting sort

Podemos **otimizar a etapa de ordenação utilizando radix/counting sort**.

Para isso, realizamos duas etapas para um dado $k$:

* Ordenamos via counting sort conforme o valor da classe de equivalência da segunda metade, $A[k - 1][i + 2^{k-1}]$
* Ordenamos **de forma estável** conforme o valor da classe de equivalência da primeira metade, $A[k - 1][i]$

Dessa forma, como a ordenação é estável, o vetor final estará ordenado pela primeira metade, de tamanho $2^{k - 1}$, e **como critério de desempate, pela segunda metade**, fruto da primeira etapa de ordenação.

Para isso, podemos implementar a seguinte função utilizando a ideia de **bucket**

```c++
void bucket_sort_with_offset(vector<int>& p, const vector<int>& cls_map, int offset){
	const int n = cls_map.size();
	vector<vector<int>> buckets(max(n, 256));  // 256 = alphabet size (ASCII), for the first case
	for (int i = 0; i < n; i++){  // since we iterate in order of i, this is stable
		int cls = cls_map[(p[i] + offset) % n];
		buckets[cls].emplace_back(p[i]);
	}
	int i = 0;
	for (int cls = 0; cls < max(n, 256); cls++){
		for (int x: buckets[cls]) p[i++] = x;	
	}
}
```

e a etapa de ordenação se torna:

```c++
vector<int> v(n);
iota(v.begin(), v.end(), 0);
bucket_sort_with_offset(v, c[k - 1], (1ll << (k - 1)));
bucket_sort_with_offset(v, c[k - 1], 0);
```

Para **evitar o overhead de `vector<vector<int>>` e vários `emplace_back`s, podemos fazer prefix sums para obter a final inicial de cada classe**!

```c++
void bucket_sort_with_offset(vector<int>& p, const vector<int>& cls_map, int offset){
	const int n = cls_map.size();
	vector<int> last_bucket_pos(max(n, 256), 0);
	for (int i = 0; i < n; i++){
		int cls = cls_map[(p[i] + offset) % n];
		++last_bucket_pos[cls];
	}
	for (int i = 1; i < max(n, 256); i++) last_bucket_pos[i] += last_bucket_pos[i - 1];
	
	const auto orig = p;
	for (int i = n - 1; i >= 0; i--){
		// since we iterate in order of i here, we put elements right to left
		// from last bucket position, this is stable
		int cls = cls_map[(orig[i] + offset) % n];
		p[--last_bucket_pos[cls]] = orig[i];  // --pos instead of pos-- !!!
	}
}
```


> [!tip] Essa implementação sem o overhead de inserir no vetor pode ser até 4x mais rápida com $N = 10^5$
> (Testado em [Codeforces EDU - Suffix Array - Step 1 - A. Suffix Array - 1](https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/problem/A))


## Implementação final

```c++
void bucket_sort_with_offset(vector<int>& p, const vector<int>& cls_map, int offset){
	const int n = cls_map.size();
	vector<int> last_bucket_pos(max(n, 256), 0);
	for (int i = 0; i < n; i++){
		int cls = cls_map[(p[i] + offset) % n];
		++last_bucket_pos[cls];
	}
	for (int i = 1; i < max(n, 256); i++) last_bucket_pos[i] += last_bucket_pos[i - 1];
	
	const auto orig = p;
	for (int i = n - 1; i >= 0; i--){
		// since we iterate in order of i here, we put elements right to left
		// from last bucket position, this is stable
		int cls = cls_map[(orig[i] + offset) % n];
		p[--last_bucket_pos[cls]] = orig[i];  // --pos instead of pos-- !!!
	}
}

pair<vector<int>, vector<vector<int>>> suffix_array(string s){
	s.push_back('$');
	const int n = s.size();
	int ceilLogN = 0;
	while ((1ll << ceilLogN) < n) ++ceilLogN;  // guarantees 2^ceilLogN >= n
	vector<vector<int>> c(ceilLogN + 1);
	for (int i = 0; i <= ceilLogN; i++) c[i].resize(n);
	for (int i = 0; i < n; i++){
		c[0][i] = s[i] - '$';  // uses own ascii code as starting equivalence class
	}
	auto get_pair = [&c, n](int i, int k){
		return make_pair(c[k - 1][i], c[k - 1][(i + (1ll << (k - 1))) % n]);
	};
 
	vector<int> p(n);
	iota(p.begin(), p.end(), 0);
		
	for (int k = 1; k <= ceilLogN; k++){
		// THIS IS WHERE SORTING HAPPENS
		bucket_sort_with_offset(p, c[k - 1], (1ll << (k - 1)));
		bucket_sort_with_offset(p, c[k - 1], 0);
		
		int cur_class = 0;
		c[k][p[0]] = 0;
		for (int i = 1; i < n; i++){
			if (get_pair(p[i], k) > get_pair(p[i - 1], k)) ++cur_class;
			c[k][p[i]] = cur_class;
		}
	}
	return {p, c}; 
	// p is the suffix array itself
	// c[k] are the equivalence classes of substrings of size 2^k
	// c.back() are the final equivalence classes
}
```

# LCP

Podemos descobrir o **maior prefixo em comum entre $s[i...]$ e $s[j...]$ em $O(\log N)$ utilizando as classes de equivalência!**

Procedemos gulosamente conforme o seguinte pseudocódigo:

```python
function lcp(i, j, classes):
	lcp = 0
	if (i == j) return n - i;
	for k=2^ceil(log(n))...0:
		if classes[k][i] == classes[k][j]:
			i = (i + 2^k) % n;
			j = (j + 2^k) % n;
	return lcp;
```


> [!tip] Não precisamos nos preocupar de, ao somar $2^k$, andarmos ciclicamente pela string ao tirar o mod. O resultado do LCP ainda estará correto.
> Como temos o caractere final, menor que todos os outros, é garantido que vamos dar no máximo $n - \max(i, j)$ saltos para $i \neq j$, pois o prefixo que começa em $\max(i, j)$  encontrará o caractere sentinela '\$' estritamente antes do outro em qualquer soma de offset que excedesse $n$.

## LCP Array

> [!info] LCP Array - Definição
> O array de LCP é o array que contém o LCP entre **sufixos adjacentes na ordem lexicográfica**

Ou seja, se $SA$ é o suffix array, então o LCP-Array é

$$A_{LCP}[i] := LCP(SA[i], SA[i+1])$$


Defina por $rank$ a permutação inversa do suffix-array, de forma que $rank[i] =$ posição do sufixo iniciado em $i$ na ordem lexicográfica. Então temos o seguinte teorema:

Temos o seguinte teorema:

> Teorema: (LCP sobre ranges) Seja $i < j$. Então o LCP entre os sufixos $i$ e $j$ na ordem lexicográfica é:
> $$LCP(SA[i], SA[j]) = \min_{i \leq k < j}A_{LCP}[k]$$
> Em particular, o LCP entre os sufixos $i$ e $j$ na ordem da string é:
> $$LCP(i, j) = \min_{\min(rank[i], rank[j]) \leq k < \max(rank[i], rank[j])} A_{LCP}[k]$$

Prova: a segunda afirmação segue trivialmente substituindo $i \gets rank[i]$ e $j \gets rank[j]$ na primeira afirmação, uma vez que $SA[rank[i]] = i$ para todo $i$ por definição.

Para a primeira afirmação, podemos proceder por indução em $j - i$, sendo o caso $j - i = 1$ a próprio definição de $A[i]$. Suponha por indução agora que vale sempre que $j - i \leq d$ e considere um caso em que $j - i = d + 1$.

Dessa forma, sabemos que o maior sufixo compartilhado por $s[SA[j]...]$ com alguém menor ou igual a ele é com o sufixo imediatamente anterior na ordem lexicográfica, $s[SA[j-1]...]$: do contrário, se ele compartilhasse com outro índice $SA[k]$, necessariamente deveríamos ter que o sufixo iniciado em $SA[k]$ está entre aquele de $SA[j - 1]$ e o de $SA[j]$ na ordem lexicográfica, contradição, e portanto $j - 1 < k < j$ contradição!

Dessa forma,
$$\begin{align*}
LCP(SA[i], SA[j]) &= \min(LCP(SA[i], SA[j - 1]), LCP(SA[j - 1], SA[j])) \\
&= \min(LCP(SA[i], SA[j - 1]), A[j - 1])
\end{align*}$$
porém por hipótese indutiva $LCP(SA[i], SA[j - 1]) = \min_{i \leq k < j - 1}A[k]$, e o resultado segue.

$$\tag*{$\blacksquare$}$$



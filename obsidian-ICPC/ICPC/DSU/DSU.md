
# Preliminares

* **Nota: consideramos $n$ durante o texto como a soma dos tamanhos de todos os conjuntos**. 

* DSU é uma estrutura de dados que suporta **conjuntos disjuntos** e permite dois tipos de queries:
	- `get(a)`: retorna qual conjunto $a$ pertence
	- `union(a, b)`: une o conjunto que contém $a$ com o conjunto que contém $b$

## Panorama das possíveis soluções

1. Naive:
	- Mantemos um array $p$ com $p[a]$ sendo o id (_leader_) do conjunto em que $a$ está.
	- `get(a)`: retornamos $p[a]$ 
		- Complexidade: $O(1)$
	- `union(a, b)`: simplesmente iteramos sobre todos os elementos e fazemos o update apenas de cada $x$ no mesmo conjunto de $a$ (isto é, que satisfaz $p[x] = p[a]$), pondo $p[x] = p[b]$.
		- Complexidade: $O(n)$

2. Linked List
	- Mantemos um array $p$ com $p[a]$ sendo o id (_leader_) do conjunto em que $a$ está.
	- Mantemos uma lista ligada $l[id]$ para cada _leader_ $id$, com os elementos do conjunto $id$.
	- `get(a)`: retornamos $p[a]$
		- Complexidade: $O(1)$
	- `union(a, b)`: iteramos sobre todos os elementos de $x \in l[p[a]]$ e fazemos o update $p[x] = p[b]$. Depois, juntamos $l[a]$ no final de $l[b]$ em $O(1)$ (simplesmente fazendo o último elemento de $l[b]$ apontar para a head de $l[a]$).
		- Complexidade $O(|l[a]|) = O(n)$ **amortizado**
		- A complexidade é $O(n)$ amortizado pois se tomarmos as uniões sucessivas `union(i, i + 1)` (começando de $n$ conjuntos unitários) temos runtime de $O(1 + 2 + \dotsc n - 1) = O(n^2)$ para $n$ uniões, e portanto se torna $O(n)$ amortizado.
	
3. Linked List + Small-to-Large heuristic
	- `union(a, b)`: mesmo mecanismo do anterior, porém se $|l[a]| > |l[b]|$, fazemos o _swap_ de $a$ e $b$, fazendo sempre o merge do menor sobre o maior.
		- Complexidade: $O(\min(|l[a]|, |l[b]|)) = O(\log n)$ amortizada.
		- A informação de tamanho pode ser mantida e atualizada em $O(1)$
		- A complexidade é $O(\log n)$ amortizada, pois supondo um tamanho inicial de $|l[p[x]]| = 1$ (pior caso), só fazemos o primeiro update de $p[x]$ se o union acontecer com um conjunto de tamanho pelo menos 1 - repetindo esse raciocínio, o update $r$ só ocorre na união com um conjunto de tamanho $2^r$. Como os conjuntos tem tamanhos de no máximo $n$, fazendo um grande número de uniões (o máximo possível é $n - 1$) teremos complexidade $O(n \log n)$, e portanto a complexidade de uma única união é $O(\log n)$ amortizado. 

4. DSU: armazenando elementos em árvores e utilizamos _small to large_
	- Mantemos uma árvore atráves de um array de parents $p$, para cada set. Inicialmente, cada elemento é raiz de sua própria árvore, isto é, $p[a] = a$.
	- `get(a)`: subimos a árvore até a raiz, e retornamos a raiz.
		- Complexidade: $O(\log n)$ (não amortizado)
	- `union(a, b)`: se $size(a) \leq size(b)$, setamos o parent da raiz $r_a$ como $r_b$, e fazemos o update de `size`.
		- Complexidade: $O(get) = O(\log n)$ (não amortizado)

	- O uso de _small-to-large_ garante que não teremos árvores-linha (pois assim a complexidade degeneraria para $O(n)$), e sim árvores aproximadamente balanceadas.

5. DSU com _path compression_ 
	- Fazemos $p[a]$ apontar para a root toda vez que executamos `get(a)` (isto é, comprimimos o caminho de $a$ até a root) - não só isso, fazemos $p[x]$ apontar para a root para todo $x$ no caminho de subida $a \to root$. Isso pode potencialmente fazer o próximo get ser mais rápido.



# Small to large - geral

*  Utiliza a mesma ideia de merge do DSU porém **mantemos as listas contendo os sets**
*  Complexidade: $O(\log N)$ amortizada -  ou seja, $O(N \log N)$ para uma sequência de merges que resulta em um único conjunto.

```c++
struct DSU{
	vector<int> p;
	vector<vector<int>> elements;

	DSU(int n){
		p.resize(n);
		iota(p.begin(), p.end());
		elements.resize(n);
		for (int i = 0; i < n; i++){
			elements[i].emplace_back(i);
		}
	}
	int find(int x){
		if (p[p[x]] != p[x]) p[x] = find(p[x]);
		return p[x];
	}
	
	void merge(int x, int y){
		x = find(x), y = find(y);
		if (x == y) return;
		if (elements[x].size() < elements[y].size()) swap(x, y);
	
		for (int z: elements[y]){
			elements[x].emplace_back(z);
		}
		p[y] = x;
	}
}

```


## Exemplo: 

Link: [CodeforcesEDU - DSU - Step1C. Experience](https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/C)

* Montamos uma DSU mantendo um `lazy` tal que `lazy[find(x)]` é quanto deve ser adicionado a todos os elementos do set que contém `x` .
* No merge, **atualizamos os valores do set menor de acordo com seu lazy** 
	* Entretanto, devemos **subtrair o valor do lazy do set maior, pois esse incremento foi feito antes do merge**  e não deve ser aplicado a essa nova parte mergeada.

```c++
void merge(int x, int y){
	x = find(x), y = find(y);
	if (x == y) return;
	if (elements[x].size() < elements[y].size()) swap(x, y);

	for (int z: elements[y]){
		val[z] += lazy[y];  // commits the pending update
		val[z] -= lazy[x];  // avoids adding lazy[x] which was an update that happened before this z was added to this set
		elements[x].emplace_back(z);
	}
	parent[y] = x;
}

int get(int x){
	return val[find(x)] + lazy[find(x)];
}
```


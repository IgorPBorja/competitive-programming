#strings 
* O objetivo é atribuir valor numérico a strings
* Utilizaremos *polynomial hashing* (rolling hash)

* Dadas **constantes escolhidas A, B**
$$h(S) = s[0]A^{n - 1} + s[1]A^{n - 2} + ... + s[n-1]A^0 \mod B$$

## Propriedades

* Hash de prefixos:
	* Calculamos $h[k] := h(S[0..k])$ 
	* Temos que $$h[k] = s[0]A^{k - 1} + ... s[k-2]A^{1} + s[k-1] \mod B = A(s[0]A^{k-2} + ... + s[k-2]A^0) + s[k-1] \mod B = Ah[k-1] + s[k-1] \mod B$$
	* Logo é possível calcular o array $h$ em $O(n)$
 * Existe possibilidade de colisão
	 * Assumindo que a distribuição de probabilidade dos hashes é uniforme, temos probabilidade de colisão $\frac{1}{B}$
	 * Se $x$ é comparado com $n$ strings, a probabilidade de colisão é $1 - \left(1 - \frac{1}{B}\right)^n$
	 * Se $n$ strings são comparadas par a par, a probabilidade de uma colisão é calculada da seguinte maneira:
		 * Precisamos que as $n$ strings formem um subconjunto ordenado sem repetições, para os quais temos $A(B, n) = \binom{B}{n} \cdot n!$ opções, cada uma com probabilidade $B^{-n}$
		 * Logo a probabilidade de colisão é $1 - \frac{\binom{B}{n} \cdot n!}{B^n}$, o que é muito alto para $B$ pequeno (**Birthday Paradox**)

* É comum **randomizar o módulo B nas soluções**
## Double hashing

* Utilizamos dois mods distintos $B_1, B_2$, ou mesmo mais mods
* Comparamos todos os mods - se um não corresponder, as strings são diferentes
* Probabilidade de colisão é o produto das probabilidades de colisão individuais para cada hash


# Problema 1: ## CCC '20 S3 - Searching for Strings

Link: [CCC'20 S3 - Searching for Strings](https://dmoj.ca/problem/ccc20s3)

### Solução

* Como queremos permutações e não nos importamos com a ordem para qualificar um matching, utilizamos uma **sliding window da tabela de frequência de caracteres** (como o tamanho do alfabeto é 26, a complexidade é $O(26n)$)
* Para cada match das tabelas de frequências, **adicionamos a um set o rolling hash da janela**
* O tamanho do set é a quantidade de permutações distintas que dão match, que é a resposta que buscamos.

### Implementação (TODO)


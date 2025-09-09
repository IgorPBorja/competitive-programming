#strings 
# Algoritmo

* Texto $t$, padrão $s$: queremos conseguir todos os matches entre $s$ e uma substring de $t$.
* Também é possível, com o mesmo algoritmo, conseguir para cada $t[0..j]$ o maior $i$ tal que o sufixo de $t[0..j]$ de tamanho $i+1$ dá match com $s[0..i]$

A função de prefixo $\pi$ de um prefixo $\bar{s}$ é o maior **prefixo próprio** de $\bar{s}$ que é sufixo de $\bar{s}$. Ou seja, montamos uma tabela (sendo $\pi[i]$ a função $\pi$ para o prefixo $s[0..i]$):

$$\pi[i] = \max_{1 \leq j \leq i}\{j: s[0..j-1] = s[i-j+1..i]\}$$
Se sabemos que o melhor prefixo que dá match como sufixo de $t[0..j]$ é $s[0..i]$, ao avançar em **uma unidade** o ponteiro direito da sliding window de $t$ (para $j + 1$), queremos dar o **menor salto possível** do ponteiro esquerdo da sliding window (onde começamos o matching).

Ou seja, se estamos com uma sliding window $(j-i, j)$ em $t$, que dá match com $s[0..i]$, ao tentar mover o ponteiro direito para $j+1$, antes queremos mover o ponteiro esquerdo para $j - \ell$, de forma que possamos reaproveitar tudo e com o menor salto possível: ou seja, precisamos do maior $\ell < i$ tal que

$$t[j - \ell..j] = s[0..\ell] \iff s[i-\ell..i] = s[0..\ell]$$

Para minimizar o salto, queremos maximizar o $\ell$, e dessa forma $\ell = \pi[i] - 1$ e devemos mover o ponteiro esquerdo $i - \ell = i + 1 - \pi[i]$ casas. Como o tamanho do prefixo $s[0..i]$ é $i + 1$, isso corresponder a **pular para o início do maior sufixo que é prefixo desse $s[0..i]$! 

Agora que movemos o ponteiro esquerdo reaproveitando o máximo possível, tentamos mover o ponteiro direito, fazemos as comparações conforme formos seguindo.

```c++
// TODO INCOMPLETO
%% vector<int> match(const string& s, const string& t, const vector<int>& pi){
	const int n = s.size(), m = t.size();
	vector<int> v(m);
	v[0] = (t[0] == s[0]) ? 1 : 0;
	int l = 0;
	for (int r = 1; r < m; r++){
		int l = ;
		while (t[i] != s[v[i]]){  // can't expand
			// we jump 
		}
	}
} %%
```

## Calculando a função $\pi$

Trivialmente $\pi[0] = 0$, uma vez que o único prefixo próprio de $s[0..0]$ é o prefixo vazio.

Considere que sabemos $\pi[i-1]$. Então
$$s[0]...s[\pi[i-1]-1]] = s[i-\pi[i-1]]...s[i-1]$$

Para expandir o matching, precisamos que $s[\pi[i - 1]] = s[i]$. Caso isso não seja verdade, **gulosamente** pulamos para o maior $j$ cujo prefixo $s[0..j]$ ainda é sufixo de $s[0..i-1]$.

Como $s[0..\pi[i-1]-1]$ é sufixo de $s[0..i-1]$ também, então $s[0..j]$ precisa ser sufixo do match anterior, $s[0..\pi[i-1]-1$], e dessa forma pela maximalidade do $\pi$ temos
$$j = \pi[\pi[i-1] - 1] - 1$$

Se ainda não ocorreu matching, então novamente movemos o ponteiro de $j$ para $\pi[j] - 1$, sucessivamente até conseguirmos expandir - ou alcançarmos $j=-1$ sem nenhuma possibilidade de expansão , em que significa que não foi preservado prefixo que é sufixo da iteração anterior e $\pi[i] = (s[i] == s[0])$.

Temos então o seguinte algoritmo:

```c++
vector<int> pi(const string& s){
	int n = s.size();
	vector<int> p(n);
	p[0] = 0;
	for (int i = 1; i < n; i++){
		int j = p[i - 1] - 1;  // end of best match
		while (j >= 0 && s[i] != s[j + 1]){
			j = p[j] - 1;
		}
		if (j == -1) p[i] = s[i] == s[0]; // might match only on new char
		else p[i] = j + 2;  // can expand match to [0...j+1]
	}
	return p;
}
```

Porém, para simplificar a implementação, podemos pensar em $j$ como o tamanho do match, em vez da posição final do match - ou seja, o $j$ do lgoritmo acima mais $1$.

```c++
vector<int> pi(const string& s){
	int n = s.size();
	vector<int> p(n);
	p[0] = 0;
	for (int i = 1; i < n; i++){
		int j = p[i - 1];  // size of best match
		while (j > 0 && s[i] != s[j]){
			// j-1 is end of match
			j = p[j - 1];
		}
		p[i] = j + (s[i] == s[j]);
	}
	return p;
}
```
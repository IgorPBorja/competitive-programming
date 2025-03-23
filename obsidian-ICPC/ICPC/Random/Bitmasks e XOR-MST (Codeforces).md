# Problema:


> [!NOTE] Link para o problema
> https://codeforces.com/contest/888/problem/G

# Solução

Resolveremos o problema recursivamente, de acordo com os bits ativos a serem considerados. Denote por $MST(A, \ell, r, b)$ a MST do subarray

$$A' = [A[\ell] \mod 2^{b + 1}, \dotsc, A[r] \mod 2^{b + 1}]$$
Inicialmente, como $\max A \leq 2^B$ com $B = 30$, sendo $n := |A|$ queremos $MST(A, 0, n - 1, B - 1)$.

**Primeiramente, ordenemos o array**. Assim, todos os seus subarrays também estarão ordenados. Consideremos então o problema de resolver $MST(A, \ell, r, b)$.  Seja $A'$ o subarray acima definido e
$$m = \max\{\ell \leq i \leq r: A[i] \land 2^b = 0\}$$
a última posição em que o $b$-ésimo bit está inativo. Então o subarray $A'[\ell..m-1]$ possui apenas elementos com esse bit inativo e o subarray $A'[m..r]$ possui apenas elementos com esse bit ativo, e os bits de posição anterior ao $b$-ésimo são todos nulos por definição de $MST(A, \ell, r, b)$. 

Assim, podemos calcular os pesos $w_1 = MST(A, \ell, m - 1, b - 1)$  e $w_2 = MST(A, m, r, b - 1)$ das MSTs dessas duas metades e teremos garantia de que não estamos considerando nenhum peso $\geq 2^b$ . Precisamos então agora apenas de uma aresta - a de menor peso - que conecte essas duas metades, **se ambas as metades forem não vazias**. Ou seja, queremos $2^b$ (já que essas duas metades diferem no $b$-ésimo bit) mais o XOR mínimo entre essas duas metades considerando apenas os bits à direita / de menor valor que o $b$-ésimo. Assim, pondo

$$\begin{align*}
\Delta = \min\{(A[i] \mod 2^b) \operatorname{xor} (A[j] \mod 2^b) : \ell \leq i \leq m - 1 \land m \leq j \leq r\}
\end{align*}$$
a resposta final será
$$
	MST(A, \ell, r, b) = \begin{cases}
		w_1 + w_2 + \Delta + 2^b \text{ se } \ell < m \leq r \\
		w_1 + w_2 \text{ caso contrário }
	\end{cases}
$$
Defina por
$$
MX(A, \ell_1, r_1, \ell_2, r_2, b) := \min\{(A[i] \mod 2^{b + 1}) \operatorname{xor} (A[j] \mod 2^{b + 1}) : \ell_1 \leq i \leq r_1 \land \ell_2 \leq j \leq r_2\}
$$

Podemos utilizar uma recursão semelhante para calcular $MX(A, \ell_1, r_1, \ell_2, r_2, b)$ em $O((r_1 - \ell_1 + 1 + r_2 - \ell_2 + 1) \cdot b)$. De fato, segue a recursão (assumindo $\ell_1 \leq r_1$ e $\ell_2 \leq r_2$, para que ambos os intervalos sejam não vazios):

```c++
i64 min_xor(const vector<int>& a, int l1, int r1, int l2, int r2, const int pos){
    // each range is guaranteed to have all bits with position > pos fixed
    if (pos < 0){
        return 0;
    }
    vector<int> la, lb, ra, rb;
    int m1 = l1, m2 = l2;
    while (m1 <= r1 && (a[m1] & (1ll << pos)) == 0) ++m1;
    while (m2 <= r2 && (a[m2] & (1ll << pos)) == 0) ++m2;
    
    if (l1 < m1 && m1 <= r1 && l2 < m2 && m2 <= r2){
        return min(min_xor(a, l1, m1 - 1, l2, m2 - 1, pos - 1), min_xor(a, m1, r1, m2, r2, pos - 1));
    } else if (l1 < m1 && l2 < m2){
        return min_xor(a, l1, m1 - 1, l2, m2 - 1, pos - 1);
    } else if (m1 <= r1 && m2 <= r2){
        return min_xor(a, m1, r1, m2, r2, pos - 1);
    } else if (l1 < m1 && m2 <= r2){
        return min_xor(a, l1, m1 - 1, m2, r2, pos - 1) + (1ll << pos);
    } else if (m1 <= r1 && l2 < m2){
        return min_xor(a, m1, r1, l2, m2 - 1, pos - 1) + (1ll << pos);
    }
}
```

e a solução final será
$$
	MST(A, \ell, r, b) = \begin{cases}
		w_1 + w_2 + MX(A, \ell, m - 1, m, r, b - 1) + 2^b \text{ se } \ell < m \leq r \\
		w_1 + w_2 \text{ caso contrário }
	\end{cases}
$$
Assim, é possível resolver o problema em
$$O\left(\sum_{B - 1 \geq b \geq 0}Nb\right) = O(NB^2)$$
com uma constante relativamente baixa, o que é o suficiente para passar.
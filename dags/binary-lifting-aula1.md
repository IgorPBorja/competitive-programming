# Binary Lifting

Considere uma função $f$ (mais especificamente um operador/uma função de um conjunto nele mesmo): queremos calcular $f^k(x)$ para algum $k$ grande e $x$ no seu domínio. 

**Ideia**: calculamos $f^1, f^2, \dotsc, f^{2^n}$ para $n = O(\log k)$, e depois utilizamos a expansão binária de $k$. Isto é, se $k = \sum b_i 2^i$ então 
$$f^k(x) = \bigotimes_{i:\ b_i \neq 0}f^{2^i}$$
(esse símbolo representando composição sucessiva).

**Complexidade**: 
1. Calcular $f^k(u)$ para um único $u$ dado: $O(n \cdot O(f) +  \log k)$ em que $n$ é o tamanho do domínio da função.
2. Calcular $f^k$, isto é $f^k(u)$ para todo $u$ no domínio: $O(n \cdot O(f) + n \log k)$.

De fato, a complexidade de calcular cada $f^{2^i}$, já conhecendo $f^1, \dotsc, f^{2^{i-1}}$ é de 
$O(n\cdot O(f))$, pois calculamos $f^{2^i}(x) = f^{2^{i-1}}(f^{2^{i-1}}(x))$ em $O(f)$ para cada $x$ no domínio. Como $f^k$ é a composição de algumas funções da "base"
$$\mathcal{B} = \{f^1, \dotsc, f^{2^{\lfloor\log k\rfloor}}\}$$
então podemos calcular $f^k(u)$ com $O(\log(k))$ composições em $O(O(f)\log k)$, e podemos calcular $f^k$ sobre todo ponto em (assintoticamente) $n$ vezes esse tempo.

## Exemplo

### Definições importantes:

**Definição 1 um grafo funcional é um grafo direcionado tal que de todo vértice sai apenas uma aresta**

### O problema

**Enunciado**: suponha que temos um grafo funcional $G$. Dado um vértice $u$ e um $k \geq 0$, queremos calcular o vértice $v$ ao qual se chega com $k$ movimentos, partindo de $u$.  

**Ideia de implementação**: 
Considere a função $f: G \to G$ que leva o vértice $u$ no **único** (pois $G$ é funcional) $v$ tal que $u \to v$. Assim, a $f$ simula um movimento no grafo.

Fazemos então uma DP 2-dimensional, pondo $dp[i][u] = f^{2^i}(u)$ então
$$dp[i + 1][u] = f^{2^i}(f^{2^i}(u)) = dp[i]\big[dp[i][u]\big]$$

Assim, mais geralmente
$$dp[x + y][u] = f^x(f^y(u)) = dp[x]\big[dp[y][u]\big]$$

Obtemos o seguinte (pseudo)código para calcular $f^k(u)$:
```c++
// assuming f^{2^i}(u) = dp[0][u]
result = u
for (i = 0; 2^i <= k; i++)
    bit = (k / 2^i) mod 2
    if (bit == 1)
        // result = f^{2^i}(result)
        result = dp[i][result]
```

# Diâmetro de uma árvore

* Algoritmo $O(n)$:
1. Escolha um $x$ arbitrário 
2. Faça uma DFS partindo de $x$ e encontre $y$ tal que $d(y, x)$ é máximo. 
3. Faça uma DFS partindo de $y$ e encontre $w$ tal que $d(y, w)$ é máximo.
4. Então diâmetro da árvore será: 
$$D_t = d(y, w)$$

Prova:
Suponha que $z_1 \to z_2$ é um caminho com tamanho igual ao diâmetro da árvore. Então 
$d(z_1, z_2) \leq d(z_1, x) + d(x, z_2) = d(x, z_1) + d(x, z_2) \leq 2d(x, y)$
pela maximalidade de $y$. 
(TODO: FINALIZAR)



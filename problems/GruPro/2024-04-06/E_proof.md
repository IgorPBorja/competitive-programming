# Prova da E (INCOMPLETA)

Seja $S[i]$ a melhor solução local: isto é, a melhor solução no segmento $1..i$, ordenando primeiro por quantidade de poções ingeridas e depois ordenando, em caso de empate, pela maior saúde. Seja $h[i]$ a saúde final de $S[i]$ e $c[i]$ a quantidade de poções ingeridas.

Note que não vale a pena, para calcular $S[i + 1]$, usar nenhuma solução não-ótima em questão de quantidade de poções ingeridas: se $S' = (x_1, \dotsc, x_k)$ é uma solução não-ótima, pois $k < c[i]$, com $x_1 < \dotsc < x_k$, então:

1. Se $h[i] + a[i + 1] \geq 0$, então a solução obtida adicionando $a[i + 1]$ à solução $S[i]$ possui $c[i] + 1 > k + 1$ poções, que seria o melhor valor para uma solução construída a partir de $S'$.
2. Se $h[i] + a[i + 1] < 0$, porém $a[i + 1] > \min S[i]$, então a solução obtida trocando uma ocorrência de $\min S[i]$ por $a[i + 1]$ gera uma solução com soma $h[i] - \min S[i] + a[i] > h[i]$. Para a solução    

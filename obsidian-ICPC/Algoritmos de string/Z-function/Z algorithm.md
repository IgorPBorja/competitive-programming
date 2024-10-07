

> [!z-function-def] Definição (função Z)
> Dada uma string $s = s_0\dotsc s_{n - 1}$, a função $z$ para essa dada string é definida por, para todo $0 \leq i < n$:
> $$z[i] = \max\{0 \leq j \leq n - i : z[0..j-1] = z[i..i+j-1]\}$$
> Em particular, para toda string de tamanho $n$, $z[0] = n$.

## Algoritmo:


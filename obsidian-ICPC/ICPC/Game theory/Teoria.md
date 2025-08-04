Link: https://cp-algorithms.com/game_theory/sprague-grundy-nim.html

### Suposições

* O **jogo é imparcial**
	* Ambos os jogadores tem acesso às mesmas informações e às mesmas ações possíveis
* O jogo tem **perfect information** (tudo é visível, todas as informações estão disponíveis)
* O jogo é finito (em uma quantidade finita de movimentos acaba em vitória/derrota, **sem empates**)

O jogo pode, portanto, ser representado por um DAG.

Dado o DAG $G$ de estados do jogo, dizemos que:

* Um estado $u$ é dito vencedor se existe uma aresta $uv$ tal que $v$ é perdedor.
* Um estado $u$ é dito perdedor se para toda aresta $uv$, $v$ é vencedor

Isso é, **um estado $u$ é vencedor se, iniciando o jogo nesse estado e na vez do 1º jogador, o 1º jogador consegue vencer** - e perdedor do contrário.


# Nim

O jogo de Nim consiste de $n$ pilhas com diferente quantidades de pedras $a_1, \dotsc, a_n$. Em um movimento, um jogador pode escolher uma pilha não-vazia e tirar qualquer quantidade de pedras dela. **Vence aquele que tirar a última pedra de todas**: isto é, perde aquele que não poder fazer mais um movimento.

> [!note] Teorema 1 (Nim)
> O jogador do turno atual vence se e somente se a xor-sum $a_1 \oplus a_2 \oplus \dotsc \oplus a_n \neq 0$, em que $\oplus$ é o XOR bit a bit.
^nim-theorem

Prova:

Provamos por indução a seguinte afirmação: 

> [!tip] Afirmação
> Se o xor-sum é 0, então qualquer movimento leva a um estado de xor-sum diferente de zero.
> 
> Se o xor-sum é diferente de 0, então existe um movimento que leva a um xor-sum 0.

A indução será na quantidade total de pedras nas pilhas (ou seja, em $\sum a_i$): no caso de todas as pilhas vazias o jogador atual perde por ser o caso base do jogo.

Então, suponha que para qualquer configuração com $\sum a_i < A$ pedras vale a afirmação anterior, e seja $a_1, \dotsc, a_n$ uma configuração com total de $A$ pedras.

Se o xor-sum é $s = 0$, e um movimento é feito que reduz $a_i$ para $b_i$, então o novo xor-sum é

$$
t = \bigoplus_{1 \leq j \leq n, \ j \neq i} a_j \oplus b_i = \bigoplus_{1 \leq j \leq n}a_j \oplus b_i \oplus a_i = s \oplus a_i \oplus b_i = a_i \oplus b_i
$$
pois $s = 0$, $x \oplus x = 0$ para qualquer $x$ e XOR é uma operação comutativa e associativa. Como $b_i < a_i$ (pelo menos uma pedra é tirada) então $t \neq 0$, provando a primeira parte da afirmação.

Suponha agora que $s \neq 0$. Sabemos que ao realizar um movimento de redução de $a_i$ para $b_i$, o novo xor-sum é $t = s \oplus a_i \oplus b_i = s \oplus (a_i \oplus b_i)$. Sabemos que $s$ indica os bits que aparecem um número ímpar de vezes olhando para o conjunto de todas as pilhas: isto é, se $s = \sum_{i=1\dotsc k} 2^{m_i}$ com $m_1 < \dotsc < m_k$ então os bits nas posições $S = \{m_1, \dots, m_k\}$, e apenas eles, aparecem ativos um número ímpar de vezes no conjunto. Queremos flipar exatamente esses bits em algum número.

Selecione então algum índice $i$ em que o bit $m_k$ de $a_i$ está ativo (ou seja, um elemento com o bit de índice mais alto ativo, dentro os bits ativos um número ímpar de vezes). Você pode então flipar os bits $m_1, \dotsc, m_k$ de $a_i$ que teremos um número **menor** que $a_i$, e portanto uma transição válida de Nim. Além disso, o xor-sum passará a ser $0$.

Dessa forma, está provada a afirmação por indução.


Da afirmação, derivamos o teorema:

* Se o xor-sum inicia como 0, então pelo teorema existe uma estratégia em que o segundo jogador pode sempre tornar o xor-sum igual a 0. Dessa forma, como a quantidade total de pedras decresce a cada jogada, é garantido que em alguma jogada o segundo jogador obtém o estado $a_1 = \dotsc = a_n = 0$, ganhando o jogo.
* Se o xor-sum inicia como diferente de 0, então pelo teorema o primeiro jogador pode torná-lo 0 e mantê-lo 0 a cada jogada sua, eventualmente ganhando o jogo pelo mesmo motivo anterior.


> [!NOTE] Resumo da estratégia de Nim
> Se o bitwise XOR é $= 0$, o jogador 2 **cancelando a jogada do jogador 1**: flipando de uma vez todos os bits que aparecem um número ímpar de vezes em alguma pilha que tem ativo o maior bit "alvo".
>
> Se o bitwise XOR é $\neq 0$, o jogador 1 pode torná-lo 0 dessa forma forma e então adotar a mesma estratégia do caso anterior.

## Mìsere Game

É o jogo oposto do Nim: nessa versão, **perde quem tirar a última pedra**.

Joga-se com a mesma estratégia do Nim, até o final, em que se impõe a seguinte mudança:

* Em uma configuração do tipo $(x, 1, 1, \dotsc, 1)$, com $x > 1$ qualquer, em que uma ou nenhuma pilha não-vazia tem mais que 1 elemento, **em vez de jogar para que a quantidade de 1 fique par (como no Nim), jogamos para que ela fique ímpar**
* Em uma configuração do tipo $(1, 1, \dotsc, 1)$ (apenas uns), o vencedor é o oposto do que seria o vencedor do Nim na mesma configuração: vence o 1º jogador se a quantidade for par.

Ou seja:

* Se temos $(x, 1, \dotsc, 1)$ ($2k$ vezes 1) então:
	* No Nim removeríamos $x$
	* No Mìsere removeríamos $x - 1$
* Se temos $(x, 1, \dotsc, 1)$ ($2k + 1$ vezes 1) então:
	* No Nim removeríamos $x - 1$
	* No Mìsere removeríamos $x$

Se existe ao menos uma pilha com $a_i > 1$, então **necessariamente alcançaremos uma situação com exatamente uma pilha com valor maior que 1**, pois a quantidade de pilhas com valor maior que 1 decresce monotonicamente por 0 unidades ou 1 unidade por turno.

# Teorema de Sprague-Grundy

## Números de Nim


> [!NOTE] Definição 1: Número de Nim
> Para qualquer jogo imparcial de dois jogadores representado por grafo acíclico de estados $G$, **em que as sinks (vértices sem arestas de saída) são vértices perdedores, podemos designar a cada estado (vértice) $v$ o chamado número de Nim** $n(v)$ do estado conforme abaixo.
>
> * Se $v$ não possui arestas de saída (caso base) então $n(v) = 0$
> * Se $v$ possui arestas de saída para $v_1, \dotsc, v_k$ então $$n(v) := \operatorname{mex}(n(v_1), \dotsc, n(v_k))$$

Note: essa condição em que os estados sem movimentos possíveis são estados perdedores é chamada também de [normal play convention](https://en.wikipedia.org/wiki/Normal_play_convention).

> [!NOTE] Teorema 2: Teorema de Sprague-Grundy
> $v$ é um estado vencedor se e somente se $n(v) \neq 0$

Prova:
A prova se dá por indução estrutural no DAG do jogo (supondo um único estado inicial). O caso base de um vértice sem arestas de saída é trivial pela construção do número de Nim, pois $n(v) = 0$ e esse vértice é perdedor pela definição do jogo.

Suponha então que isso é verdade para todo $u$ alcançável a partir de $v$ (conjunto esse que forma um "sub-DAG"), e que $v$ se liga a vértices $v_1, \dotsc, v_k$ pelas transições válidas do jogo.

Então $v$ é vencedor se e somente se algum dos estados $v_1, \dotsc, v_k$ é perdedor, o que ocorre, por hipótese indutiva, se e somente se $n(v_i) = 0$ para algum $i$. Porém, isso é equivalente $\operatorname{mex}(n(v_1), \dotsc, n(v_k)) > 0$ , isto é, $n(v) > 0$. Está provado então por indução.


> [!example] Esses números de Nim também são chamados de **números de Grundy**

## Equivalência a Nim com acréscimos

Observe que, como $n(v)$ é definido via o MEX, então **para todo $m < n(v)$ existe uma transição de $v$ para um estado com número de Grundy $m$**.  Assim, podemos pensar em um movimento como **equivalente a uma transição em um jogo de Nim com uma única pilha e, adicionalmente, com possibilidades de acréscimos de valores específicos**.

Ou seja, em nossa jogada, podemos reduzir para um estado com número de Grundy $m$, para um $m < n(v)$ qualquer (ou seja, reduzir nossa pilha para $m$ elementos), ou ir para um estado com $m \geq n(v)$ para certos valores de $m$ que dependem das regras do jogo e do estado atual. Entretanto, como veremos, as regras de acréscimo específicas não importam, desde que mantenham o jogo acíclico - então, abstrairemos esses detalhes.

Dessa forma, se denotarmos por $*m$ o jogo de Nim com acréscimos em uma única pilha de tamanho $*m$, temos que $v \approx *m$ (são equivalentes).

## Combinando jogos

Sejam $S_1$ e $S_2$ estados em dois jogos independentes que operam sob a _normal play convention_: ganha quem faz o último movimento possível.

**Combinar os dois jogos significa jogá-los ao mesmo tempo (podendo escolher entre jogar no primeiro jogo, em estado inicial $S_1$, ou no segundo jogo, em estado inicial $S_2$), e decidir como ganhador aquele que fizer o último movimento possível globalmente**. Isto é, perde aquele que não consegue realizar um movimento em nenhum dos jogos. Denotamos esse estado no novo jogo por $S_1 + S_2$.

Dessa forma, como observamos que $S \approx *n(S)$ para todo estado $S$, temos que o estado da combinação dos jogos, $S_1 + S_2$, naturalmente é equivalente a $*n(S_1) + *n(S_2)$, **que é o jogo de Nim com acréscimos e duas pilhas com tamanhos $*n(S_1)$ e $*n(S_2)$**. Portanto, basta computarmos a combinação de jogos de Nim. De fato, podemos pensar em pilhas de Nim como jogos independentes, sendo que número de Grundy do jogo de Nim vazio é $0$, e para todo $n$ o número de Grundy de um jogo de Nim com $n$ pedras na pilha é $\operatorname{mex}(0, 1, \dotsc, n-1) = n$ por indução.


> [!NOTE] Lema 1
> O número de Grundy da combinação de dois jogos de Nim $A = \{a_1, \dotsc, a_n\}$ e $B = \{b_1, \dotsc, b_m\}$ é simplesmente o xor-sum dos seus números de Grundy:
> $$
> n(A + B) = n(A) \oplus n(B)
> $$

Temos agora o material necessário para provar o teorema principal sobre teoria de Sprague-Grundy:


> [!NOTE] Teorema 3: Teorema de Sprague-Grundy, generalizado
> Podemos analisar sub-jogos (criados em casos em que transições quebram o jogo em dois ou mais jogos independentes) independentemente: sua combinação se dará pela xor-sum dos números de Grundy dos sub-jogos.
>
> Mais formalmente, seja $G$ o DAG de um jogo imparcial de dois jogadores qualquer, em que as sinks (vértices sem arestas de saída) são vértices perdedores
> 
> Suponha que $v$ se liga a vértices $v_1, \dotsc, v_k$, e cada vértice/estado $v_i$ pode ser interpretado como $k_i$ jogos independentes $u_{i,1}, \dotsc, u_{i,k_i}$, em que para vencer o jogador precisa dar a última jogada (global) nesse conjunto de $k_i$ jogos.
> 
> Então o número de Grundy de $v$ é
> $$n(v) = \operatorname{mex}\left\{\bigoplus_{j=1}^{k_i}n(u_{i,j}): \ 1 \leq i \leq k\right\}$$
> em que $\bigoplus$ é a operação de XOR.

Prova:

Para uma dada transição $v \to v_i$, que gera $k_i$ jogos independentes $u_{i, 1}, \dotsc, u_{i,k_i}$, temos que cada subjogo $u_{i, j}$ é equivalente a $*n(u_{i,j})$, que é o jogo de Nim com acréscimos formado por uma única pilha de tamanho $n(u_{i, j})$.

Assim, como vale a seguinte equivalência de jogos (pela independência entre os subjogos gerados pela transição, que foi dada pelo enunciado):

$$v_i \approx u_{i, 1} + \dotsc + u_{i, k_i}$$
então pelo lema 1

$$
n(v_i) = n(u_{i,1} + \dotsc + u_{i,k_i}) = \bigoplus_{j=1}^{k_i}n(u_{i,j})
$$

Como $v$ leva aos estados $v_1, \dotsc, v_k$, então pela definição dos números de Grundy e pela equação anterior:

$$n(v) = \operatorname{mex}(n(v_1), \dotsc, n(v_k)) = \operatorname{mex}\left\{\bigoplus_{j=1}^{k_i}n(u_{i,j}): \ 1 \leq i \leq k\right\}$$
provando o teorema.
# Detecção de ciclos

*  Maneira "naive": realiza $O(N)$ BFSs (partindo de cada vértice) e para cada uma, se em alguma momento existe uma aresta $(u, v)$ do vértice atual $u$ para um visitado $v$ então há um ciclo.
	* Pode detectar também o **menor ciclo** (usando BFS garantimos que o primeiro ciclo detectado para o vértice $u$ é o menor que o contém)
	* Para o problema de detectar o menor ciclo essa complexidade $O(N \cdot (N + M))$ **é ótima**.
*  Maneira ótima com **apenas uma DFS**
	* Coloração
		* Vértices **brancos: não visitados**
		* Vértices **pretos: visitados e com todos os vizinhos já visitados**
		* Vértices **cinzas: visitados e ainda no path gerado pela DFS (não concluídos)**
	* Existe um ciclo se existe uma aresta entre vértices cinzas
	* Complexidade $O(N+ M)$.

```c++
#define WHITE 0
#define GRAY 1
#define BLACK 2
bool has_cycle = false;

void dfs(vector<vector<int>> &g, int u, vector<int> &color){
	if (color[u] != WHITE){
		continue;
	}
	color[u] = GRAY;
	for (int v: g[u]){
		if (color[v] == GRAY){
			has_cycle = true;
		} else if (color[v] == WHITE){
			dfs(g, u, color);
		}
	}
	color[u] = BLACK;
}
```

# Topological sort

* Encontrar uma ordem dadas **relações de dependência**, sem que haja dependências cíclicas 
* Podemos pensar esse conjunto de objetos e relações de precedência com grafos  como um **grafo direcionado** 
* É necessário que o grafo seja **acíclico (Directed Acyclic Graph - DAG)** 

###  Algoritmo 

*  Realiza-se uma DFS partindo de **cada vértice de grau de entrada 0 (_in-degree_)** 
* A ordem topológica é a **ordem inversa dos vértices que tem sua vizinhança finalizada / completamente visitada** 

```c++
#define WHITE 0
#define GRAY 1
#define BLACK 2
bool has_cycle = false;

void dfs(vector<vector<int>> &g, int u, vector<int> &color, vector<int> &order){
	if (color[u] != WHITE){
		continue;
	}
	color[u] = GRAY;
	for (int v: g[u]){
		if (color[v] == GRAY){
			has_cycle = true;
		} else if (color[v] == WHITE){
			dfs(g, u, color);
		}
	}
	color[u] = BLACK;
	order.emplace_back(u);
}

vector<int> toposort(vector<vector<int>> g){
	vector<vector<int>> gR = reverse_graph(g);  // get the reverse graph of g
	vector<int> color(g.size(), WHITE);
	vector<int> order;
	
	queue<int> sources;
	for (int u = 0; u < gR.size(); u++){
		if (gR[u].size() == 0){
			sources.push(u);
		}
	}
	
	while (!sources.empty()){
		int src = sources.front();
		sources.pop();
		dfs(g, src, color, order);
	}
	reverse(order.begin(), order.end());
	return order;
}
```

### Método alternativo: "desmontando" o grafo a partir das sinks

* Cria uma fila com os vértices de grau de saída 0.
* Para cada vértice $u$ de grau de saída 0, analisa as back-edges $(u, v) \in E^R$ e decrementa o grau de cada um desses vértices $v$ nessas arestas. Caso um deles alcance grau 0, adiciona-o à fila.
	* É como se removéssemos uma sink do grafo e suas arestas relacionadas à cada iteração
* O topological sort é o **histórico da fila invertido**

*  Note que sempre que acrescentamos um vértice ao final da fila colocamos ele também no final da lista invertida da ordem topológica - então podemos eliminar essa fila e iterar apenas sobre essa lista (que crescerá em algumas iterações).

```c++
vector<int> iterative_toposort(vector<vector<int>> g){
	vector<vector<int>> gR = reverse_graph(g);
	const int n = g.size();
	vector<int> deg(n);
	vector<int> order;
	for (int u = 0; u < n; u++){
		deg[u] = g[u].size();
		if (deg[u] == 0){
			order.emplace_back(u);
		}
	}
	for (int i = 0; i < order.size(); i++){
		for (int v: g[order[i]]){
			--deg[v];
			if (deg[v] == 0){
				order.emplace_back(v);
			}
		}
	}
	reverse(order.begin(), order.end());
	return order;
}
```

# Exemplos de problemas com topological sort

*  Toda DP que funciona deve-se ao fato da estrutura das arestas formar um **DAG**
* Porém, algumas DPs explicitamente precisam do DAG

### Exemplo 1: maior (ou menor) caminho em um DAG

*  Relação de recorrência:
* $$dp[u] = \max_{(v, u) \in E}(dp[v] + w(v, u))$$
* Podemos utilizar DP se **processarmos os vértices na ordem topológica**.

### Exemplo 2: scheduling mínimo permitindo várias disciplinas por semestre

* Queremos a composição de grade curricular com a menor quantidade de semestres totais, se não há restrição para a quantidade de disciplinas por semestre.
* No fim, é equivalente ao **maior caminho mínimo no DAG** (i.e diâmetro)
* Pode ser feito via **BFS**, começando com uma fila contendo todas as sources com distância atribuída como 0.


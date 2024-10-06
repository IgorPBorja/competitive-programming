#include <iomanip>  // setprecision
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;


struct HashTable {
	const int INF = 1e9;
	vector<int> T;
	int m1, m2;
	int total_probings;

	HashTable(int m, int m1, int m2) : m1(m1), m2(m2), total_probings(0) {
		T.resize(m);
		T.assign(m, INF);
	}

	bool insert(int x){
		int h1 = x % m1;
		int h2 = 1 + (x % m2);
		// infer existence of cycle
		// occurs with the smallest i s.t i * h2(x) = 0 mod m
		// which is i = m / gcd(m, h2(x))

		const int m = T.size();
		const int max_iterations = m / gcd(m, h2);
		int cur = h1, count_iterations = 0;
		while (count_iterations < max_iterations){
			++total_probings;
			if (T[cur] == INF){
				T[cur] = x;
				return true;
			} else {
				cur = (cur + h2) % m;
				++count_iterations;
			}
		}
		return false;
	}

	bool insert_batch(int X[], int n){
		bool ok = true;
		for (int i = 0; i < n; i++){
			ok = ok && insert(X[i]);
		}
		return ok;
	}

	void print(){
		cout << "H=[";
		for (int x: T){
			if (x == INF){
				cout << "NULL, ";
			} else {
				cout << x << ", ";
			}
		}
		cout << "]" << endl;
	}

	HashTable& operator=(HashTable& new_table){
		this->T = new_table.T;
		this->m1 = new_table.m1;
		this->m2 = new_table.m2;
		this->total_probings = new_table.total_probings;
		return *this;
	}
};

int main(){
	int X[] = {6, 90, 22, 18, 30, 39, 51, 69, 73, 33};
	int n = sizeof(X) / sizeof(int);
	int m = 11;
	
	int min_probings = 1e9;
	int ideal_m1, ideal_m2;
	HashTable ideal_H(m, 1, 1);
	for (int m1 = 1; m1 <= m; m1++){
		for (int m2 = 1; m2 <= m; m2++){
			HashTable H(m, m1, m2);
			bool status = H.insert_batch(X, n);
			if (status && (H.total_probings < min_probings)){
				min_probings = H.total_probings;
				ideal_m1 = m1;
				ideal_m2 = m2;
				ideal_H = H;
			}
		}
	}

	float avg_probings = (float)min_probings / (float)n;
	cout << "Configuração ideal para HashTable é m1=" << ideal_m1 << " e m2=" << ideal_m2 << endl;
	cout << "Com " << min_probings << " sondagens totais" << endl;
	cout << "Com uma média de " << fixed << setprecision(3) << avg_probings << " sondagens por elemento inserido" << endl;
	ideal_H.print();
	cout << endl;

	// calcula sondagens para o problema
	HashTable H(m, 7, 5);
	bool status = H.insert_batch(X, n);
	if (!status){
		cout << "Inserção de todos os elementos com m1=7 e m2=5 foi impossível" << endl;
	} else {
		int probings = H.total_probings;
		cout << "Configuração com m1=7 e m2=5:" << endl;
		cout << "Tivemos " << probings << " sondagens totais" << endl;
		cout << "Com uma média de " << fixed << setprecision(3) << (float)probings / (float)n << " sondagens por elemento inserido" << endl;
		H.print();
	}
}

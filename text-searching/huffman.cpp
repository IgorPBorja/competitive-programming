#include <bits/stdc++.h>
using namespace std;

struct Node {
    char symbol = 0;
    double weight;
    shared_ptr<Node> children[2] = {nullptr, nullptr};

    Node(double weight, char symbol = 0) : weight(weight), symbol(symbol) {}
};

bool operator>(Node n1, Node n2){
    return n1.weight > n2.weight;
}

struct HuffmanEncoding {
    shared_ptr<Node> tree;
    unordered_map<char, string> encoding;

    // encode from probability (or estimated probability) vector
    HuffmanEncoding(const vector<char>& alphabet, const vector<double>& weights){
        _init_from_probabilities(alphabet, weights);
    }

    // encode from message
    HuffmanEncoding(const string& msg){
        // build frequency array
        // assumes lowercase and uppercase
        unordered_map<char, int> indices;
        vector<char> alphabet;
        int n = 0;
        for (const char c: msg){
            if (indices.find(c) == indices.end()){
                indices[c] = n++;
                alphabet.emplace_back(c);
            }
        }
        vector<int> freq(n);
        vector<double> weights(n);
        for (const char c: msg){
            ++freq[indices[c]];
        }
        for (int i = 0; i < n; i++){
            weights[i] = (double(freq[i])) / (double(msg.size()));
        }
        _init_from_probabilities(alphabet, weights);
    }

    string decode(string s, string sep = ""){
        string t = "";        
        for (int i = 0; i < s.size(); i++){
            t += encoding[s[i]];
            if (i + 1 < s.size()) t += sep;
        }
        return t;
    }
private:
    void _init_from_probabilities(const vector<char>& alphabet, const vector<double>& weights){
        _build(alphabet, weights);
        vector<char> path;
        _dfs(tree, path);
    }

    void _build(const vector<char>& A, const vector<double>& weights){
        assert(weights.size() >= A.size() && A.size() >= 2);
        // erase previous codification
        tree.reset();
        encoding.clear();

        priority_queue<Node, vector<Node>, greater<Node>> pq;
        // initial nodes
        for (int i = 0; i < A.size(); i++){
            pq.emplace(weights[i], A[i]);
        }
        while (pq.size() > 1){
            Node n1 = pq.top();
            pq.pop();
            Node n2 = pq.top();
            pq.pop();
            Node parent = Node(n1.weight + n2.weight);
            parent.children[0] = make_shared<Node>(n1);
            parent.children[1] = make_shared<Node>(n2);
            pq.push(parent);
        }
        Node root = pq.top();
        tree = make_shared<Node>(root);
    }

    void _dfs(shared_ptr<Node> cur, vector<char>& path){
        if (cur->symbol != 0){
            // O(depth(tree)) building of encoding
            string code(path.begin(), path.end());
            encoding[cur->symbol] = code;
        }
        for (int i = 0; i < 2; i++){
            if (cur->children[i] != nullptr){
                path.emplace_back(char('0' + i));
                _dfs(cur->children[i], path);
                path.pop_back();
            }
        }
    }
};

signed main(){
    vector<char> a = {'a', 'b', 'c', 'd'};
    vector<double> w = {0.4, 0.35, 0.2, 0.05};

    HuffmanEncoding coding(a, w);
    cout << coding.decode("abacd", "|") << endl;
}

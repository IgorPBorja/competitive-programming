#include <bits/stdc++.h>
using namespace std;

// implementation in a graph where the values on the nodes are not consecutive numbers (1...n)
template <typename T>
vector<T> bfs_with_path(map<T, vector<T>>& adj,
                        map<T, bool>& visited,
                        T start,
                        T end
                        ){
    queue<vector<T>> paths;
    
    paths.push({start});
    visited[start] = true;
    while (!paths.empty()){
        vector<T> curr_path = paths.front();
        paths.pop();
        
        T last_node = curr_path[curr_path.size() - 1];
        if (last_node == end){
            return curr_path;
        } else {
            for (T u: adj[last_node]){
                if (!visited[u]){
                    visited[u] = true;
                    vector<T> new_path = curr_path;
                    new_path.push_back(u);
                    paths.push(new_path);
                }
            }
        }
    }
    return {}; // no paths
}

/* Example:
int main(){
    map<string, vector<string>> adj = {
                                        {"a", {"b", "e"}},
                                        {"b", {"a", "c"}},
                                        {"c", {"b", "d", "e", "f"}},
                                        {"d", {"c", "e", "f"}},
                                        {"e", {"c", "d", "e", "f", "g"}},
                                        {"f", {"c", "d", "e", "g"}},
                                        {"g", {"e", "f"}}
                                        };

    map<string, bool> visited; 
    for (auto key: adj) 
        visited[key.first] = false;
    vector<string> ans = bfs_with_path(adj, visited, string("b"), string("g"));
    
    for (string node: ans){
        cout << node << " ";
    }
}
*/

// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 INF = (i64)2e18;

const map<char, i64> value_map = {
    {'A', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'D', 10},
    {'Q', 11},
    {'J', 12},
    {'K', 13}
};

constexpr i64 WILDCARD = 100;

struct Player {
    vector<i64> cards;
    bool has_wildcard = false;
    i64 turns_since_wildcard = 0;

    Player() {}

    void erase_by_key(i64 val){
        vector<i64> new_cards;
        bool erased = false;
        for (i64 x: cards){
            if (!erased && x == val){
                erased = true;
                continue;
            }
            new_cards.emplace_back(x);
        }
        cards = new_cards;
    }

    map<i64, i64> get_freq_map(){
        map<i64, i64> f;
        // now skip WILDCARD
        for (i64 x: cards){
            if (x == WILDCARD) continue;
            ++f[x];
        }
        return f;
    }

    i64 get_card(){
        if (has_wildcard && turns_since_wildcard > 0) {
            return WILDCARD;
        }
        auto freq_map = get_freq_map();
        // freq, val
        vector<pair<i64, i64>> f;
        for (auto[val, freq]: freq_map){
            f.emplace_back(freq, val);
        }
        sort(all(f));
        return f[0].second;
    }

    bool is_winning(){
        auto freq_map = get_freq_map();
        return freq_map[cards[0]] == (i64)cards.size();  // all equal
    }
};

void pass_card(i64 idx, vector<Player>& p){
    const i64 n = p.size();
    i64 c = p[idx].get_card();
    i64 next = (idx + 1) % n;
    // cout << "passing card c=" << c << " from idx=" << idx+1 << " to next=" << next+1 << endl; 
    p[idx].erase_by_key(c);
    p[next].cards.emplace_back(c);
    if (c == WILDCARD){
        // received wildcard
        p[next].has_wildcard = true;
        p[next].turns_since_wildcard = 0;
        // lost wildcard
        p[idx].has_wildcard = false;
        p[idx].turns_since_wildcard = 0;
    } else if (p[idx].has_wildcard){
        // did have wildcard but did not lose it
        ++p[idx].turns_since_wildcard;
    }
}

// returns -1 in case of no winner
i64 check_winner(vector<Player>& players){
    i64 win_value = INF;
    i64 winning_player = -1;
    const i64 n = players.size();
    for (i64 i = 0; i < n; i++) {
        if (players[i].is_winning()) {
            if (players[i].cards[0] < win_value){
                win_value = players[i].cards[0];
                winning_player = i;
            }
        }
    }
    return winning_player;
}

void solve(){
    i64 n, k;
    cin >> n >> k;
    --k;  // 0-index k
    vector<Player> p(n);

    for (i64 i = 0; i < n; i++){
        string s;
        cin >> s;
        for (char c: s){
            p[i].cards.emplace_back(value_map.at(c));
        }
    }
    p[k].cards.emplace_back(WILDCARD);
    p[k].has_wildcard = true;

    i64 winner = -1;
    i64 idx = k;
    while ((winner = check_winner(p)) == -1){
        pass_card(idx, p);
        idx = (idx + 1) % n; 
    }
    cout << winner + 1 << endl;  // 1-index winner
}
 
signed main(){
	fastio;
	int t;
#ifdef TESTCASES
	cin >> t;
#else
	t = 1;
#endif
	while (t--){
		solve();
	}
}

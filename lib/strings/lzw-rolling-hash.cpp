// TODO deal with collisions in rolling hash (will probably break correctness)

#include <bits/stdc++.h>
#define printmsg(msg, iterator) cout << msg;for(auto x: iterator){cout<<x<<" ";}cout<<endl
#define i64 int64_t

using namespace std;

namespace RollingHash {
    vector<i64> _prime_pows = {1};
    const i64 p = 53, m = (i64)1e9 + 7;

    vector<i64> rollingHash(const vector<int>& v, i64 p, i64 m){
        const i64 n = v.size();
        vector<i64> prefH(n);
        vector<i64> p_pow(n);
        // prefH = RollingHash(v[0...i]) = sum(j<=i) v[j] * p^j mod m
        p_pow[0] = 1;
        prefH[0] = v[0] % m;
        for (i64 i = 1; i < n; i++){
            p_pow[i] = (p_pow[i - 1] * p) % m;
            prefH[i] = (v[i] * p_pow[i] + prefH[i - 1]) % m;
        }
        return prefH;
    }

    // lowercase
    vector<i64> rollingHash(const string& s){
        vector<int> s_repr(s.size());
        for (i64 i = 0; i < s.size(); i++){
            s_repr[i] = s[i] - 'a';
        }
        return rollingHash(s_repr, 31, (i64)1e9 + 7);
    }

    i64 encode(char c){
        if (c - 'A' < 26){
            return ((c - 'A') + 1) % m;
        } else {
            return ((c - 'a') + 1 + 26) % m;
        }
    }

    void precompute(int pos){
        if (_prime_pows.size() <= pos){
            const int _s = _prime_pows.size();
            _prime_pows.resize(pos + 1);
            for (int i = _s; i <= pos; i++){
                _prime_pows[pos] = (_prime_pows[pos - 1] * p) % m;
            }
        }
    }

    i64 add_char(char c, int pos, const i64 cur_hash = 0){
        RollingHash::precompute(pos);
        return (cur_hash + ((RollingHash::encode(c) * _prime_pows[pos]) % m)) % m;
    }

    i64 remove_char(char c, int pos, const i64 cur_hash = 0){
        RollingHash::precompute(pos);
        return (cur_hash + m - ((RollingHash::encode(c) * _prime_pows[pos]) % m)) % m;
    }
}

struct word {
    int idx;
    char next;
};

ostream& operator<<(ostream& os, word w){
    os << "(" << w.idx << "," << w.next << ")";
    return os;
}

struct LZW {
    unordered_map<i64, int> lookup_dict;  // maps hash to idx
    vector<string> words;
    vector<char> alphabet;
    int idx = 0;

    LZW(const vector<char>& alphabet) : alphabet(alphabet) {
        setup(alphabet);
    }

    LZW() = default;

    void ascii_letters_setup() {
        // standard lowercase/uppercase
        alphabet.resize(52);
        iota(alphabet.begin(), alphabet.begin() + 26, 'a');
        iota(alphabet.begin() + 26, alphabet.end(), 'A');
        printmsg("alphabet=", alphabet);
        setup(alphabet);
    }

    vector<word> encode(const string& stream){
        reset();

        string cur = "";
        i64 h = 0;
        vector<word> code;
        for (const char c: stream){
            i64 new_h = RollingHash::add_char(c, cur.size(), h);
            unordered_map<i64, int>::iterator it = lookup_dict.find(new_h);
            if (it != lookup_dict.end()){
                // found word, keep looking
                h = new_h;
                cur.push_back(c);
                continue;
            }
            // cur + c is not in dict but cur is
            if (cur.size() == 0){
                // empty
                code.push_back({.idx=-1, .next=c});
            } else {
                code.push_back({.idx=lookup_dict[h], .next=c});
            }
            lookup_dict[new_h] = idx++;
            cur.push_back(c);
            words.emplace_back(cur);
            cur = "";
            h = 0;
        }
        if (cur.size() == 1){
            // last char remained
            code.push_back({.idx=-1, .next=cur[0]});
        } else if (cur.size() > 0){
            // suffix matched, so taking one from the end still matches
            // (otherwise would have stopped just before last char)
            h = RollingHash::remove_char(cur.back(), cur.size() - 1, h);
            code.push_back({.idx=lookup_dict[h], .next=cur.back()});
        }
        return code;
    }

    string decode(const vector<word>& code){
        string s;
        for (const word& W: code){
            if (W.idx != -1){
                s += words[W.idx];
            }
            s += W.next;
        }
        return s;
    }
private:
    void setup(const vector<char>& alphabet){
        for (const char c: alphabet){
            lookup_dict[RollingHash::encode(c)] = idx++;
            words.emplace_back(to_string(c));
        }
    }

    void reset(){
        lookup_dict.clear();
        words.clear();
        idx = 0;
        setup(alphabet);
    }
};

signed main(){
    LZW enc;
    string s;
    cin >> s;
    vector<word> code = enc.encode(s);
    cout << "Encoded string: ";
    for (const word& w: code){
        cout << w << " ";
    }
    cout << endl;
    cout << "Decoded string: " << enc.decode(code) << endl;
    // assert(enc.decode(code) == s);
}

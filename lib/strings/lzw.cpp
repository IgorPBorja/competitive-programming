#include <bits/stdc++.h>
#define printmsg(msg, iterator) cout << msg;for(auto x: iterator){cout<<x<<" ";}cout<<endl
using namespace std;

struct word {
    int idx;
    char next;
};

ostream& operator<<(ostream& os, word w){
    os << "(" << w.idx << "," << w.next << ")";
    return os;
}

struct LZW {
    unordered_map<string, int> lookup_dict;
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
        vector<word> code;
        for (const char c: stream){
            cur += c;
            // TODO isn't this quadratic? rolling hash might be needed
            unordered_map<string, int>::iterator it = lookup_dict.find(cur);
            if (it != lookup_dict.end()){
                // found word, keep looking
                continue;
            }
            // cur is not in dict but cur \ c is
            cur.pop_back();
            if (cur.size() == 0){
                // empty
                code.push_back({.idx=-1, .next=c});
            } else {
                code.push_back({.idx=lookup_dict[cur], .next=c});
            }
            cur.push_back(c);
            lookup_dict[cur] = idx++;
            words.emplace_back(cur);
            cur = "";
        }
        if (cur.size() == 1){
            // last char remained
            code.push_back({.idx=-1, .next=cur[0]});
        } else if (cur.size() > 0){
            // suffix matched, so taking one from the end still matches
            // (otherwise would have stopped just before last char)
            char c = cur.back();
            cur.pop_back();
            code.push_back({.idx=lookup_dict[cur], .next=c});
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
            lookup_dict[to_string(c)] = idx++;
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
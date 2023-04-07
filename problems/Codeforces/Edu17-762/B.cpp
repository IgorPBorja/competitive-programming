#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'

template <typename ForwardIterator>
void read(ForwardIterator itr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> *itr;
        ++itr;
    }
}
template <typename ForwardIterator>
void print(ForwardIterator itr, int n, string sep=" ")
{
    for (int i = 0; i < n; i++)
    {
        cout << *itr << sep;
        ++itr;
    }
}
template <typename ForwardIterator, typename T>
void setval(ForwardIterator itr, int n, T v)
{
    for (int i = 0; i < n; i++)
    {
        *itr = v;
        ++itr;
    }
}

template <typename ForwardIterator>
void read_pairs(ForwardIterator itr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> itr->first >> itr->second;
        ++itr;
    }
}

int main(){
    fastio;
    int usb, ps2, both, n;
    cin >> usb >> ps2 >> both;

    vi m_usb, m_ps2;
    cin >> n;
    for (int i = 0; i < n; i++){
        int p;
        string type;
        cin >> p >> type;
        if (type == "USB") m_usb.eb(p);
        else m_ps2.eb(p);
    }
    sort(m_usb.begin(), m_usb.end());
    sort(m_ps2.begin(), m_ps2.end());
    int lusb = 0, lps2 = 0;
    long long total = 0; // no overflow (val can be up to 1e9)
    // pick usb
    while (lusb < (int)m_usb.size() && usb > 0){
        total += (long long)(m_usb[lusb]);
        ++lusb;
        --usb;
    }
    // pick ps2
    while (lps2 < (int)m_ps2.size() && ps2 > 0){
        total += (long long)(m_ps2[lps2]);
        ++lps2;
        --ps2;
    }
    // pick both
    while (( lusb < (int)m_usb.size() || lps2 < (int)m_ps2.size() ) && both > 0){
        bool grab_usb = (lusb < (int)m_usb.size());
        bool grab_ps2 = (lps2 < (int)m_ps2.size());
        if (!grab_ps2 || (grab_usb && grab_ps2 && m_usb[lusb] <= m_ps2[lps2]) ){
            total += (long long)(m_usb[lusb]);
            ++lusb;
        } else if (!grab_usb || (grab_usb && grab_ps2 && m_ps2[lps2] < m_usb[lusb]) ){
            total += (long long)(m_ps2[lps2]);
            ++lps2;
        }
        --both;
    }
    cout << lusb + lps2 << ' ' << total << '\n';
}

#include <bits/stdc++.h>
using namespace std;

int main(){
    int x, y, r;
    cin >> x >> y >> r;
    cout << x - r << " " << y - r << endl;  // topleft
    cout << x + r << " " << y - r << endl;  // topright
    cout << x + r << " " << y + r << endl;  // bottom right
    cout << x -r  << " " << y + r << endl;  // bottom left
}
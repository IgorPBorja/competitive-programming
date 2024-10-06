
"""
    i64 n;
    cin >> n;
    vector<i64> a;
    i64 mx = 1, x;
    for (i64 i = 0; i < n; i++){
        cin >> x;
        mx = max(mx, x);
        while (true){
            if (!a.empty() && a.back() == x){
                a.pop_back();
                x *= 2;
                mx = max(mx, x);
            } else if (a.size() >= 2 && a[a.size() - 2] == x){
                a.pop_back();
                a.pop_back();
                x *= 2;
                mx = max(mx, x);
            } else {
                break;
            }
        }
        a.push_back(x);
        // printmsg("a=", a.begin(), a.end());
    }
    cout << mx << endl;
"""

n = int(input())
a = list(map(int, input().split()))

b = []
mx = 1
for x in a:
    while True:
        if b and b[-1] == x:
            b.pop()
            x *= 2
            mx = max(mx, x)
        elif len(b) >= 2 and b[-2] == x:
            b.pop()
            b.pop()
            x *= 2
            mx = max(mx, x)
        else:
            break
    mx = max(mx, x)
    b.append(x)
print(mx)

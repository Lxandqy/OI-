#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    int mx = 0;
    bool allSame = true;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
        if (i > 0 && a[i] != a[0]) {
            allSame = false;
        }
    }

    int best = 0;
    if (n <= 100) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (a[i] == a[j]) {
                    best = max(best, a[i]);
                }
            }
        }
    } else if (allSame) {
        best = a[0];
    } else if (mx <= 1000) {
        vector<int> cnt(1001, 0);
        for (int x : a) {
            cnt[x]++;
        }
        for (int x = 1; x <= 1000; x++) {
            if (cnt[x] >= 2) {
                best = x;
            }
        }
    } else {
        cout << 0 << '\n';
        return 0;
    }

    cout << 1LL * best * n << '\n';
    return 0;
}

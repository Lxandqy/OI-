#include<bits/stdc++.h>
using namespace std;

long long brute(const vector<long long> &a, long long k) {
    long long ans = -1;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long value = a[i] * a[i] + a[j] * a[j];
            if (value % k == 0) {
                ans = max(ans, value);
            }
        }
    }
    return ans;
}

long long smallK(const vector<long long> &a, int k) {
    vector<pair<long long,long long>> best(k, {0, 0});
    for (long long x : a) {
        int r = (long long)((__int128)x * x % k);
        if (x > best[r].first) {
            best[r].second = best[r].first;
            best[r].first = x;
        } else if (x > best[r].second) {
            best[r].second = x;
        }
    }
    long long ans = -1;
    for (int r = 0; r < k; r++) {
        int s = (k - r) % k;
        if (r == s) {
            if (best[r].second > 0) {
                ans = max(ans, best[r].first * best[r].first + best[r].second * best[r].second);
            }
        } else if (best[r].first > 0 && best[s].first > 0) {
            ans = max(ans, best[r].first * best[r].first + best[s].first * best[s].first);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (long long &x : a) {
        cin >> x;
    }

    if (n <= 2000) {
        cout << brute(a, k) << '\n';
    } else if (k <= 100000) {
        cout << smallK(a, (int)k) << '\n';
    } else {
        cout << -1 << '\n';
    }
    return 0;
}

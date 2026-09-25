#include<bits/stdc++.h>
using namespace std;

struct CustomHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t seed = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + seed);
    }
};

void insertValue(pair<long long,long long> &p, long long x) {
    if (x > p.first) {
        p.second = p.first;
        p.first = x;
    } else if (x > p.second) {
        p.second = x;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;

    unordered_map<long long,pair<long long,long long>,CustomHash> best;
    best.reserve(n * 2 + 10);
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        long long r = (long long)((__int128)x * x % k);
        auto &p = best[r];
        insertValue(p, x);
    }

    long long ans = -1;
    for (const auto &it : best) {
        long long r = it.first;
        long long s = (k - r) % k;
        auto jt = best.find(s);
        if (jt == best.end()) {
            continue;
        }
        if (r == s) {
            if (it.second.second > 0) {
                ans = max(ans, it.second.first * it.second.first + it.second.second * it.second.second);
            }
        } else {
            ans = max(ans, it.second.first * it.second.first + jt->second.first * jt->second.first);
        }
    }

    cout << ans << '\n';
    return 0;
}

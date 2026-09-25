#include<bits/stdc++.h>
using namespace std;

long long solve(const string &s) {
    int n = s.size();
    const long long inf = (1LL << 60);
    long long answer = inf;

    auto id = [](char c) {
        if (c == 'r') return 0;
        if (c == 'g') return 1;
        return 2;
    };

    for (int first = 0; first < 3; first++) {
        long long dp[3] = {inf, inf, inf};
        dp[first] = (first - id(s[0]) + 3) % 3;

        for (int i = 1; i < n; i++) {
            long long ndp[3] = {inf, inf, inf};
            int original = id(s[i]);
            for (int last = 0; last < 3; last++) {
                for (int now = 0; now < 3; now++) {
                    if (last != now) {
                        ndp[now] = min(ndp[now], dp[last] + (now - original + 3) % 3);
                    }
                }
            }
            for (int c = 0; c < 3; c++) {
                dp[c] = ndp[c];
            }
        }

        for (int last = 0; last < 3; last++) {
            if (last != first) {
                answer = min(answer, dp[last]);
            }
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;
    cout << solve(s) << '\n';
    return 0;
}

#include<bits/stdc++.h>
#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int L, R;
        cin >> L >> R;
        vector<int> len(R + 1, 1);
        vector<cpp_int> ways(R + 1, 1);

        for (int x = L; x <= R; x++) {
            for (int y = x + x; y <= R; y += x) {
                int candidate = len[x] + 1;
                if (candidate > len[y]) {
                    len[y] = candidate;
                    ways[y] = ways[x];
                } else if (candidate == len[y]) {
                    ways[y] += ways[x];
                }
            }
        }

        int bestLen = 0;
        cpp_int answer = 0;
        for (int x = L; x <= R; x++) {
            if (len[x] > bestLen) {
                bestLen = len[x];
                answer = ways[x];
            } else if (len[x] == bestLen) {
                answer += ways[x];
            }
        }
        cout << bestLen << ' ' << answer << '\n';
    }
    return 0;
}

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
        int n = R - L + 1;
        if (!(n <= 21 || R <= 2000)) {
            cout << "0 0\n";
            continue;
        }

        vector<int> len(n, 1);
        vector<cpp_int> ways(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x = L + i;
                int y = L + j;
                if (y % x == 0) {
                    int candidate = len[i] + 1;
                    if (candidate > len[j]) {
                        len[j] = candidate;
                        ways[j] = ways[i];
                    } else if (candidate == len[j]) {
                        ways[j] += ways[i];
                    }
                }
            }
        }

        int bestLen = 0;
        cpp_int answer = 0;
        for (int i = 0; i < n; i++) {
            if (len[i] > bestLen) {
                bestLen = len[i];
                answer = ways[i];
            } else if (len[i] == bestLen) {
                answer += ways[i];
            }
        }
        cout << bestLen << ' ' << answer << '\n';
    }
    return 0;
}

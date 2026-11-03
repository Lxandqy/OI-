// 守护行动，第1项：所有k_i等于1；子任务1保证17分；时间O(n)，空间O(1)。
#include<bits/stdc++.h>
using namespace std;


int main(){
    int n;
    long long s,sum = 0;
    cin >> n >> s;
    for(int i = 1; i <= n; i++){
        long long a,k;
        cin >> a >> k;
        sum += a;
    }
    cout << max(0ll,sum - s) << '\n';
    return 0;
}

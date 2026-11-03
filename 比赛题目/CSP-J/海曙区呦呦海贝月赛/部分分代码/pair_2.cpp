// 双人挑战，第2项：每人去向固定；点9至10保证10分；时间O(n+m)，空间O(m)。
#include<bits/stdc++.h>
using namespace std;


const int N = 100000 + 10;
int cnt[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    long long k;
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++){
        int a,b;
        cin >> a >> b;
        cnt[a]++;
    }
    for(int i = 1; i <= m; i++){
        if(cnt[i] % 2 == 1) k--;
    }
    cout << k << '\n';
    return 0;
}

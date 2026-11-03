#include<bits/stdc++.h>
using namespace std;
const int N = 500010;
const int MOD = 998244353;
int n,m,a[N],b[N],L[N],R[N],t[N];
long long P[N],Q[N];
void add(int x,int v){
    for(; x <= m; x += x & -x){
        t[x] += v;
        if(t[x] >= MOD) t[x] -= MOD;
    }
}
int ask(int x){
    int sum = 0;
    for(; x > 0; x -= x & -x){
        sum += t[x];
        if(sum >= MOD) sum -= MOD;
    }
    return sum;
}
int main(){
    freopen("cut.in","r",stdin);
    freopen("cut.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        b[i] = a[i];
    }
    for(int i = 1; i <= n; i++){
        L[i] = 1;
        if(i > 1 && a[i - 1] < a[i]) L[i] = L[i - 1] + 1;
        P[i] = (P[i - 1] + L[i]) % MOD;
    }
    for(int i = n; i >= 1; i--){
        R[i] = 1;
        if(i < n && a[i] < a[i + 1]) R[i] = R[i + 1] + 1;
        Q[i] = (Q[i + 1] + R[i]) % MOD;
    }
    long long ans = 0;
    // 未跨接缝的上升段：按删除区间的左端点、右端点分别求和。
    for(int i = 1; i <= n; i++){
        ans = (ans + P[i - 1] * (n - i + 1) + Q[i + 1] * i) % MOD;
    }
    sort(b + 1,b + n + 1);
    m = unique(b + 1,b + n + 1) - b - 1;
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(b + 1,b + m + 1,a[i]) - b;
    }
    // 接缝为 i,j 时删去 i+1..j-1，跨缝上升段有 L[i]*R[j] 个。
    for(int j = 3; j <= n; j++){
        add(a[j - 2],L[j - 2]);
        ans = (ans + 1LL * ask(a[j] - 1) * R[j]) % MOD;
    }
    cout << ans << '\n';
    return 0;
}

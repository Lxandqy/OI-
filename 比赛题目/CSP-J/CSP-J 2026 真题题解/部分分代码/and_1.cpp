// 按位与 and，部分分 1：枚举恰好 m 个位置
// 适用条件：n <= 20；另支持 n <= 2000 且 m 为 1、n 或 2
// 保证覆盖：点 1-10，50 分
// 复杂度：通常 O(2^n)；m=1 或 m=n 时 O(n)，m=2 时 O(n^2)；空间 O(n)
#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
int n,m,a[N],ans;

void dfs(int x,int cnt,int val){
    if(cnt == m){
        ans = max(ans,val);
        return;
    }
    for(int i = x; i <= n - (m - cnt) + 1; i++){
        dfs(i + 1,cnt + 1,val & a[i]);
    }
}

int main(){
    freopen("and.in","r",stdin);
    freopen("and.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    dfs(1,0,(1 << 30) - 1);
    cout << ans << '\n';
    return 0;
}

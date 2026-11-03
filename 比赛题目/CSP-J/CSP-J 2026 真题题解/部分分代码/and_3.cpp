// 按位与 and，部分分 3：枚举两个位置
// 适用条件：m=2 且 n<=2000
// 保证覆盖：点 8-10，15 分
// 复杂度：时间 O(n^2)，空间 O(n)
#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
int a[N];

int main(){
    freopen("and.in","r",stdin);
    freopen("and.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            ans = max(ans,a[i] & a[j]);
        }
    }
    cout << ans << '\n';
    return 0;
}

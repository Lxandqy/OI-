// 按位与 and，部分分 6：性质 B 按所需数量确定低位零的个数
// 适用条件：n=2^k 且 a[i]=i-1
// 保证覆盖：点 14、15，10 分
// 复杂度：含读入时间 O(n+log m)，额外空间 O(1)
#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("and.in","r",stdin);
    freopen("and.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
    }
    int p = 1;
    while(p < m) p *= 2;
    cout << n - p << '\n';
    return 0;
}

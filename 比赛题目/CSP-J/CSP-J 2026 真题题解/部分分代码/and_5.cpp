// 按位与 and，部分分 5：性质 A 排序取第 m 大
// 适用条件：各 a[i] 为 2^k-1；或 m=1
// 保证覆盖：点 6、13，10 分
// 复杂度：时间 O(n log n)，空间 O(n)
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
    sort(a + 1,a + n + 1);
    cout << a[n - m + 1] << '\n';
    return 0;
}

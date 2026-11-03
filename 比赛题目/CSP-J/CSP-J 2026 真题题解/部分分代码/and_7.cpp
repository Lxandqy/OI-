// 按位与 and，部分分 7：小值域频次统计并枚举答案
// 适用条件：所有 a[i]<U，U<=1024
// 保证覆盖：点 16-19，20 分
// 复杂度：时间 O(n+U^2)，空间 O(n+U)
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
    int mx = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        mx = max(mx,a[i]);
    }
    vector<int> cnt(mx + 1,0);
    for(int i = 1; i <= n; i++) cnt[a[i]]++;
    for(int x = mx; x >= 0; x--){
        int sum = 0;
        for(int v = 0; v <= mx; v++){
            if((v & x) == x) sum += cnt[v];
        }
        if(sum >= m){
            cout << x << '\n';
            break;
        }
    }
    return 0;
}

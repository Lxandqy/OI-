// 双人挑战，第1项：二选一搜索并维护奇数组数；点1至10合计保证50分。
// n,m<=20时O(2^n+n+m)；全a=b时O(n+m)。空间O(n+m)，递归深度n。
#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
int n,m,a[N],b[N],cnt[N],odd,best;
long long k;
void dfs(int x){
    if(x > n){
        best = min(best,odd);
        return;
    }
    for(int t = 0; t < 2; t++){
        int id = a[x];
        if(t == 1){
            if(a[x] == b[x]) continue;
            id = b[x];
        }
        int old = odd;
        cnt[id]++;
        if(cnt[id] % 2 == 1){
            odd++;
        }else{
            odd--;
        }
        dfs(x + 1);
        cnt[id]--;
        odd = old;
    }
}
int main(){
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    best = n;
    dfs(1);
    cout << k - best << '\n';
    return 0;
}

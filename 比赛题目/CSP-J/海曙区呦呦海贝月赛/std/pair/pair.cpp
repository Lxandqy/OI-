#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
int fa[N],sz[N],cnt[N];

int find(int x){
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    long long k;
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++){
        fa[i] = i;
        sz[i] = 1;
    }
    for(int i = 1; i <= n; i++){
        int a,b;
        cin >> a >> b;
        int x = find(a),y = find(b);
        if(x != y){
            if(sz[x] < sz[y]) swap(x,y);
            fa[y] = x;
            sz[x] += sz[y];
            cnt[x] += cnt[y];
        }
        cnt[x]++;
    }
    long long ans = k;
    for(int i = 1; i <= m; i++){
        if(fa[i] == i && cnt[i] % 2 == 1) ans--;
    }
    cout << ans << '\n';
    return 0;
}

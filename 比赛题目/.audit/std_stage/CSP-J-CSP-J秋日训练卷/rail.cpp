#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;

int n,m,p[N];
long long d[N];

int main(){
    freopen("rail.in","r",stdin);
    freopen("rail.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) cin >> p[i];
    for(int i = 1; i < m; i++){
        int l = min(p[i],p[i + 1]);
        int r = max(p[i],p[i + 1]);
        d[l]++;
        d[r]--;
    }
    long long cnt = 0,ans = 0;
    for(int i = 1; i < n; i++){
        long long a,b,c;
        cin >> a >> b >> c;
        cnt += d[i];
        ans += min(cnt * a,c + cnt * b);
    }
    cout << ans << '\n';
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
struct node{
    long long x,y;
}b[2 * N];

bool cmp(node u,node v){
    return u.x > v.x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    long long s;
    cin >> n >> s;
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        long long a,k;
        cin >> a >> k;
        b[++cnt] = {k,a / k};
        b[++cnt] = {a % k,1};
    }
    sort(b + 1,b + cnt + 1,cmp);

    long long ans = 0;
    for(int i = 1; i <= cnt; i++){
        long long take = min(s,b[i].y);
        ans += b[i].x * (b[i].y - take);
        s -= take;
    }
    cout << ans << '\n';
    return 0;
}

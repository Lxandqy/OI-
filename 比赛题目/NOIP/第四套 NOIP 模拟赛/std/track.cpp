#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
struct node{
    long long x,y;
    int id;
}a[N];
int n,t,m,c[N],left_count[N];
long long k,b[N];
bool cmp(node u,node v){
    return u.x < v.x;
}
void add(int x){
    for(int i = x; i <= m; i += i & -i){
        c[i]++;
    }
}
int ask(int x){
    int ans = 0;
    for(int i = x; i > 0; i -= i & -i){
        ans += c[i];
    }
    return ans;
}
long long count(long long d){
    fill(c + 1,c + m + 1,0);
    int p = 1;
    for(int j = 1; j <= n; j++){
        while(p < j && a[p].x <= a[j].x - d){
            add(a[p].id);
            p++;
        }
        int q = upper_bound(b + 1,b + m + 1,a[j].y - d) - b - 1;
        left_count[j] = ask(q);
    }
    fill(c + 1,c + m + 1,0);
    p = n;
    long long ans = 0;
    for(int j = n; j >= 1; j--){
        while(p > j && a[p].x >= a[j].x + d){
            add(a[p].id);
            p--;
        }
        int q = lower_bound(b + 1,b + m + 1,a[j].y + d) - b - 1;
        int right_count = n - p - ask(q);
        ans += 1LL * left_count[j] * right_count;
    }
    return ans;
}
int main(){
    freopen("track.in","r",stdin);
    freopen("track.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> t >> k;
    for(int i = 1; i <= n; i++){
        long long v;
        cin >> a[i].x >> v;
        a[i].y = a[i].x + t * v;
        b[i] = a[i].y;
    }
    sort(a + 1,a + n + 1,cmp);
    sort(b + 1,b + n + 1);
    m = unique(b + 1,b + n + 1) - b - 1;
    for(int i = 1; i <= n; i++){
        a[i].id = lower_bound(b + 1,b + m + 1,a[i].y) - b;
    }
    long long need = 1LL * n * (n - 1) * (n - 2) / 6 - k + 1;
    long long l = 1,r = a[n].x - a[1].x,ans = 0;
    while(l <= r){
        long long mid = (l + r) / 2;
        if(count(mid) >= need){
            ans = mid;
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    cout << ans << '\n';
    return 0;
}

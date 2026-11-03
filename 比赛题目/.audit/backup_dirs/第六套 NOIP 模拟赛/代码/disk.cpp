#include<bits/stdc++.h>
using namespace std;

const int N = 400010;
const long long INF = (1LL << 60);
int n,q;
long long a[N],pre[N],mx[N * 4];

void build(int p,int l,int r){
    if(l == r){
        mx[p] = pre[l];
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2,l,mid);
    build(p * 2 + 1,mid + 1,r);
    mx[p] = max(mx[p * 2],mx[p * 2 + 1]);
}

long long query(int p,int l,int r,int x,int y){
    if(x <= l && r <= y) return mx[p];
    int mid = (l + r) / 2;
    long long ans = -INF;
    if(x <= mid) ans = max(ans,query(p * 2,l,mid,x,y));
    if(y > mid) ans = max(ans,query(p * 2 + 1,mid + 1,r,x,y));
    return ans;
}

int find_first(int p,int l,int r,int x,int y,long long v){
    if(r < x || l > y || mx[p] < v) return -1;
    if(l == r) return l;
    int mid = (l + r) / 2;
    int ans = find_first(p * 2,l,mid,x,y,v);
    if(ans != -1) return ans;
    return find_first(p * 2 + 1,mid + 1,r,x,y,v);
}

int main(){
    freopen("disk.in","r",stdin);
    freopen("disk.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        a[i + n] = a[i];
    }
    for(int i = 1; i <= 2 * n; i++) pre[i] = pre[i - 1] + a[i];
    build(1,1,2 * n);
    while(q--){
        int s;
        long long x;
        cin >> s >> x;
        long long best = query(1,1,2 * n,s,s + n - 1) - pre[s - 1];
        long long turns = 0;
        if(best < x){
            if(pre[n] <= 0){
                cout << -1 << '\n';
                continue;
            }
            turns = (x - best + pre[n] - 1) / pre[n];
        }
        long long need = pre[s - 1] + x - turns * pre[n];
        int pos = find_first(1,1,2 * n,s,s + n - 1,need);
        cout << turns * n + pos - s + 1 << '\n';
    }
    return 0;
}

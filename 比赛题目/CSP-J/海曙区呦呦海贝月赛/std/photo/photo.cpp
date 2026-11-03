#include<bits/stdc++.h>
using namespace std;

const int N = 1000000 + 10;
const int M = 1000 + 10;
struct node{
    int h,id;
}a[N];
int cnt[M];

bool cmp(node u,node v){
    return u.h < v.h;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,s;
    cin >> n >> s;
    int tot = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= s; j++){
            int h;
            cin >> h;
            a[++tot] = {h,i};
        }
    }
    sort(a + 1,a + tot + 1,cmp);

    int l = 1,covered = 0,ans = 1000000000;
    for(int r = 1; r <= tot; r++){
        int id = a[r].id;
        if(cnt[id] == 0) covered++;
        cnt[id]++;
        while(covered == n){
            ans = min(ans,a[r].h - a[l].h);
            id = a[l].id;
            cnt[id]--;
            if(cnt[id] == 0) covered--;
            l++;
        }
    }
    cout << ans << '\n';
    return 0;
}

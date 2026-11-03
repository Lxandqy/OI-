// 合影安排，第3项：窗口计数、扫描所有班判断覆盖；复用至子任务4，保证75分。
// N=ns；时间O(N log N+Nn)，空间O(N+n)。
#include<bits/stdc++.h>
using namespace std;

const int N = 1000000 + 10;
const int M = 1000 + 10;
struct node{
    int h,id;
}a[N];
int cnt[M],n;
bool cmp(node u,node v){
    return u.h < v.h;
}

bool check(){
    for(int i = 1; i <= n; i++){
        if(cnt[i] == 0) return false;
    }
    return true;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int s,tot = 0;
    cin >> n >> s;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= s; j++){
            int h;
            cin >> h;
            a[++tot] = {h,i};
        }
    }
    sort(a + 1,a + tot + 1,cmp);

    int l = 1,ans = 1000000000;
    for(int r = 1; r <= tot; r++){
        cnt[a[r].id]++;
        while(check()){
            ans = min(ans,a[r].h - a[l].h);
            cnt[a[l].id]--;
            l++;
        }
    }
    cout << ans << '\n';
    return 0;
}

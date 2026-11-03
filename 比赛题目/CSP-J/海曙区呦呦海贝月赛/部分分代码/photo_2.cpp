// 合影安排，第2项：枚举左右端点并增量计数；子任务1、2保证33分。
// N=ns；时间O(N log N+N(N+n))，空间O(N+n)。
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

    int ans = 1000000000;
    for(int l = 1; l <= tot; l++){
        for(int i = 1; i <= n; i++) cnt[i] = 0;
        int covered = 0;
        for(int r = l; r <= tot; r++){
            int id = a[r].id;
            if(cnt[id] == 0) covered++;
            cnt[id]++;
            if(covered == n){
                ans = min(ans,a[r].h - a[l].h);
                break;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}

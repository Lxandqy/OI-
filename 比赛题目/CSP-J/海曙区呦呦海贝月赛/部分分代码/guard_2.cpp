// 守护行动，第2项：逐名选最大实际收益；复用至子任务3，保证61分。
// n<=100、s<=10000、a_i<=100；时间O(n(1+min(s,T)))，空间O(n)，T为清空防线所需守卫数。
#include<bits/stdc++.h>
using namespace std;


const int N = 100000 + 10;
long long a[N],k[N];
int main(){
    int n;
    long long s,ans = 0;
    cin >> n >> s;
    for(int i = 1; i <= n; i++){
        cin >> a[i] >> k[i];
        ans += a[i];
    }
    while(s > 0){
        long long gain = 0;
        int pos = 0;
        for(int i = 1; i <= n; i++){
            long long now = min(a[i],k[i]);
            if(now > gain){
                gain = now;
                pos = i;
            }
        }
        if(gain == 0) break;
        a[pos] -= gain;
        ans -= gain;
        s--;
    }
    cout << ans << '\n';
    return 0;
}

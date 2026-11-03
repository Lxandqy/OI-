// 幸运号码，第2项：限制枚举上界并先检查整除；点1至16保证80分。
// M为截短区间长度、D为最大位数；时间O(M+1539D)，空间O(1)。
#include<bits/stdc++.h>
using namespace std;

int calc(long long x){
    int sum = 0;
    while(x > 0){
        int d = x % 10;
        sum += d * d;
        x /= 10;
    }
    return sum;
}

int main(){
    long long k,a,b;
    cin >> k >> a >> b;
    long long r = b;
    if(k <= b / 1539) r = k * 1539;
    int ans = 0;
    for(long long x = a; x <= r; x++){
        if(x % k == 0 && x / k == calc(x)) ans++;
    }
    cout << ans << '\n';
    return 0;
}

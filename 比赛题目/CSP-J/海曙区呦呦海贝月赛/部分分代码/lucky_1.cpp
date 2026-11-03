// 幸运号码，第1项：区间逐个枚举；点1至8保证40分；时间O(LD)，空间O(1)。
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
    int ans = 0;
    for(long long x = a; x <= b; x++){
        if(x % k == 0 && x / k == calc(x)) ans++;
    }
    cout << ans << '\n';
    return 0;
}

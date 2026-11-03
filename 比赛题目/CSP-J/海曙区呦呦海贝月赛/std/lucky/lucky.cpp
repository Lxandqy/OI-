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
    int d = 0;
    for(long long x = b; x > 0; x /= 10) d++;

    int ans = 0;
    for(int t = 1; t <= 81 * d; t++){
        if(t > b / k) break;
        long long x = k * t;
        if(x >= a && calc(x) == t) ans++;
    }
    cout << ans << '\n';
    return 0;
}

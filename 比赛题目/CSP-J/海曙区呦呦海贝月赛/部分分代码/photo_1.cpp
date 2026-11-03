// 合影安排，第1项：两个班排序双指针；子任务1保证11分；时间O(s log s)，空间O(s)。
#include<bits/stdc++.h>
using namespace std;


const int N = 1000 + 10;
int a[N],b[N];
int main(){
    int n,s;
    cin >> n >> s;
    for(int i = 1; i <= s; i++) cin >> a[i];
    for(int i = 1; i <= s; i++) cin >> b[i];
    sort(a + 1,a + s + 1);
    sort(b + 1,b + s + 1);
    int i = 1,j = 1,ans = 1000000000;
    while(i <= s && j <= s){
        ans = min(ans,abs(a[i] - b[j]));
        if(a[i] < b[j]){
            i++;
        }else{
            j++;
        }
    }
    cout << ans << '\n';
    return 0;
}

// 部分分 3
/*
T3 melody; join left/right increasing runs. Valid for k <= 1.
Guaranteed: points 4-10 (35). Time O(n); space O(n).
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,k;
int a[N],l[N],r[N];
int main(){
	freopen("melody.in","r",stdin);
	freopen("melody.out","w",stdout);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	// l[i]：以 i 结尾的最长上升段；r[i]：以 i 开头的最长上升段
	for(int i = 1; i <= n; i++){
		if(i > 1 && a[i - 1] < a[i]) l[i] = l[i - 1] + 1;
		else l[i] = 1;
	}
	for(int i = n; i >= 1; i--){
		if(i < n && a[i] < a[i + 1]) r[i] = r[i + 1] + 1;
		else r[i] = 1;
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = max(ans,l[i]);
	if(k >= 1){
		// 删掉第 i 个，把 i-1 结尾的段和 i+1 开头的段接起来
		for(int i = 2; i < n; i++){
			if(a[i - 1] < a[i + 1]) ans = max(ans,l[i - 1] + r[i + 1]);
		}
	}
	cout << ans << endl;
	return 0;
}

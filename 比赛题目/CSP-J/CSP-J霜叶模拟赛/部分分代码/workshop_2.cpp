// 工坊互助：部分分 2，枚举完工时间，保证测试点 1、5~8（25 分）。
// n<=1000 且 a_i<=1000，或 n=1；一般时间 O(n max a_i)，空间 O(n)。
// n=1 时下界就是答案，只需一次判定。
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n;
long long a[N],b[N],c[N];

bool check(long long t){
	long long need = 0,help = 0;
	for(int i = 1; i <= n; i++){
		if(a[i] > t) need += a[i] - t;
		else if(t > a[i] + c[i]) help += (t - a[i] - c[i]) / b[i];
	}
	return help >= need;
}

int main(){
	freopen("workshop.in","r",stdin);
	freopen("workshop.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	long long sum = 0;
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> b[i] >> c[i];
		sum += a[i];
	}
	long long t = (sum + n - 1) / n;
	while(!check(t)) t++;
	cout << t << '\n';
	return 0;
}

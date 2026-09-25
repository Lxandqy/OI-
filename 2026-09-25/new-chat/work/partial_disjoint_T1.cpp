#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
long long prefix[N];
int que[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,b[4],x;
	cin >> n >> b[0] >> b[1] >> b[2] >> b[3];
	for(int i = 1; i <= n; i++){
		cin >> x;
		prefix[i] = prefix[i - 1] + x;
	}
	int maxLength = n - 4,front = 1,back = 0;
	long long answer = -(1LL << 60);
	for(int r = 1; r <= n; r++){
		int j = r - 1;
		while(front <= back && prefix[que[back]] >= prefix[j]) back--;
		que[++back] = j;
		while(front <= back && que[front] < r - maxLength) front++;
		if(front <= back) answer = max(answer,prefix[r] - prefix[que[front]]);
	}
	cout << answer << '\n';
	return 0;
}

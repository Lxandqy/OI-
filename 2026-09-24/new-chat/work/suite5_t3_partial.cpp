#include<bits/stdc++.h>
using namespace std;

const int N = 100010;
int len[N];
long long ways[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--){
		int L,R;
		cin >> L >> R;
		for(int x = L; x <= R; x++){
			len[x] = 1;
			ways[x] = 1;
			for(int y = L; y < x; y++){
				if(x % y != 0) continue;
				int candidate = len[y] + 1;
				if(candidate > len[x]){
					len[x] = candidate;
					ways[x] = ways[y];
				}else if(candidate == len[x]){
					ways[x] += ways[y];
				}
			}
		}
		int bestLen = 0;
		long long count = 0;
		for(int x = L; x <= R; x++){
			if(len[x] > bestLen){
				bestLen = len[x];
				count = ways[x];
			}else if(len[x] == bestLen){
				count += ways[x];
			}
		}
		cout << bestLen << ' ' << count << '\n';
	}
	return 0;
}

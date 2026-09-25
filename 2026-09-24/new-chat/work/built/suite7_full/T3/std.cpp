#include<bits/stdc++.h>
using namespace std;

string a[11], b[11];
int n;

bool isLetter(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool rootNameOK(const string &s){
	int i = 0;
	while(i < (int)s.size() && isLetter(s[i])){
		i++;
	}
	if(i == 0 || i == (int)s.size()){
		return false;
	}
	while(i < (int)s.size()){
		if(s[i] < '0' || s[i] > '9'){
			return false;
		}
		i++;
	}
	return true;
}

bool check(){
	if(n != 8){
		return false;
	}
	string root = "";
	for(int i = 1; i <= n; i++){
		bool hasParent = false;
		for(int j = 1; j <= n; j++){
			if(a[i] == b[j]){
				hasParent = true;
			}
		}
		if(!hasParent){
			if(root != "" && root != a[i]){
				return false;
			}
			root = a[i];
		}
	}
	if(!rootNameOK(root)){
		return false;
	}
	int tasks = 0;
	for(int i = 1; i <= n; i++){
		if(a[i] != root){
			continue;
		}
		tasks++;
		string task = b[i];
		for(int j = 0; j < (int)task.size(); j++){
			if(!isLetter(task[j])){
				return false;
			}
		}
		int files = 0;
		for(int j = 1; j <= n; j++){
			if(a[j] == task){
				files++;
				if(b[j] != task + ".cpp"){
					return false;
				}
			}
		}
		if(files != 1){
			return false;
		}
	}
	// 四条根边 + 四条代码文件边已经占满全部八条关系。
	return tasks == 4;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> a[i] >> b[i];
		}
		if(check()){
			cout << "yes\n";
		}else{
			cout << "no\n";
		}
	}
	return 0;
}

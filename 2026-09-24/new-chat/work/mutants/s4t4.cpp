#include<bits/stdc++.h>
using namespace std;

struct Big{
	static const int BASE = 10000;
	vector<int> d;
	Big(int x = 0){
		if(x > 0) d.push_back(x);
	}
	void addDigit(int x){
		int carry = x;
		for(int i = 0; i < (int)d.size(); i++){
			int value = d[i] * 10 + carry;
			d[i] = value % BASE;
			carry = value / BASE;
		}
		if(carry > 0) d.push_back(carry);
	}
	void add(const Big &b){
		if(d.size() < b.d.size()) d.resize(b.d.size(),0);
		int carry = 0;
		for(int i = 0; i < (int)d.size(); i++){
			int value = d[i] + carry;
			if(i < (int)b.d.size()) value += b.d[i];
			d[i] = value % BASE;
			carry = value / BASE;
		}
		if(carry > 0) d.push_back(carry);
	}
	Big multiply(const Big &b) const{
		Big result;
		if(d.empty() || b.d.empty()) return result;
		result.d.resize(d.size() + b.d.size() + 1,0);
		for(int i = 0; i < (int)d.size(); i++){
			long long carry = 0;
			for(int j = 0; j < (int)b.d.size() || carry > 0; j++){
				long long value = result.d[i + j] + carry;
				if(j < (int)b.d.size()) value += 1LL * d[i] * b.d[j];
				result.d[i + j] = value % BASE;
				carry = value / BASE;
			}
		}
		while(!result.d.empty() && result.d.back() == 0) result.d.pop_back();
		return result;
	}
	void print() const{
		if(d.empty()){
			cout << 0;
			return;
		}
		cout << d.back();
		for(int i = (int)d.size() - 2; i >= 0; i--){
			cout << setw(4) << setfill('0') << d[i];
		}
	}
};

int main(){
	freopen("eval.in","r",stdin);
	freopen("eval.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s;
	cin >> s;
	Big product(1),sum,number;
	for(int i = 0; i < (int)s.size(); i++){
		if(s[i] >= '0' && s[i] <= '9'){
			number.addDigit(s[i] - '0');
		}else if(s[i] == '*'){
			sum.add(number);
			number = Big();
		}else{
			sum.add(number);
			product = product.multiply(sum);
			sum = Big();
			number = Big();
		}
	}
	sum.add(number);
	product = product.multiply(sum);
	product.print();
	cout << '\n';
	return 0;
}

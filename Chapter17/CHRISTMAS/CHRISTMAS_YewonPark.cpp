//yewon
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int buy(const vector<int>& psum, int k) {
	const int MOD = 20091101;
	int ret = 0;
	vector<long long> count(k, 0);
	for (int i = 0; i < psum.size(); i++)
		count[psum[i]]++;
	for (int i = 0; i < k; i++)
		if (count[i] >= 2)
			ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
	return ret;
}

int maxBuy(const vector<int>& psum, int k) {
	vector<int> ret(psum.size(), 0);

	vector<int> prev(k, -1);
	for (int i = 0; i < psum.size(); i++) {
		if (i > 0)
			ret[i] = ret[i - 1];
		else
			ret[i] = 0;
		int loc = prev[psum[i]];
		if (loc != -1)
			ret[i] = max(ret[i], ret[loc] + 1);
		prev[psum[i]] = i;
	}
	return ret.back();
}

int main() {

	int t, n, k;
	cin >> t;
	while (t--) {
		cin >> n >> k;
		vector<int> sum = vector<int>();
		int temp;
		cin >> temp;
		sum.push_back(temp);
		for (int i = 1; i < n; i++) {
			cin >> temp;
			sum.push_back(sum[i-1]+temp);
		}
		//cout << buy(sum, k);
		cout << maxBuy(sum, k);
	}

	return 0;
}

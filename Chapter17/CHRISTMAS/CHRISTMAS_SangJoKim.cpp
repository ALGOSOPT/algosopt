#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;


#define MOD 20091101

int n, k;
vector<int> dollspSum;
int main() {

	freopen("input.txt", "r", stdin);

	int TC; scanf("%d", &TC);

	while (TC--) {

		scanf("%d%d", &n, &k);
		dollspSum.clear();
		dollspSum.resize(n, 0);
		scanf("%d", &dollspSum[0]);
		
		for (int i = 1; i < n; i++) {
			
			scanf("%d", &dollspSum[i]);
			dollspSum[i] += dollspSum[i - 1];
		}
		for (int i = 0; i < n; i++) {
			dollspSum[i] %= k;
		}

			
		int ret = 0;

		for (int i = 0; i < n; i++) {
			ret += (dollspSum[i] == 0);
		}

		vector<int> f(k, 0);

		for (int i = 0; i < n; i++) {
			f[dollspSum[i]]++;
		}

		for (int i = 0; i < k; i++) {
			ret += f[i] * (f[i] - 1) / 2;
			ret %= MOD;
		}

		cout << ret << " " << endl;

	}



	return 0;
}
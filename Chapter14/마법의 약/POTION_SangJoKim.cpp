#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;



int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p % q);
}



int main() {
	freopen("input.txt", "r", stdin);

	int TC; cin >> TC;

	while (TC--) {
		int n; cin >> n;

		int r[1001]; int p[1001];

		for (int i = 0; i < n; i++) {
			cin >> r[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> p[i];
		}

		//cout << n << endl;

		if (n == 1) {
			int ret = (r[0] > p[0]) ? r[0] - p[0] : 0;
			cout << ret << endl;
			continue;
		}

		double ratio = 0;

		for (int i = 0; i < n; i++) {
			ratio = max(ratio, (double)p[i] / r[i]);
		}

		if (ratio <= 1) {
			for (int i = 0; i < n; i++) {
				cout << r[i] - p[i] << " ";
			}
			cout << endl;
			continue;
		}
		else {
			
			int GCD = gcd(r[0], r[1]);
			for (int i = 2; i < n; i++) {
				GCD = gcd(GCD, r[i]);
			}


			for (int i = 0; i < n; i++) {
				r[i] /= GCD;
			}

			ratio = 0.0;
			int what = -1;

			for (int i = 0; i < n; i++) {
				if (ratio < (double)p[i] / r[i]) {
					ratio = (double)p[i] / r[i];
					what = i;
				}
			}
			//cout << what << endl;

			//나누어 떨어지면
			if (p[what] % r[what] == 0) {
				for (int i = 0; i < n; i++) {
					if (i == what) {
						cout << 0 << " ";
					}
					else {
						cout << ratio * r[i] - p[i] << " ";
					}
				}
				cout << endl;
				continue;
			}
			//나누어 떨어지지 않으면
			else {
				ratio = (p[what] + r[what] - p[what] % r[what])/ r[what];

				for (int i = 0; i < n; i++) {
					cout << ratio * r[i] - p[i] << " ";
				}
				cout << endl;
				continue;
			}
		}
	}





	return 0;
}
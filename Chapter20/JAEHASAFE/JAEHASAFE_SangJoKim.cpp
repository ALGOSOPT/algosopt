#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int n;
int absSub(int a, int b) {
	return a > b ? a - b : b - a;
}
vector<int> getPi(const string N) {
	int matched = 0, m = N.size();
	vector<int> pi(m, 0);

	for (int i = 1; i < m; i++) {

		while (matched > 0 && N[i] != N[matched])
			matched = pi[matched - 1];

		if (N[i] == N[matched]) {
			pi[i] = ++matched;
		}
	}
	return pi;
}

int kmp(const string H, const string N) {
	int n = H.size(), m = N.size();

	int matched = 0;

	vector<int> pi = getPi(N);


	for (int i = 0; i < n; i++) {
		while (matched > 0 && H[i] != N[matched])
			matched = pi[matched - 1];

		if (H[i] == N[matched]) {
			matched++;
			if (matched == m) {
				return i - m + 1;
			}
		}
	}
	return 0;
}
int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int TC;
	cin >> TC;
	while (TC--) {


		cin >> n;

		vector<string> strongBox(n);
		string ref;
		cin >> ref;
		ref += ref;
		for (int i = 0; i < n; i++) {
			cin >> strongBox[i];
		}

		vector<int> posi;
		posi.push_back(0);
		for (int i = 0; i < n; i++) {
			posi.push_back(kmp(ref, strongBox[i]));

		}
		int ret = 0; int size = strongBox[0].size();

		for (int i = 0; i < n; i++) {
			//홀수 작아져야함
			if (i % 2) {
				if (posi[i] > posi[i + 1]) {
					ret += size - absSub(posi[i + 1], posi[i]);
				}
				else {
					ret += absSub(posi[i], posi[i + 1]);
				}
			}
			//짝수 커져야함
			else {
				if (posi[i] > posi[i + 1]) {
					ret += absSub(posi[i + 1], posi[i]);
				}
				else {
					ret += size - absSub(posi[i + 1], posi[i]);
				}
			}
		}
		cout << ret << endl;
	}

	return 0;
}
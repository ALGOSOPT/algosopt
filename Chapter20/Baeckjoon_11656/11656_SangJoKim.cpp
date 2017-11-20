#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAX = 1001;
string input;


int N, d, group[MAX];

bool cmp(int i, int j) {

	if (group[i] != group[j]) return group[i] < group[j];

	i += d;
	j += d;
	return (i < N && j < N) ? (group[i] < group[j]) : (i > j);
}

vector<int> getSuffixArray() {

	vector<int> sa(N);

	for (int i = 0; i < N; i++) {

		sa[i] = i;
		group[i] = input[i];
	}

	for (d = 1; ; d *= 2) {
		sort(sa.begin(), sa.end(), cmp);

		vector<int> newGroup(N);

		for (int i = 0; i < N - 1; i++) 
			newGroup[i + 1] = newGroup[i] + cmp(sa[i], sa[i + 1]);

		for (int i = 0; i < N; i++) 
			group[sa[i]] = newGroup[i];

		if (newGroup[N - 1] == N - 1) break;
	}
	return sa;
}

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> input;
	N = input.size();
	vector<int> sa = getSuffixArray();


	for (int i = 0; i < sa.size(); i++) {
		for (int j = sa[i]; j < N; j++)
			cout << input[j];
		cout << endl;
	}

}


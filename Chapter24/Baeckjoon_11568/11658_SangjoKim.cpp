#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define LSB(i) i & -i;

int n, m;
vector<vector<long long> > fenwick;
vector<vector<int> > arr;



void update(int y, int x, int upValue) {

	while (x <= n) {
		fenwick[y][x] += upValue;
		x += LSB(x);
	}
}

long long sum(int y, int x) {
	long long ret = 0;
	while (x > 0) {
		ret += fenwick[y][x];
		x -= LSB(x);
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);


	fenwick = vector<vector<long long> >(n + 1, vector<long long>(n + 1, 0));
	arr = vector<vector<int> >(n + 1, vector<int>(n + 1, 0));

	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			scanf("%d", &arr[y][x]);
			update(y, x, arr[y][x]);
		}
	}

	for (int i = 0; i < m; i++) {
		int w; scanf("%d", &w);
		//update
		if (w == 0) {
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			update(y, x, c - arr[y][x]);
			arr[y][x] = c;
		}
		//sum
		else {

			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);

			long long ret = 0;
			for (int y = y1; y <= y2; y++) {
				ret += sum(y, x2) - sum(y, x1 - 1);
			}
			printf("%lld\n", ret);
		}
	}

	return 0;
}
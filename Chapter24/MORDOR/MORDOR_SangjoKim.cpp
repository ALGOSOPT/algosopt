#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAXN = 100000;
int n, q;

int maxTree[4 * MAXN + 1], minTree[4 * MAXN + 1];
int h[MAXN + 1];

void init(int node, int nodeLeft, int nodeRight) {
	if (nodeLeft == nodeRight) {
		maxTree[node] = h[nodeLeft];
		minTree[node] = h[nodeRight];
		return;
	}

	int mid = (nodeLeft + nodeRight) / 2;

	init(node * 2 + 1, nodeLeft, mid); init(node * 2 + 2, mid + 1, nodeRight);

	maxTree[node] = max(maxTree[node * 2 + 1], maxTree[node * 2 + 2]);
	minTree[node] = min(minTree[node * 2 + 1], minTree[node * 2 + 2]);
}

int maxQuery(int node, int nodeLeft, int nodeRight, int left, int right) {
	if (left > nodeRight || right < nodeLeft)
		return 0;

	if (nodeLeft >= left && nodeRight <= right) {
		return maxTree[node];
	}

	int mid = (nodeLeft + nodeRight) / 2;

	return max(maxQuery(node * 2 + 1, nodeLeft, mid, left, right), maxQuery(node * 2 + 2, mid + 1, nodeRight, left, right));

}
int minQuery(int node, int nodeLeft, int nodeRight, int left, int right) {
	if (left > nodeRight || right < nodeLeft)
		return 0x3f3f3f3f;

	if (nodeLeft >= left && nodeRight <= right) {
		return minTree[node];
	}

	int mid = (nodeLeft + nodeRight) / 2;

	return min(minQuery(node * 2 + 1, nodeLeft, mid, left, right), minQuery(node * 2 + 2, mid + 1, nodeRight, left, right));

}


int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int TC; scanf("%d", &TC);
	while (TC--){
		memset(maxTree, 0, sizeof(maxTree)); memset(minTree, 0, sizeof(minTree));
		scanf("%d%d", &n, &q);

		for (int i = 0; i < n; i++) {
			scanf("%d", &h[i]);
		}
		init(0, 0, n - 1);

		for (int i = 0; i < q; i++) {
			int a, b; scanf("%d%d", &a, &b);
			int M = maxQuery(0, 0, n - 1, a, b);
			int m = minQuery(0, 0, n - 1, a, b);
			cout << M - m<< endl;
		}
	}


	return 0;
}
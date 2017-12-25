#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;


int n, m;
int arr[100001], segTree[400001];
int lazy[400001];


void propagation(int node, int nodeLeft, int nodeRight) {

	if (lazy[node] == 0) return;

	if (nodeLeft != nodeRight) {
		lazy[node * 2 + 1] += lazy[node];
		lazy[node * 2 + 2] += lazy[node];
	}
	if (lazy[node] % 2)
		segTree[node] = (nodeRight - nodeLeft + 1) - segTree[node];
	lazy[node] = 0;

}

void turnOnOFF(int node, int nodeLeft, int nodeRight, int start, int end) {
	propagation(node, nodeLeft, nodeRight);

	if (nodeLeft > end || nodeRight < start) return;
	if (start <= nodeLeft && nodeRight <= end) {
		lazy[node] = 1;
		propagation(node, nodeLeft, nodeRight);
		return;
	}
	int mid = (nodeLeft + nodeRight) >> 1;
	turnOnOFF(node * 2 + 1, nodeLeft, mid, start, end);
	turnOnOFF(node * 2 + 2, mid + 1, nodeRight, start, end);

	segTree[node] = segTree[node * 2 + 1] + segTree[node * 2 + 2];
}


int sum(int node, int nodeLeft, int nodeRight, int start, int end) {

	propagation(node, nodeLeft, nodeRight);

	if (end < nodeLeft || start > nodeRight) return 0;
	if (start <= nodeLeft && nodeRight <= end) return segTree[node];

	int mid = (nodeLeft + nodeRight) >> 1;

	return sum(node * 2 + 1, nodeLeft, mid, start, end)
		+ sum(node * 2 + 2, mid + 1, nodeRight, start, end);

}
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int o, s, t;
		scanf("%d%d%d", &o, &s, &t);
		
		if (o == 0) {
			//반전
			turnOnOFF(0, 0, n - 1, s - 1, t - 1);
		}
		else {
			//구하기
			printf("%d\n", sum(0, 0, n - 1, s - 1, t - 1));
		}
	}


	return 0;
}
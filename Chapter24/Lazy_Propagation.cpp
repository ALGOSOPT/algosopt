#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAX = 1000001;

ll arr[MAX], segTree[4 * MAX], lazy[4 * MAX];

int n, m, k;

void init(int node, int nodeLeft, int nodeRight) {
	if (nodeLeft == nodeRight) {
		segTree[node] = arr[nodeLeft];
		return;
	}
	int mid = (nodeLeft + nodeRight) >> 1;

	init(node * 2 + 1, nodeLeft, mid); init(node * 2 + 2, mid + 1, nodeRight);
	
	segTree[node] = segTree[node * 2 + 1] + segTree[node * 2 + 2];
}

// node 값의 lazy를 propagate
void propagate(int node, int nodeLeft, int nodeRight) {
	
	//없으면 return
	if (lazy[node] == 0) return;
	
	//leaf 노드가 아니면 자식들에게 lazy를 미룸
	if (nodeLeft != nodeRight) {
		lazy[node * 2 + 1] += lazy[node];
		lazy[node * 2 + 2] += lazy[node];
	}

	//자신의 lazy값을 segTree에 반영
	segTree[node] += lazy[node] * (nodeRight - nodeLeft + 1);
	lazy[node] = 0;
}


ll sum(int node, int nodeLeft, int nodeRight, int left, int right) {
	//lazy값을 갱신한다.
	propagate(node, nodeLeft, nodeRight);

	if (right < nodeLeft || left > nodeRight) return 0;
	if (left <= nodeLeft && nodeRight <= right) return segTree[node];

	int mid = (nodeLeft + nodeRight) >> 1;
	
	return sum(node * 2 + 1, nodeLeft, mid, left, right)
		+ sum(node * 2 + 2, mid + 1, nodeRight, left, right);
}


void update(int node, int nodeLeft, int nodeRight, int left, int right, int addValue) {

	//일단 propagate
	propagate(node, nodeLeft, nodeRight);

	if (right < nodeLeft || left > nodeRight) return;
	//노드의 범위가 update의 범위에 완전히 포함되면
	if (left <= nodeLeft && nodeRight <= right) {

		lazy[node] += addValue;
		propagate(node, nodeLeft, nodeRight);
		return;
	}

	int mid = (nodeLeft + nodeRight) >> 1;
	update(node * 2 + 1, nodeLeft, mid, left, right, addValue);
	update(node * 2 + 2, mid + 1, nodeRight, left, right, addValue);
	
	//자식들로부터 다시 값 update
	segTree[node] = segTree[node * 2 + 1] + segTree[node * 2 + 2];
}

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d%d%d", &n, &m, &k);

	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

	init(0, 0, n - 1);
	for (int i = 0; i < m + k; i++) {
		int a, b, c, d;
		scanf("%d", &a);
		if (a == 1) {
			scanf("%d%d%d", &b, &c, &d);
			//update
			update(0, 0, n - 1, b - 1, c - 1, d);
		}
		else {
			scanf("%d%d", &b, &c);
			//sum
			cout << sum(0, 0, n - 1, b - 1, c - 1) << endl;
		}
	}


	return 0;
}
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int n, m;
int arr[100001], tree[400001];
int lazy[400001];

void propagate(int node, int nodeLeft, int nodeRight) {

	if (lazy[node] == 0) return;

	if (nodeLeft != nodeRight) {
		lazy[node * 2 + 1] += lazy[node];
		lazy[node * 2 + 2] += lazy[node];
	}
	if (lazy[node] % 2)
		tree[node] = (nodeRight - nodeLeft + 1) - tree[node];
	lazy[node] = 0;
}

void change(int node, int nodeLeft, int nodeRight, int start, int end) {
	propagate(node, nodeLeft, nodeRight);

	if (nodeLeft > end || nodeRight < start) 
		return;
	if (start <= nodeLeft && nodeRight <= end) {
		lazy[node] = 1;
		propagate(node, nodeLeft, nodeRight);
		return;
	}
	int mid = (nodeLeft + nodeRight) >> 1;
	change(node * 2 + 1, nodeLeft, mid, start, end);
	change(node * 2 + 2, mid + 1, nodeRight, start, end);

	tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
}

int sum(int node, int nodeLeft, int nodeRight, int left, int right) {

	propagate(node, nodeLeft, nodeRight);

	if (right < nodeLeft || left > nodeRight) 
		return 0;
	if (left <= nodeLeft && nodeRight <= right) 
		return tree[node];

	int mid = (nodeLeft + nodeRight) >> 1;

	return sum(node * 2 + 1, nodeLeft, mid, left, right)
		+ sum(node * 2 + 2, mid + 1, nodeRight, left, right);

}

int main() {
	
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int o, s, t;
		cin >> o >> s >> t;
		
		if (o == 0) {
			change(0, 0, n - 1, s - 1, t - 1);
		else 
			cout << sum(0, 0, n - 1, s - 1, t - 1) << "\n";
	}

	return 0;
}

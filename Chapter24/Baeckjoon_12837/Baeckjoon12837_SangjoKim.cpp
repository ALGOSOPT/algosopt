#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using namespace std;

typedef long long int ll;

const int MAX = 1000000;

int n, q;

ll seg[3 * MAX];
void update(int node, int nodeLeft, int nodeRight, int idx, int value) {

	//1. 밖에 있는지
	if (idx < nodeLeft || idx > nodeRight)
		return;

	seg[node] += value;

	int mid = (nodeLeft + nodeRight) / 2;
	if (nodeLeft != nodeRight) {
		update(node * 2 + 1, nodeLeft, mid, idx, value);
		update(node * 2 + 2, mid + 1, nodeRight, idx, value);
	}
}
ll query(int node, int nodeLeft, int nodeRight, int left, int right) {
	if (right < nodeLeft || left > nodeRight)
		return 0;

	if (left <= nodeLeft && right >= nodeRight)
		return seg[node];

	int mid = (nodeLeft + nodeRight) /2;

	return query(node * 2 + 1, nodeLeft, mid, left, right)
		+ query(node * 2 + 2, mid + 1, nodeRight, left, right);

}

int main() {

	freopen("intput.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n >> q;
	memset(seg, 0, sizeof(seg));
	for (int i = 0; i < q; i++) {
		int cmd, p, x;
		cin >> cmd >> p >> x;
		if (cmd == 1) {
			//update
			update(1, 1, n, p, x);

		}
		else {
			//query
			cout << query(1, 1, n, p, x) << endl;
		}
	}
	

	return 0;
}
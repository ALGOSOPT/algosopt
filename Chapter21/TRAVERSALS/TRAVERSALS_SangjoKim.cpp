#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
int n;

vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}

void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {

	const int N = preorder.size();

	if (preorder.empty()) return;

	const int root = preorder[0];

	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();

	const int R = N - 1 - L;
	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));

	cout << root << " ";
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int TC; cin >> TC;
	while (TC--) {
		cin >> n;

		vector<int> preOrder(n);
		vector<int> inOrder(n);
		for (int i = 0; i < n; i++) {
			cin >> preOrder[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> inOrder[i];
		}


		printPostOrder(preOrder, inOrder);
		cout << endl;
	}

	return 0;
}
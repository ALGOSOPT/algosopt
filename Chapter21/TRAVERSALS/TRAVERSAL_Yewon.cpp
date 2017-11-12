#include<iostream>
#include<cstdio>

using namespace std;

void maketree(int * pre, int * in, int * tree, int * ed, int i, int t) {
	
	//전위순회에서 노드를 찾는다
	int node = tree[t] = pre[i];
	ed[i] = 1;
	
	//중위순회에서 노드를 찾아서 왼쪽 트리와 오른쪽 트리로 나눈다
	int j;
	for (j = 0; j<100; j++)
		if (in[j] == node)
			break;
	//j에는 왼쪽 서브트리에 있는 노드의 수가 저장되어 있음
	//왼쪽 서브트리의 루트노드를 찾아서 저장
	if (ed[i + 1] == 0)
		maketree(pre, in, tree, ed, i + 1, 2 * t);
	//오른쪽 서브트리의 루트노드를 찾아서 저장
	if (ed[j + 1] == 0)
		maketree(pre, in, tree, ed, j + 1, 2 * t + 1);
}

void postorder(int * tree, int index) {
	//1. 왼쪽
	if (tree[2 * index] != 0)
		postorder(tree, 2 * index);
	//2. 오른쪽
	if (tree[2 * index + 1] != 0)
		postorder(tree, 2 * index + 1);
	//3. 노드
	cout << tree[index];
}

int main() {

	int c;
	cin >> c;

	while (c--) {
		//입력
		int n;
		cin >> n;

		int pre[100];
		int in[100];
		int tree[300];
		int ed[100] = { 0, };

		for (int i = 0; i<n; i++)
			cin >> pre[i];
		for (int i = 0; i<n; i++)
			cin >> in[i];

		maketree(pre, in, tree, ed, 0, 1);

		postorder(tree, 1);
		cout << "\n";
	}
	return 0;
}

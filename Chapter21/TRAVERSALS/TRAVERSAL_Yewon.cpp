#include<iostream>
#include<cstdio>

using namespace std;

void maketree(int * pre, int * in, int * tree, int * ed, int i, int t) {
	
	//������ȸ���� ��带 ã�´�
	int node = tree[t] = pre[i];
	ed[i] = 1;
	
	//������ȸ���� ��带 ã�Ƽ� ���� Ʈ���� ������ Ʈ���� ������
	int j;
	for (j = 0; j<100; j++)
		if (in[j] == node)
			break;
	//j���� ���� ����Ʈ���� �ִ� ����� ���� ����Ǿ� ����
	//���� ����Ʈ���� ��Ʈ��带 ã�Ƽ� ����
	if (ed[i + 1] == 0)
		maketree(pre, in, tree, ed, i + 1, 2 * t);
	//������ ����Ʈ���� ��Ʈ��带 ã�Ƽ� ����
	if (ed[j + 1] == 0)
		maketree(pre, in, tree, ed, j + 1, 2 * t + 1);
}

void postorder(int * tree, int index) {
	//1. ����
	if (tree[2 * index] != 0)
		postorder(tree, 2 * index);
	//2. ������
	if (tree[2 * index + 1] != 0)
		postorder(tree, 2 * index + 1);
	//3. ���
	cout << tree[index];
}

int main() {

	int c;
	cin >> c;

	while (c--) {
		//�Է�
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

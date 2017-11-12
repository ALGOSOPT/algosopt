#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>

using namespace std;

int x[100], y[100], r[100];
int n;

/*
//�ϴ� �̷��� �����ϴ� ���� �� �ʿ�����?���� ��������
//���� x, y, radius�� �� �����ϴ� ���� �߿��ϳ�??NoNo!
struct Circle {
	int x, y;
	int r;
};
*/

//����ü�� Ʈ�� ����
struct TreeNode {
	int label;
	//TreeNode * parent;
	vector<TreeNode *> children;
};

//**�ؾ��ϴ� ���� �������� ����ȭ ���Ѿ��Ѵ�!
bool isChild(int parent, int child) {
	//�ҸӴ� ���� ���� �ȵ�. ���� �ڽ� ���踸 ��
	
	//1. parent�� child�� �����Ѵ�
	if (!encloses(parent, child))
		return false;
	//2. parent�� �ڽ��� ���� �����Ѵ�
	//kick : �̰� ������ �� Ȯ���ؾ���. � ������ ������ �𸣱� ������
	for (int i = 0; i < n; i++) {
		if (i != parent && i != child && encloses(parent, i) && encloses(i, child))
			return false;
	}

	return true;
}

bool encloses(int parent, int child) {
	//parent�� chile�� �����ϴ� ��� true ��ȯ
	int l = (x[parent] - x[child])*(x[parent] - x[child]) + (y[parent] - y[child])*(y[parent] - y[child]);
	if (r[parent] > r[child] && l < (r[parent] - r[child])*(r[parent] - r[child]))
		return true;
	return false;
}

//**�ڽĸ� �����ϸ� �ȴ�!(x, y, r�� ������ ������ �ʿ� ����)
TreeNode * makeTree(int root) {
	TreeNode * ret = new TreeNode();

	//tree�� �ڽ� �߰�
	for (int i = 0; i < n; i++) {
		if (isChild(root, i))
			ret->children.push_back(makeTree(i));
	}
	return ret;
}

int longest;
//root�� ��Ʈ�� �ϴ� ����Ʈ���� ��ȯ�Ѵ�
int height(TreeNode * root) {
	vector<int> heights;
	if (root->children.size() == 0)//�ڽ��� ������ 0 ��ȯ
		return 0;
	//�� �ڽ��� ��Ʈ�� �ϴ� ����Ʈ���� ���̸� ����Ѵ�
	for (int i = 0; i<root->children.size(); ++i)
		heights.push_back(height(root->children[i]));
	sort(heights.begin(), heights.end());
	//���� �� ��-�ٰ�� ���
	longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	//���� �� ����Ʈ�� ���� ���
	return heights.back() + 1;
}


int main() {

	int c;
	cin >> c;
	
	while (c--) {
		cin >> n;

		int temp1, temp2, temp3;
		for (int i = 0; i < n; i++) {
			cin >> temp1 >> temp2 >> temp3;
			x[i] = temp1;
			y[i] = temp2;
			r[i] = temp3;
		}

		TreeNode * tree = makeTree(0);
		longest = 0;
		int h = height(tree);

		printf("%d\n", max(longest, h));		
	}
}
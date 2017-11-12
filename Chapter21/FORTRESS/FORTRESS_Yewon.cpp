#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>

using namespace std;

int x[100], y[100], r[100];
int n;

/*
//일단 이렇게 구현하는 것이 꼭 필요한지?먼저 생각하자
//지금 x, y, radius를 다 저장하는 것이 중요하나??NoNo!
struct Circle {
	int x, y;
	int r;
};
*/

//구조체로 트리 구현
struct TreeNode {
	int label;
	//TreeNode * parent;
	vector<TreeNode *> children;
};

//**해야하는 일을 과정으로 세분화 시켜야한다!
bool isChild(int parent, int child) {
	//할머니 손주 관계 안됨. 엄마 자식 관계만 됨
	
	//1. parent가 child를 포함한다
	if (!encloses(parent, child))
		return false;
	//2. parent가 자식을 직접 포함한다
	//kick : 이거 일일히 다 확인해야함. 어떤 순서로 들어올지 모르기 때문에
	for (int i = 0; i < n; i++) {
		if (i != parent && i != child && encloses(parent, i) && encloses(i, child))
			return false;
	}

	return true;
}

bool encloses(int parent, int child) {
	//parent가 chile를 포함하는 경우 true 반환
	int l = (x[parent] - x[child])*(x[parent] - x[child]) + (y[parent] - y[child])*(y[parent] - y[child]);
	if (r[parent] > r[child] && l < (r[parent] - r[child])*(r[parent] - r[child]))
		return true;
	return false;
}

//**자식만 저장하면 된다!(x, y, r을 일일히 저장할 필요 없음)
TreeNode * makeTree(int root) {
	TreeNode * ret = new TreeNode();

	//tree에 자식 추가
	for (int i = 0; i < n; i++) {
		if (isChild(root, i))
			ret->children.push_back(makeTree(i));
	}
	return ret;
}

int longest;
//root를 루트로 하는 서브트리를 반환한다
int height(TreeNode * root) {
	vector<int> heights;
	if (root->children.size() == 0)//자식이 없으면 0 반환
		return 0;
	//각 자식을 루트로 하는 서브트리의 높이를 계산한다
	for (int i = 0; i<root->children.size(); ++i)
		heights.push_back(height(root->children[i]));
	sort(heights.begin(), heights.end());
	//가장 긴 잎-잎경로 계산
	longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	//가장 긴 서브트리 높이 계산
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
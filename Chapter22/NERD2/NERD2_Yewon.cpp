#include<iostream>
#include<cstdio>
#include<vector>
#include<map>

using namespace std;

bool isDominated(map<int, int>& tree, int x, int y) {//�������� �����ڰ� ����Ǿ� �ִ� �� üũ
	map<int, int>::iterator it = tree.lower_bound(x);//�������� �����ں��� ���� ���� ���� �� ���� ������
	if (it == tree.end()) 
		return false;//���� ���� �� ���� �����ڰ� ������ ������� ����
	return y < it->second;
}

void isDominating(map<int, int>& tree, int x, int y) {
	map<int, int>::iterator it = tree.lower_bound(x);
	if (it == tree.begin())//���� ���� �� ���� �����ڰ� ������ �������� ����
		return;
	it--;//�������� �����ں��� ���� ���� ���� �� ���� ������(A)
	while (true) {
		if (y < it->second)//�������� �����ڰ� �������� ������
			break;
		//�������� �����ڰ� �����ϸ� �����ϴ� ���� �����Ѵ�
		//����Ǵ� ���� ���� ���ʿ� �ִ� ���� ��� �����ϰ� ����
		if (it == tree.begin()) {
			tree.erase(it);
			break;
		}
		//�ƴ� ��� �����ϰ� �� �������� ���� �����ڸ� ������
		else {
			map<int, int>::iterator it_r = it;
			--it;
			tree.erase(it_r);
		}
	}
}

int main() {

	int c;
	cin >> c;

	while (c--) {
		int n;
		cin >> n;

		map<int, int> tree;
		int result = 0;

		while (n--) {
			int p, q;
			cin >> p >> q;

			//������(A)�� ���� �� �������� ���� ���� ���� ������(B)�� ��� ���� ��
			if (isDominated(tree, p, q))
				result += tree.size();
			continue;
			//������(A)�� ���� �� �������� ���� ���� ���� ������(B)�� ��� ���� ��
			//������ ���� ���� ����
			isDominating(tree, p, q);
			map<int, int>::iterator a = tree.lower_bound(p);
			tree[p] = q;
			result += tree.size();
		}

		cout << result;
		
	}
	return 0;
}

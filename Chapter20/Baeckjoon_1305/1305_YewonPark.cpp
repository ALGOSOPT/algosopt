#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
//�κ���ġ���̺� �����ϴ� �Լ�

vector<int> PartialMatch(const string& input) {
	int n = input.size();
	vector<int> v(n, 0);//�갡 �κ���ġ���̺�

	int begin = 1, matched = 0;

	while (begin + matched<n) {
		if (input[begin + matched] == input[matched]) {
			++matched;//��ġ�ϴ±���!
			v[begin + matched - 1] = matched;//����
		}
		else {
			if (matched == 0)//�ϳ��� ��ġ���� ������
				++begin;
			else {//�ϳ� �̻� ��ġ�� �� ����ġ �߻��ϸ� begin�̶� matched�� �ٲ��ش�(kmp)
				begin += matched - v[matched - 1];
				matched = v[matched - 1];
			}
		}
	}

	return v;
}

int main() {

	int L;
	cin >> L;

	string input;
	cin >> input;

	vector<int> pi = PartialMatch(input);

	cout << L - pi[L-1];
}
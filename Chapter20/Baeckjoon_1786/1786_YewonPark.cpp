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

vector<int> kmp(const string& H, const string& N) {
	int n = H.size(), m = N.size();

	vector<int> ret;
	vector<int> pi = PartialMatch(N);

	int begin = 0, matched = 0;

	while (begin <= n - m) {
		if (matched<m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) {
				ret.push_back(begin);
			}
		}
		else {
			if (matched == 0)
				++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}

int main() {

	string T = "";
	string P = "";

	char input[1000000];
	cin.getline(input, 1000000);
	
	for (int i = 0; input[i] != NULL; i++) {
		T += input[i];
	}
	
	cin.getline(input, 1000000);
	for (int i = 0; input[i] != NULL; i++) {
		P += input[i];
	}

	vector<int> result = kmp(T, P);

	cout << result.size() << "\n";
	for (int i = 0; i < result.size(); i++)
		cout << result[i] + 1 << " ";
}
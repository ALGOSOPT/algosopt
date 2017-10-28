#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

vector<string> state;
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

int kmp(const string& H, const string& N) {
	int n = H.size(), m = N.size();

	vector<int> ret;
	vector<int> pi = PartialMatch(N);

	int begin = 0, matched = 0;

	while (begin <= n - m) {
		if (matched<m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) {
				return begin;
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
}

int main() {

	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;

		state = vector<string>();
		int result = 0;
		for (int i = 0; i <= n; i++) {
			string temp;
			cin >> temp;
			state.push_back(temp);
		}

		string H = state[0];
		H += state[0];

		int now = state[0].size();
		for (int i = 0; i < n; i++) {
			int after = kmp(H, state[i + 1]);
			//¦���� �ð���� : ó��-����
			if (i % 2 == 0) {
				//cout << now - after << " ";
				result += now - after;
				if (now - after < 0)
					result += state[0].size();
			}
			else {
				//cout << after - now << " ";
				result += after - now;
				if (after - now < 0)
					result += state[0].size();
			}
			now = after;
		}

		cout << result << "\n";
	}
}
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

vector<string> state;
//부분일치테이블 생성하는 함수
vector<int> PartialMatch(const string& input) {
	int n = input.size();
	vector<int> v(n, 0);//얘가 부분일치테이블

	int begin = 1, matched = 0;

	while (begin + matched<n) {
		if (input[begin + matched] == input[matched]) {
			++matched;//일치하는구나!
			v[begin + matched - 1] = matched;//갱신
		}
		else {
			if (matched == 0)//하나도 일치하지 않으면
				++begin;
			else {//하나 이상 일치한 후 불일치 발생하면 begin이랑 matched를 바꿔준다(kmp)
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
			//짝수면 시계방향 : 처음-나중
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
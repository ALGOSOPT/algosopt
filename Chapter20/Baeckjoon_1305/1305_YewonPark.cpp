#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
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

int main() {

	int L;
	cin >> L;

	string input;
	cin >> input;

	vector<int> pi = PartialMatch(input);

	cout << L - pi[L-1];
}
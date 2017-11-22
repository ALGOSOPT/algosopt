#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAX = 200010;
string input;

//group : 그룹 번호
int N, d, group[MAX];

vector<int> SA;
vector<int> LCP;

//접미사 비교에 사용할 비교 함수
bool cmp(int i, int j) {
	//먼저 자신의 위치의 문자를 비교
	if (group[i] != group[j]) return group[i] < group[j];
	//문자가 같으면 d칸 뒤의 문자끼리 비교
	i += d;
	j += d;
	return (i < N && j < N) ? (group[i] < group[j]) : (i > j);
}

//S를 사용해 sa 배열을 만드는 함수
vector<int> getSuffixArray() {

	//전처리
	for (int i = 0; i < N; i++) {
		SA[i] = i;
		group[i] = input[i]; //제일 첫 번쨰 루프에서는 제자리 문자로 비교
	}

	//d를 2배씩 늘려가면서 매번 앞에서부터 d*2글자만 보고 접미사 정렬
	for (d = 1; ; d *= 2) {
		sort(SA.begin(), SA.end(), cmp);
		//newGroup : 새로운 그룹 번호
		vector<int> newGroup(N);
		//앞에서부터 훑으면서 각 접미사가 서로 다른 그룹에 속할때마다 그룹 번호 증가시킴
		for (int i = 0; i < N - 1; i++)
			newGroup[i + 1] = newGroup[i] + cmp(SA[i], SA[i + 1]);
		//group배열을 newGroup 배열로 대체
		for (int i = 0; i < N; i++)
			group[SA[i]] = newGroup[i];

		//모든 접미사가 다른 그룹으로 나뉘어졌다면 종료
		if (newGroup[N - 1] == N - 1) break;
	}
	return SA;
}

//SA가 주어지면 LCP를 만드는 함수
void getLCP() {

	//group[i] = S[i:]가 SA의 몇 번째에 있는가(group[SA[i]] = i)
	//제일 긴 접미사(S)부터 시작한다.
	//매 루프마다 k > 0 이면  k--
	for (int i = 0, k = 0; i < N; i++, k = max(k - 1, 0)) {

		//마지막 접미사(길이 1)면 아무것도 안함
		if (group[i] == N - 1) continue;

		//바로 아래 인접한 접미사와 비교하여 앞에서 부터 몇 개의 글자가 
		//일치하는지 센다
		for (int j = SA[group[i] + 1]; input[i + k] == input[j + k]; k++);

		LCP[group[i]] = k;
	}
}

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> N;
	cin >> input;
	SA = vector<int>(N);
	LCP = vector<int>(N - 1);

	getSuffixArray();

	//for (int i = 0; i < SA.size(); i++) {
	//	for (int j = SA[i]; j < N; j++)
	//		cout << input[j];
	//	cout << endl;
	//}


	getLCP();
	int ret = 0;
	for (int i = 0; i < LCP.size(); i++) {
		ret = max(ret, LCP[i]);
	}
	cout << ret << endl;

}


#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

string S;

int N, d;

//Suffix Array : 사전 순 i번째 접미사의 번호
vector<int> SA;

//group : 접미사S[i..]의 그룹 번호
vector<int> group;

//접미사 비교에 사용할 함수
// 같은 그룹 0, 다른 그룹 1
// 시간 복잡도가 O(1)
bool cmp(int i, int j){

	// 먼저 자신의 위치의 문자를 비교
	if(group[i] != group[j]) return group[i] < group[j];

	// 문자가 같으면 d칸 뒤의 문자끼리 비교
    //
	i += d;
	j += d;
	return (i < N && j < N) ? (group[i] < group[j]) : (i > j);
}


//S를 사용해 sa 배열을 만드는 함수
void constructSA(){


	//전처리
	for(int i = 0; i < N; i++){
		SA[i] = i;
		//제일 첫 번째 루프에서는 제자리 문자로 비교
        // 접미사의 첫 글자로 그루핑한다.
		group[i] = S[i];
	}

	for(d = 1; ; d *= 2) {
        // 그룹이 같을때와
		sort(SA, SA + N, cmp);
		//newGroup : 새로운 그룹 번호
		vector<int> newGroup(N, 0);

		//앞에서 부터 훑으면서 각 접미사가 서로 다른 그룹에 속할 때 마다 그룹번호 증가시킴
		for(int i = 0; i < N - 1; i++)
			newGroup[i + 1] = newGroup[i] + cmp(SA[i], SA[i + 1]);

		//group 배열을 newGroup 배열로 대체
		for(int i = 0; i < N; i++)
			group[SA[i]] = newGroup[i];

		//모든 접미사가 다른 그룹으로 나뉘어졌다면 종료
		if(newGroup[N - 1] == N - 1) break;
	}
}


int main(){

	cin>>S;
	N = S.size();

	SA = vector<int>(N);
	group = vector<int>(N);

	for(int i = 0; i < N; i++)
		//첫 번째 인덱스가 0인 경우
 		cout<<SA[i]<<" ";

	return 0;
}

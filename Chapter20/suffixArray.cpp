#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 1<<19;

char S[MAX];

//group : 그룹 번호
int N, d, sa[MAX], group[MAX];

//접미사 비교에 사용할 비교 함수
bool cmp(int i, int j){
	//먼저 자신의 위치의 문자를 비교
	if(group[i] != group[j]) return group[i] < group[j];
	//문자가 같으면 d칸 뒤의 문자끼리 비교
	i += d;
	j += d;
	return (i < N && j < N) ? (group[i] < group[j]) : (i > j);
}

//S를 사용해 sa 배열을 만드는 함수
void constructSA(){
	N = strlen(S);

	//전처리
	for(int i = 0; i < N; i++){
		sa[i] = i;
		group[i] = S[i]; //제일 첫 번쨰 루프에서는 제자리 문자로 비교
	}
	//d를 2배씩 늘려가면서 매번 앞에서부터 d*2글자만 보고 접미사 정렬
	for(d = 1; ; d *= 2){
		sort(sa, sa + N, cmp);
		//newGroup : 새로운 그룹 번호
		int newGroup[MAX] = {0};
		//앞에서부터 훑으면서 각 접미사가 서로 다른 그룹에 속할때마다 그룹 번호 증가시킴
		for(int i = 0; i < N - 1; i++)
			newGroup[i + 1] = newGroup[i] + cmp(sa[i], sa[i + 1]);
		//group배열을 newGroup 배열로 대체
		for(int i = 0; i < N; i++)
			group[sa[i]] = newGroup[i];

		//모든 접미사가 다른 그룹으로 나뉘어졌다면 종료
		if(newGroup[N - 1] == N - 1) break;
	}
}
 
int main(){
    scanf("%s", S);
    constructSA();
    for(int i=0; i<N; i++)
        printf("%d ", sa[i]+1);
}


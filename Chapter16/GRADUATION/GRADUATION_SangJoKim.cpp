#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N, K, M, L;

//선수과목
int prerequisite[13];

//열리는 과목
int openLecture[11];

//dp[학기][들은과목]
int dp[11][1 << 12];

//semester 학기에 takenLecture 학기를 들었다면
int solve(int semester, int takenLecture) {

	//전공과목  K개를 다 들었다면. 기저사례
	if (__popcnt(takenLecture) == K) return 1;

	int& ret = dp[semester][takenLecture];
	
	if (ret != -1) return ret;

	ret = 0x3f3f3f3f;

	//지금 학기에 열린 과목들을 전부 한 번 들어보자!
	for (int subject = openLecture[semester]; subject; subject = ((subject - 1) & openLecture[semester])) {
		//subject의 각 bit가 들을 과목.


		//들을 수 있는 과목의 숫자 check!
		if (__popcnt(subject) > L) continue;

		bool possible = true;
		//들을 과목들을 돌면서 선수과목을 check!
		for (int j = 0; j < N; j++) {
			//openLecture[j]가 takenLecture의 부분집합이 아니면
			if ((openLecture[j] & takenLecture) != openLecture[j]) {
				possible = false;
				break;
			}

			//j번째 과목을 이미 들었다면 pass!
			if (takenLecture & (1 << j)) {
				possible = false;
				break;
			}
		}

		//가능하면,
		if (possible) {
			ret = min(ret, solve(semester + 1, takenLecture | subject) + 1);
		}

	}
	//이번학기 안 들을수도 있잖아
	ret = min(ret, solve(semester + 1, takenLecture));

	return ret;
}

int main() {

	freopen("input.txt", "r", stdin);


	int TC; cin >> TC;

	while (TC--)
	{
		cin >> N >> K >> M >> L;

		memset(prerequisite, 0, sizeof(prerequisite));
		memset(openLecture, 0, sizeof(openLecture));
		memset(dp, -1, sizeof(dp));

		#pragma region 입력처리


		for (int i = 0; i < N; i++) {
			int R;
			cin >> R;
			for (int j = 0; j < R; j++) {
				int subject; cin >> subject;
				prerequisite[i] &= (1 << subject);
			}
		}
		for (int semester = 0; semester < M; semester++) {
			int subjectNumber; cin >> subjectNumber;
			for (int index = 0; index < subjectNumber; index++) {
				int subject; cin >> subject;
				openLecture[semester] &= (1 << subject);
			}
		}
		#pragma endregion

		int ret = solve(0, 0);

		if (ret == -1) cout << "IMPOSSIBLE" << endl;
		else cout << ret << endl;

	
	}

	return 0;
}
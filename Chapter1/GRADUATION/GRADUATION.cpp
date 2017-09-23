#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

const int INF = 987654321;
int n, k, m, l;
int prerequisite[12];
int classes[10];
int cache[10][1 << 12];

int bitCount(int x) {
	if (x == 0) return 0;
	return x % 2 + bitCount(x / 2);
}

int graduate(int semester, int taken) {

	if (bitCount(taken) >= k)
		return 0;

	if (semester == m)
		return INF;

	int& ret = cache[semester][taken];

	if (ret != -1)
		return ret;

	ret = INF;
	int canTake = (classes[semester] & ~taken);
	for (int i = 0; i < n; i++)
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
			canTake &= ~(1 << i);

	for (int take = canTake; take > 0; take = ((take - 1)&canTake)) {
		if (bitCount(take) > l)
			continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}

	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}

int main() {

	int c;
	cin >> c;

	while (c--) {
		cin >> n >> k >> m >> l;
		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < n; i++) {
			int pre_total;
			cin >> pre_total;
			int pre_result = 0;
			for (int j = 0; j < pre_total; k++) {
				int pre;
				cin >> pre;
				pre_result |= (1 << pre);
			}
			prerequisite[i] = pre_result;
		}
		for (int i = 0; i < m; i++) {
			int subject_num;
			cin >> subject_num;
			int subject_result = 0;
			for (int j = 0; j < subject_num; j++) {
				int subject;
				cin >> subject;
				subject_result |= (1 << subject);
			}
			classes[i] = subject_result;
		}

		if (graduate(0, 0) == INF)
			cout << "INPOSSIBLE";
		else
			cout << graduate(0, 0);

		cout << "\n";
		
	}
}
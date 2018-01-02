#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int n;
int nowGas, destDist;
class station {
public:
	int gas, dist;
	station() {};
	station(int gas, int dist) : gas(gas), dist(dist) {}
	bool operator <(station& cmp) {
		return this->dist < cmp.dist;
	}
};

station st[10001];
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d%d", &st[i].dist , &st[i].gas);
	}

	sort(st, st + n);
	scanf("%d%d", &destDist, &nowGas);

	priority_queue<int> pq;
	int maxIdx = 0, num = 0;
	while (true) {
		if (nowGas >= destDist) break;

		while (maxIdx < n && st[maxIdx].dist <= nowGas){
			pq.push(st[maxIdx].gas);
			maxIdx++;
		}
		if (pq.empty()) break;

		nowGas += pq.top();
		pq.pop();
		num++;
	}
	
	if (nowGas < destDist) {
		cout << -1 << endl;
	}
	else {
		cout << num << endl;
	}
	return 0;
}
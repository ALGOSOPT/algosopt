#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <string>
#include <cstring>

#define mp make_pair

using namespace std;
int n;
vector<string> board;

inline bool canGo(int y, int x) {
	return y >= 0 && y < n && x >= 0 && x < n && board[y][x] != '*';
}
inline bool canGo2(int& hereY, int& hereX, int& hereDir, int& nextY, int& nextX, int& nextDir) {


}
int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

vector<pair<int, int> > doors;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n;
	board = vector<string>(n);
	for (int i = 0; i < n; i++) {
		cin >> board[i];
		for (int j = 0; j < n; j++) {
			if (board[i][j] == '#')
				doors.push_back(mp(i, j));
		}
	}

	int dist[51][51][4];
	memset(dist, -1, sizeof(dist));

	//first = y, second.first = x, second.second = dir
	queue<pair<int, pair<int, int> > > q;

	for (int i = 0; i < 4; i++) {
		q.push(mp(doors[0].first, mp(doors[0].second, i)));
		dist[doors[0].first][doors[0].second][i] = 0;
	}

	int ret = 0x3f3f3f3f;

	while (!q.empty()) {
		
		int hereY = q.front().first;
		int hereX = q.front().second.first;
		int hereDir = q.front().second.second;
		q.pop();
		if (hereY == doors[1].first && hereX == doors[1].second) {
			ret = min(ret, dist[hereY][hereX][hereDir]);
		}

		//지금 방향 그대로
		int nextY = hereY + dy[hereDir], nextX = hereX + dx[hereDir],
			nextDir = hereDir;
		if (canGo(nextY, nextX) && (dist[nextY][nextX][nextDir] == -1 ||
			dist[nextY][nextX][nextDir] > dist[hereY][hereX][hereDir]) ) {
			q.push(mp(nextY, mp(nextX, nextDir)));
			dist[nextY][nextX][nextDir] = dist[hereY][hereX][hereDir];
			
		}

		//만약 거울이라면 방향도 꺽어본다
		if (board[hereY][hereX] == '!') {
			//cout << hereY << " " << hereX <<" "<<hereDir<< " "<<dist[hereY][hereX][hereDir]<<endl;
			nextDir = ((hereDir / 2) * 2 + 2) % 4;
			nextY = hereY + dy[nextDir];
			nextX = hereX + dx[nextDir];
			if (canGo(nextY, nextX) && (dist[nextY][nextX][nextDir] == -1 ||
				dist[nextY][nextX][nextDir] > dist[hereY][hereX][hereDir])) {
				q.push(mp(nextY, mp(nextX, nextDir)));
				dist[nextY][nextX][nextDir] = dist[hereY][hereX][hereDir] + 1;
				
			
			}
			nextDir = ((hereDir / 2) * 2+ 3) % 4;
			nextY = hereY + dy[nextDir];
			nextX = hereX + dx[nextDir];
			if (canGo(nextY, nextX) && (dist[nextY][nextX][nextDir] == -1 ||
				dist[nextY][nextX][nextDir] > dist[hereY][hereX][hereDir])) {
				q.push(mp(nextY, mp(nextX, nextDir)));
				dist[nextY][nextX][nextDir] = dist[hereY][hereX][hereDir] + 1;
				
			}
		}

	}

	cout << ret << endl;

	return 0;
}
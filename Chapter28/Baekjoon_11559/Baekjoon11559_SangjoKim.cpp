#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

vector<string> board(12);
int recordBoard[12][6];


void fallDown() {
	for (int x = 0; x < 6; x++) {
		for (int y = 11; y >= 1; y--) {
			if (board[y][x] == '.') {
				int yy = y - 1;
				while (yy >= 0) {
					if (board[yy][x] != '.') {
						board[y][x] = board[yy][x];
						board[yy][x] = '.';
						break;
					}
					yy--;
				}
			}
		}
	}
}

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };
bool isIn(int y, int x) {
	return y >= 0 && x >= 0 && y < 12 && x < 6;
}
void dfs(int y, int x, vector<pair<int, int> >& record) {

	recordBoard[y][x] = 0;

	char hereColor = board[y][x];
	for (int i = 0; i < 4; i++) {
		int nextY = y + dy[i];
		int nextX = x + dx[i];
		if (isIn(nextY, nextX) && hereColor == board[nextY][nextX] && recordBoard[nextY][nextX] == -1) {
			dfs(nextY, nextX, record);
		}
	}
	record.push_back(make_pair(y, x));
}


int main() {
	freopen("input.txt", "r", stdin);

	for (int i = 0; i < 12; i++) {
		cin >> board[i];
		//cout << board[i] << endl;
	}
	//cout << endl;
	int ret = 0;
	while (true) {

		memset(recordBoard, -1, sizeof(recordBoard));
		bool check = false;
		for (int y = 0; y < 12; y++) {
			for (int x = 0; x < 6; x++) {
				if (board[y][x] != '.' && recordBoard[y][x] == -1) {
					vector<pair<int, int> > record;
					dfs(y, x, record);
					if (record.size() >= 4) {
						check = true;
						for (int i = 0; i < record.size(); i++) {
							board[record[i].first][record[i].second] = '.';
						}
					}
				}
			}
		}
		ret += check;
		fallDown();
		if (!check) break;
		//for (int i = 0; i < 12; i++) {
		//	cout << board[i] << endl;
		//}
		//cout << endl;
	}

	cout << ret << endl;
	
	return 0;
}
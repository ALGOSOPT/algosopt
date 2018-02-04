#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <cstring>

using namespace std;
#define INF 0x3f3f3f3f

int n, m;
vector<string> board;
pair<int, int> start, ee;
int dy[] = {0, 0, 1, -1};
int dx[] = {1, -1, 0, 0};

bool canGo(int y, int x){
	return y >= 0 && y < n && x >= 0 && x < m && board[y][x] != '#';
}

int main(){

	freopen("input.txt","r",stdin);
	scanf("%d%d",&n,&m);
	board = vector<string>(n);

	for(int i = 0; i < n; i++){
		cin>>board[i];
		for(int j = 0; j < m; j++){
			//now minsick is standing
			if(board[i][j] == '0'){
				start.first = i; start.second = j;
			}
			//destination of minsick
			else if(board[i][j] =='1'){
				ee.first = i; ee.second = j;
			}
		}
	}

	int dist[51][51][1<<7];
	memset(dist, -1, sizeof(dist));
	queue<pair<pair<int, int> , int> > q;
	dist[start.first][start.second][0] = 0;
	q.push(make_pair(make_pair(start.first, start.second), 0));
	int ret = INF;
	while(!q.empty()){
		int hereY = q.front().first.first;
		int hereX = q.front().first.second;
		int hereKey =q.front().second;
		// cout<<hereY<<" "<<hereX<<" "<<hereKey<<" "<<dist[hereY][hereX][hereKey]<<endl;
		q.pop();
		if(hereY == ee.first && hereX == ee.second){
			ret = min(ret, dist[hereY][hereX][hereKey]);
		}

		for(int i = 0; i < 4; i++){
			int nextY = hereY + dy[i];
			int nextX = hereX + dx[i];
			if(canGo(nextY, nextX)){
				int nextKey = hereKey;
				if(board[nextY][nextX] >= 'A' && board[nextY][nextX] <='F' && (hereKey & (1<<(board[nextY][nextX] - 'A'))) == 0){
					continue;
				} 
				if(board[nextY][nextX] >= 'a' && board[nextY][nextX] <= 'f'){
					nextKey = hereKey | (1<<(board[nextY][nextX] - 'a'));
					
				}

				if(dist[nextY][nextX][nextKey] == -1 || dist[nextY][nextX][nextKey] > dist[hereY][hereX][hereKey] + 1){
					q.push(make_pair(make_pair(nextY, nextX), nextKey));
					dist[nextY][nextX][nextKey] = dist[hereY][hereX][hereKey] + 1;
				}
			}
		}
	}

	if(ret == INF){
		cout<<-1<<endl;
	}
	else{
		cout<<ret<<endl;
	}
	return 0;
}

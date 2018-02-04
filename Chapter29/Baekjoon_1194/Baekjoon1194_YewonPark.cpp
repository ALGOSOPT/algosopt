#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>

using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

char board[50][50];
int depth[50][50][127];//key는 fedcba 
bool key[26]; 
int y_m, x_m;//민식의 위치
int result;

int main(){

	result = -1;	
	memset(depth, -1, sizeof(depth));
	
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++){
		string temp;
		cin >> temp;
		for(int j=0; j<m; j++){
			board[i][j] = temp[j];
			if(board[i][j] == '0')
				y_m = i, x_m = j;
		}
	}
	
	queue<pair<pair<int, int> ,pair<int, int> > > q;//<<y, x>, <key, depth>>
	depth[y_m][x_m][0] = 0;
	q.push(make_pair(make_pair(y_m, x_m), make_pair(0, 0)));
	
	while(!q.empty()){
		//현재 위치와 depth 
		int y = q.front().first.first, x = q.front().first.second;
		int k = q.front().second.first, d = q.front().second.second;
		//cout << y << " "<< x << " " << k << " " << d << "\n";
		q.pop();
		
		if(board[y][x] == '1'){
			result = d;
			break;	
		}
		
		//열쇠면
		if(board[y][x]>=97 && board[y][x]<=102){//열쇠를 next에서 변경해주면 안됨 
			k|=(1<<((int)board[y][x]-97));
		}	
		 
		for(int i=0; i<4; i++){
			if(y+dy[i]>=0 && y+dy[i]<n && x+dx[i]>=0 && x+dx[i]<m){
				if(board[y+dy[i]][x+dx[i]]=='#')
					continue;
				if(depth[y+dy[i]][x+dx[i]][k] != -1)
					continue;
				//열쇠를 next에서 변경해주면 안됨 
				//if(board[y+dy[i]][x+dx[i]]>=97 && board[y+dy[i]][x+dx[i]]<=102){
				//	k|=(1<<((int)board[y+dy[i]][x+dx[i]]-97));
				//}
				if(board[y+dy[i]][x+dx[i]]>=65 && board[y+dy[i]][x+dx[i]]<=70){//문 
					if(!(k & (1<<((int)board[y+dy[i]][x+dx[i]]-65))))
						continue;
				}
				depth[y+dy[i]][x+dx[i]][k] = d+1;
				q.push(make_pair(make_pair(y+dy[i], x+dx[i]), make_pair(k, d+1))); 
			}
		}
	}
	
	cout << result;
	
}

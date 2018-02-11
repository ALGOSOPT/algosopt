#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
char board[12][6];
bool visited[12][6];

int num_p;//전체 뿌요 수 
int num_s;//탐색한 뿌요 수
 
vector<pair<int, int> > rem;

void dfs(int y, int x){
	num_s++; 
	rem.push_back(make_pair(y, x));//뻐큐모양을 위한 처리 
	visited[y][x] = true;
	for(int i=0; i<4; i++){
		int y_n = y+dy[i];
		int x_n = x+dx[i];
		if(y_n >= 0 && y_n < 12 && x_n >= 0 && x_n <6){
			if(!visited[y_n][x_n] && board[y][x] == board[y_n][x_n]){
				dfs(y_n, x_n);
			}
		}
	}
	//뻐큐모양때문에 이렇게하면 망함 
	//if(num>=3)
	//	board[y][x] = '.' 
} 

int main(){
	
	//freopen("input.txt","r",stdin);
	for(int i=0; i<12; i++){
		char temp[6];
		scanf("%s", temp);
		for(int j=0; j<6; j++){
			board[i][j] = temp[j];	
			if(board[i][j] != '.')
				num_p++;	
		}
	}
/*	처음에 board에도 잘 안들어갔었음
왜냐면 한줄씩 들어가기 때문 
	for(int i=0; i<12; i++){
		for(int j=0; j<6; j++)
			printf("%c ", board[i][j]);
		cout << "\n";	
	}
*/		
	int result = 0;
	while(true){
		num_s = 0;
		bool is_p = false;//변화가 있었는 지 
		
		//뿌요가 남아있는 동안
		memset(visited, false, sizeof(visited));
		for(int i=11; i>=0; i--){
			for(int j=0; j<6; j++){
				if(board[i][j] != '.' && !visited[i][j]){
					//dfs가 시작됨
					dfs(i, j); 
					if(rem.size() >= 4){//뿌요터짐 
						is_p = true;
						for(int i=0; i<rem.size(); i++)
							board[rem[i].first][rem[i].second] = '.';
					}
					rem.clear();
				} 
			}if(num_s == num_p)//뿌요 다봤으면 
				break;
		} 
		
		if(!is_p)//뿌요가 터진적이 없으면 
			break;
			
		//뿌요들을 아래로 밀어야함
		/*
		 for(int i=0; i<12; i++){
		 	for(int j=0; j<6; j++)
		 		cout << board[i][j];
		 	cout << "\n";
		 }
		 */
		 for(int j=0; j<6; j++){
		 	int next = -1;//다음에 채워져야할 곳 
		 	for(int i=11; i>=0; i--){
		 		if(board[i][j] == '.' && next == -1){
		 			next = i;
				 }
		 		else if(board[i][j] != '.' && next != -1){
		 			board[next][j] = board[i][j];
		 			board[i][j] = '.';
		 			next--;
				 } 
			 }
		 }/*
		 for(int i=0; i<12; i++){
		 	for(int j=0; j<6; j++)
		 		cout << board[i][j];
		 	cout << "\n";
		 }*/
		 result++; 
	}
	cout << result;
}

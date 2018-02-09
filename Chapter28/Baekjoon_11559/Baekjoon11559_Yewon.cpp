#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
char board[12][6];
bool visited[12][6];

int num_p;//��ü �ѿ� �� 
int num_s;//Ž���� �ѿ� ��
 
vector<pair<int, int> > rem;

void dfs(int y, int x){
	num_s++; 
	rem.push_back(make_pair(y, x));//��ť����� ���� ó�� 
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
	//��ť��綧���� �̷����ϸ� ���� 
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
/*	ó���� board���� �� �ȵ�����
�ֳĸ� ���پ� ���� ���� 
	for(int i=0; i<12; i++){
		for(int j=0; j<6; j++)
			printf("%c ", board[i][j]);
		cout << "\n";	
	}
*/		
	int result = 0;
	while(true){
		num_s = 0;
		bool is_p = false;//��ȭ�� �־��� �� 
		
		//�ѿ䰡 �����ִ� ����
		memset(visited, false, sizeof(visited));
		for(int i=11; i>=0; i--){
			for(int j=0; j<6; j++){
				if(board[i][j] != '.' && !visited[i][j]){
					//dfs�� ���۵�
					dfs(i, j); 
					if(rem.size() >= 4){//�ѿ����� 
						is_p = true;
						for(int i=0; i<rem.size(); i++)
							board[rem[i].first][rem[i].second] = '.';
					}
					rem.clear();
				} 
			}if(num_s == num_p)//�ѿ� �ٺ����� 
				break;
		} 
		
		if(!is_p)//�ѿ䰡 �������� ������ 
			break;
			
		//�ѿ���� �Ʒ��� �о����
		/*
		 for(int i=0; i<12; i++){
		 	for(int j=0; j<6; j++)
		 		cout << board[i][j];
		 	cout << "\n";
		 }
		 */
		 for(int j=0; j<6; j++){
		 	int next = -1;//������ ä�������� �� 
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

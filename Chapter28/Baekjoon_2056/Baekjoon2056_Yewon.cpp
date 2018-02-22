#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> time;//�� �۾��� �ɸ��� �ð� 
vector<int> total_time;//ó������ �� �۾����� ������ �� �ɸ��� �ð� 
vector<vector<int> > adj;
vector<int> pre_edge;//�� �۾��� ���� ������ ����Ǵ� �۾� �� 
vector<int> visited;//������ ����Ǵ� �۾��� ��� ����Ǿ��� �� 
int result;

//����Ž���ϸ� �ð��ʰ�����.
//edge�� �̿��� �˰����̴� dfs�̴� node�� �ѹ��� �������Ѵ�. 

//�� ������ dfs���� ������ �ʿ��ϴ�.
//������ ����Ǵ� �۾��� ��� ����� ��쿡�� ������ �鸦 �� �ִ�.
//(edge�� �̿��� �˰����� �̿��ϸ� ������ �� ����) 
void dfs(int x, int pre_time){//pre_time�� x�� ���� �������� �ð� 
	//printf("x %d pre_time %d\n", x, pre_time);
	total_time[x] = pre_time+time[x];
	result = max(result, total_time[x]);  
	for(int i=0; i<adj[x].size(); i++){
		int next = adj[x][i];
		visited[next]++;
		total_time[next] = max(total_time[next], pre_time+time[x]);
		if(visited[next] == pre_edge[next])
			dfs(next, total_time[next]);
	}
}

int main(){
	
	//freopen("input.txt", "r", stdin);
	int n;
	int total = 0;
	scanf("%d", &n);
	
	time = vector<int>(n+1);
	total_time = vector<int>(n+1);
	adj = vector<vector<int> >(n+1);
	pre_edge = vector<int>(n+1);
	visited = vector<int>(n+1);
	for(int i=1; i<=n; i++){
		scanf("%d", &time[i]);
		scanf("%d", &pre_edge[i]);
		for(int j=0; j<pre_edge[i]; j++){
			int temp;
			scanf("%d", &temp);
			adj[temp].push_back(i);
		}
	}
	
	for(int i=1; i<=n; i++){
		if(pre_edge[i] == 0){
			//cout << "start " << i << "\n";
			dfs(i, 0);	
		}
	}
	
	printf("%d", result);
	return 0;
}

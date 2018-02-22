#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> time;//한 작업이 걸리는 시간 
vector<int> total_time;//처음부터 한 작업까지 끝나는 데 걸리는 시간 
vector<vector<int> > adj;
vector<int> pre_edge;//한 작업에 대해 직전에 선행되는 작업 수 
vector<int> visited;//직전에 선행되는 작업이 몇개가 수행되었는 지 
int result;

//완전탐색하면 시간초과난다.
//edge를 이용한 알고리즘이던 dfs이던 node는 한번만 지나야한다. 

//이 문제는 dfs에서 변형이 필요하다.
//직전에 선행되는 작업이 모두 수행된 경우에만 정점을 들를 수 있다.
//(edge를 이용한 알고리즘을 이용하면 수월할 것 같음) 
void dfs(int x, int pre_time){//pre_time은 x에 오기 전까지의 시간 
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

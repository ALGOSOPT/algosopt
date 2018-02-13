#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
vector<int> workTime;
vector<int> preWorking;
vector<vector<int> > adj;
int startTime[10001];
int visitedNum[10001];
int ret = 0;


void dfs(int here, int nowTime){
	startTime[here] = max(startTime[here], nowTime);
	if (visitedNum[here] != preWorking[here]) return;

	int finishTime = startTime[here] + workTime[here];

	for (int i = 0; i < adj[here].size(); i++){
		int next = adj[here][i];
		visitedNum[next]++;
		dfs(next, finishTime);
	}
	ret = max(ret, finishTime);
}
int main(){

	freopen("input.txt", "r", stdin);
	scanf("%d", &n);

	memset(startTime, 0, sizeof(startTime));
	memset(visitedNum, 0, sizeof(visitedNum));
	workTime = vector<int>(n + 1);
	preWorking = vector<int>(n + 1);
	adj = vector<vector<int> >(n + 1);

	for (int i = 1; i <= n; i++){
		scanf("%d%d", &workTime[i], &preWorking[i]);
		for (int j = 0; j < preWorking[i]; j++){
			int from; scanf("%d", &from);
			adj[from].push_back(i);
			
		}
	}

	for (int i = 1; i <= n; i++){
		if (preWorking[i] == 0) dfs(i, 0);
	}
	cout << ret << endl;


	return 0;
}

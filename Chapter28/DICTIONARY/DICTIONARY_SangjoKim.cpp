#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int ALPHABETS = 26;
const string NOT = "INVALID HYPOTHESUS";
vector<vector<int> > adj;
vector<bool> visited;
vector<int> order;
int toNumber(char a){
	return (a - 'a');
}

void dfs(int here){
	visited[here] = true;
	// order.push_back(here);
	for(int there = 0; there < adj.size(); there++){
		if(adj[here][there] && !visited[there]){
			dfs(there);
		}
	}
	order.push_back(here);
}

int main(){
	freopen("input.txt","r",stdin);
	setbuf(stdout, NULL);

	int TC; scanf("%d", &TC);

	while(TC--){

		int n; scanf("%d",&n);
		
		vector<string> dic;
		for(int i = 0; i < n; i++){
			string buf;
			cin>>buf;
			dic.push_back(buf);
		}
		adj.clear(); visited.clear();
		adj = vector<vector<int> >(26, vector<int>(26,0));
		visited = vector<bool>(26, false);
		// cout<<toNumber('c')<<endl;
		for(int i = 0; i < n - 1; i++){

			int minSize = min(dic[i].size(), dic[i + 1].size());
			
			for(int j = 0; j < minSize; j++){
				if(dic[i][j] != dic[i+1][j]){
					adj[toNumber(dic[i][j])][toNumber(dic[i + 1][j])] = 1;
					break;
				}

			}
		}


		bool check = true;
		for(int i = 0; i < 26; i++){
			for(int j = i + 1; j < 26; j++){
				if(adj[i][j] & adj[j][i]){
					check = false;
					break;
				}
			}
			if(!check)	break;
		}

		if(!check){
			cout<<NOT<<endl;
			continue;
		}
		order.clear();
		for(int i = 0; i < 26; i++){
			if(!visited[i]){
				dfs(i);
			}
		}
		// cout<<endl;

		// reverse(order.begin(), order.end());
		for(int i = 0; i < order.size(); i++){
			cout<<(char)(order[i]+'a');
		}
		cout<<endl;
		// cout<<order.size()<<endl;
	}
	return 0;
}
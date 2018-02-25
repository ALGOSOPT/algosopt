#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
int G, H;

vector<vector<int> > adj;
vector<bool> visited;

const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;

int installed;

int dfs(int here){

	visited[here] = true;

	int children[3] = {0, 0, 0};

	for(int i = 0; i < adj[here].size(); i++){
		int there = adj[here][i];

		if(!visited[there])
			children[dfs(there)]++;
	}

	if(children[UNWATCHED]){
		installed++;
		return INSTALLED;
	}

	if(children[INSTALLED])
		return WATCHED;

	return UNWATCHED;
}
int main(){
	freopen("input.txt","r",stdin);
	setbuf(stdout, NULL);

	int TC;	scanf("%d", &TC);

	while(TC--){
		
		scanf("%d %d", &G, &H);
		
		int b1, b2;

		adj = vector<vector<int> >(G);

		visited = vector<bool>(G, false);
		
		installed = 0;

		for(int i = 0; i < H; i++){

			scanf("%d %d", &b1, &b2);

			adj[b1].push_back(b2);
		
			adj[b2].push_back(b1);
		
		}

		for(int i = 0; i < G; i++){
			if(!visited[i] && dfs(i) == UNWATCHED)
				installed++;
		}


		cout<<installed<<endl;
	}

	return 0;
}
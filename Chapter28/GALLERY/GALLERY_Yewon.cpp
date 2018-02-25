#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int V;
vector<int> adj[1001];
vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;
int installed;

int dfs(int here) {
    visited[here] = true;
    int children[3] = {0, 0, 0};
    for(int i=0; i<adj[here].size(); i++) {
        int there = adj[here][i];
        if(!visited[there]) {
            ++children[dfs(there)];
        }
    }
    if(children[UNWATCHED]) {
        ++installed;
        return INSTALLED;
    }
    if(children[INSTALLED]) {
        return WATCHED;
    }
    return UNWATCHED;
}

int installCamera() {
    installed = 0;
    visited = vector<bool>(V+1, false);
    for(int u=0; u<V; u++) {
        if(!visited[u] && dfs(u) == UNWATCHED) {
            ++installed;
        }
    }
    return installed;
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--){
    	int h;
        scanf("%d %d", &V, &h);
        for(int i=0; i<V; i++) {
            adj[i].clear();
        }
        for(int i=0; i<h; i++) {
            int t1,t2;
            scanf("%d %d", &t1, &t2);
            adj[t1].push_back(t2);
            adj[t2].push_back(t1);
        }
        printf("%d\n", installCamera());
    }
    return 0;
}

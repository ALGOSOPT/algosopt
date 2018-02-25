// TIMEOUT

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> adj[500001];
int money[500001];

int n,m;

void dfs(int here, int diff) {
    for(int i=0; i<adj[here].size(); i++) {
        int there = adj[here][i];
        money[there] += diff;
        dfs(there, diff);
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; i++) {
        scanf("%d", &money[i]);
        if(i != 1) {
            int t;
            scanf("%d", &t);
            adj[t].push_back(i);
        }
    }
    for(int i=0; i<m; i++) {
        char c;
        int t1, t2;
        cin >> c;
        if(c == 'p') {
            scanf("%d %d", &t1, &t2);
            dfs(t1, t2);
        }
        else {
            scanf("%d", &t1);
            printf("%d\n", money[t1]);
        }
    }
    return 0;
}

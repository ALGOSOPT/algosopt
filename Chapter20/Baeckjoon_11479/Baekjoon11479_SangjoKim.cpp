#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
int n, m;


vector<vector<int> > adj;
int parent[100001][18];  //parent[i][k] : i의 2^k번째 부모
int depth[100001];

void makeTree(int here) {

	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		//아직 방문하지 않았으면
		if (depth[there] == -1) {
			parent[there][0] = here;
			depth[there] = depth[here] + 1;
			makeTree(there);
		}
	}
}


int main() {

	freopen("input.txt", "r", stdin);
	cin >> n;

	adj = vector<vector<int> >(n);

	for (int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	memset(parent, -1, sizeof(parent)); memset(depth, -1, sizeof(depth));

	depth[0] = 0;

	makeTree(0);

	//여기가 어렵다 parent의 나머지를 채움

	for (int j = 0; j < 17; j++) {
		for (int i = 1; i < n; i++) {
			if (parent[i][j] != -1)
				parent[i][j + 1] = parent[parent[i][j]][j];
		}
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		u--;v--;
		

		if (depth[u] < depth[v]) swap(u, v);

		int diff = depth[u] - depth[v];

		for (int j = 0; diff; j++) {
			if (diff % 2) u = parent[u][j];
			diff /= 2;
		}

		if (u != v) {

			for (int j = 17; j >= 0; j--) {
				if (parent[u][j] != -1 && parent[u][j] != parent[v][j]) {
					u = parent[u][j];
					v = parent[v][j];
				}
			}

			u = parent[u][0];
		}

		printf("%d\n", u + 1);

	}


	return 0;
}
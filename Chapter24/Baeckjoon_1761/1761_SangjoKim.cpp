#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define mp make_pair
int n, m;

vector<vector<pair<int, int>>> adj;
int parent[40001][17];
int depth[40001];
int dist[40001][17];

void makeTree(int here) {

	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i].first;
		if (depth[there] == -1) {
			parent[there][0] = here;
			for (int k = 0; k < adj[there].size(); k++) {
				if (adj[there][k].first == here) {
					dist[there][0] = adj[there][k].second;
					break;
				}
			}
			depth[there] = depth[here] + 1;
			makeTree(there);
		}
	}
}


int main() {
	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &n);

	//first는 이어진 node의 번호, second는 distance
	adj = vector<vector<pair<int, int> > >(n);

	for (int i = 0; i < n - 1; i++) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		a--; b--;
		adj[a].push_back(mp(b, c));
		adj[b].push_back(mp(a, c));
	}
	memset(parent, -1, sizeof(parent)); memset(depth, -1, sizeof(depth));
	memset(dist, 0, sizeof(dist));
	int start;
	for (int i = 0; i < n; i++) {
		if (adj[i].size() == 1) {
			start = i; break;
		}
	}
	depth[start] = 0;

	makeTree(start);

	for (int j = 0; j < 17; j++) {
		for (int i = 0; i < n; i++) {
			if (parent[i][j] != -1 && i != start) {
				parent[i][j + 1] = parent[parent[i][j]][j];
				dist[i][j + 1] = dist[i][j] + dist[parent[i][j]][j];
			}
		}
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b; scanf("%d%d", &a, &b);
		a--; b--;
		int distance = 0;
		if (depth[a] < depth[b]) swap(a, b);
		int diff = depth[a] - depth[b];
		for (int j = 0; diff; j++) {
			if (diff % 2) {
				distance += dist[a][j];
				a = parent[a][j];
			}
			diff /= 2;
		}
		if (a != b) {

			for (int j = 16; j >= 0; j--) {
				if (parent[a][j] != -1 && parent[a][j] != parent[b][j]) {
					distance += dist[a][j] + dist[b][j];
					a = parent[a][j];
					b = parent[b][j];
				}
			}
			distance += dist[a][0];
			distance += dist[b][0];
			a = parent[a][0];
		}

		cout << distance << endl;

	}


	return 0;
}
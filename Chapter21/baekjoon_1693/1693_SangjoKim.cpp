#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
int n;

vector<int> adj[100001];

int dp[100001][4];
bool visited[100001];

int solve(int here, int color) {
	//cout << here << " " << color << endl;
	int& ret = dp[here][color];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		int ret2 = 0x3f3f3f3f;
		if (!visited[there]){ 
			visited[there] = true;
			for (int c = 0; c < 4; c++) {
				if (c == color) continue;
				ret2 = min(ret2, solve(there, c));
			}
			visited[there] = false;
			ret += ret2;
		}
	}
	return ret += color + 1;
}

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n;

	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b;
		a--; b--;
		adj[a].push_back(b); adj[b].push_back(a);
	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			dp[i][j] = -1;
		}
	}
	
	for (int i = 0; i < n; i++) {
		visited[i] = false;
	}

	int ret = 0x3f3f3f3f;
	visited[0] = true;
	for (int c = 0; c < 4; c++) {
		ret = min(ret, solve(0, c));
	}
	visited[0] = false;

	cout << ret << endl;
	

	
	return 0;
}
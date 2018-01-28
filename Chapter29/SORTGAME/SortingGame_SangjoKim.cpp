#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;
int n;
int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int tc; cin >> tc;
	while (tc--) {
		cin >> n;
		vector<int> arr = vector<int>(n);
		for (int i = 0; i < n; i++) cin >> arr[i];

		vector<int> ans = arr; sort(ans.begin(), ans.end());

		map<vector<int>, int> dist;

		queue<vector<int> > q;

		dist[arr] = 0;
		q.push(arr);
		int ret;
		while (!q.empty()) {
			
			vector<int> here = q.front();
			q.pop();

			if (here == ans) {
				ret = dist[here];
				break;
			}

			int nowD = dist[here];

			for (int i = 0; i < n; i++) {
				for (int j = i + 2; j <= n; j++) {
					reverse(here.begin() + i, here.end() + j);
					if (dist.count(here) == 0) {
						dist[here] = nowD + 1;
						q.push(here);
					}
					reverse(here.begin() + i, here.end() + j);
				}
			}
		}

		cout << ret << endl;
	}


	return 0;
}
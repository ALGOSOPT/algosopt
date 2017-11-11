#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <map>

using namespace std;
int n;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; scanf("%d", &TC);

	for (int test_case = 1; test_case <= TC; test_case++) {
		scanf("%d", &n);
		map<int, int> m;
		int sum = 0;
		for (int i = 0; i < n; i++) {
			int p, q; scanf("%d %d", &p, &q);
			if (m.size() == 0)
				m[p] = q;
			else {
				map<int, int>::iterator it = m.lower_bound(p);
				if ((it == m.end() || it -> second < q)) {
					if (it != m.begin() || it != m.end()) {
						while (true) {
							if (it->second > q) break;

							if (it == m.begin()) {
								m.erase(it);
								break;
							}
							else {
								map<int, int>::iterator temp = it;
								temp--;
								m.erase(it);
								it = temp;
							}
						}
					}
					m[p] = q;
				}
			}
			sum += m.size();
		}
		cout << sum << endl;
	}

	return 0;
}
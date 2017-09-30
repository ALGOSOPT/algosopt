#include <iostream>
#include <cstdio>
#include <list>

using namespace std;


int n, k;
int main() {

	freopen("input.txt", "r", stdin);

	int TC; scanf("%d", &TC);

	while (TC--) {

		scanf("%d%d", &n, &k);

		list<int> soldier;

		for (int i = 0; i < n; i++) soldier.push_back(i + 1);

		list<int>::iterator it = soldier.begin();

		while (soldier.size() > 2){
		
			it = soldier.erase(it);

			if (it == soldier.end()) it = soldier.begin();

			for (int i = 0; i < k - 1; i++) {
				it++;
				if (it == soldier.end()) it = soldier.begin();
			}
		}


		cout << soldier.front() << " " << soldier.back() << endl;

	}


	return 0;
}
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;



int N;

typedef pair<long, int> Event;
int main() {

	freopen("input.txt", "r", stdin);

	cin >> N;
	vector<Event> event;

	for (int i = 0; i < N; i++) {
		long temp1, temp2;
		cin >> temp1 >> temp2;
		
		event.push_back(make_pair(temp1, 1));
		event.push_back(make_pair(temp2, -1));
	}

	sort(event.begin(), event.end());

	int count = 1;

	long beforePoint = event[0].first;

	long ret = 0;

	for (int i = 1; i < event.size(); i++) {

		long herePoint = event[i].first;
		int openOrClose = event[i].second;


		if (count > 0) {
			ret += herePoint - beforePoint;
		}
		count += openOrClose;

		beforePoint = herePoint;
	}


	cout << ret << endl;

	return 0;
}
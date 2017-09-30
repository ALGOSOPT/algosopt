#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {

	int n;
	cin >> n;
	
	vector<pair<int, int> > line = vector<pair<int, int> >();
	for (int i = 0; i < n; i++) {
		int input1, input2;
		cin >> input1 >> input2;
		line.push_back(make_pair(input1, input2));
	}
		
	sort(line.begin(), line.end());

	//for (int i = 0; i < line.size(); i++)
	//	cout << line[i].first << " " << line[i].second << "\n";

	int result = 0;
	int end1 = 0;
	int end2 = 0;
	for (int i = 0; i < line.size(); i++) {
		if ((line[i].first >= end1) && (line[i].first <= end2)) {
			end2 = max(end2, line[i].second);
		}
		else {
			result += end2 - end1;
			end1 = line[i].first;
			end2 = line[i].second;
		}
	}

	result += end2 - end1;
	cout << result;
}
#include <iostream>
#include <cstdio>
#include <list>
#include <string>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);

	list<char> li;
	int n;
	string st;
	cin >> st;

	for (int i = 0; i < st.size(); i++) {

		li.push_back(st[i]);
	}
	cin >> n;
	
	list<char>::iterator it = li.end();

	for (int order = 0; order < n; order++) {

		char instructor, pushedChar;
		cin >> instructor;

		if (instructor == 'P') cin >> pushedChar;

		switch (instructor){
		case 'L' : 
			if (it != li.begin()) it--;
			break;
		case 'D':
			if (it != li.end()) it++;
			break;
		case 'B':
			if (it != li.begin()) {
				it--;
				it = li.erase(it);
			}
			break;
		case 'P':
			li.insert(it, pushedChar);
			break;
		default:
			break;
		}
	}
	for (it = li.begin(); it != li.end(); it++) {
		cout << *it;
	}
	cout << endl;

	return 0;
}
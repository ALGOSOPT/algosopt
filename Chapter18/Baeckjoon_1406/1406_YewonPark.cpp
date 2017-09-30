#include<cstdio>
#include<iostream>
#include<list>
#include<string>

using namespace std;

int main() {

	list<char> editor;
	string input;
	cin >> input;
	for (int i = 0; i < input.size(); i++)
		editor.push_back(input[i]);
	int n;
	cin >> n;
	list<char>::iterator now = editor.end();
	
	for (int i = 0; i < n; i++) {
		cin >> input;
		if (input == "L" && now != editor.begin())
			now--;
		else if (input == "D" && now != editor.end())
			now++;
		else if (input == "B" && now != editor.begin()) {
			now--;
			now = editor.erase(now);
		}
		else if (input == "P") {
			char temp;
			cin >> temp;
			editor.insert(now, temp);
		}
	}
	for (now = editor.begin(); now != editor.end(); now++)
		cout << *now;

	return 0;
}


#include<cstdio>
#include<iostream>
#include<list>

using namespace std;

int main() {
	
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		list<int> person;
		for (int i = 1; i <= n; i++)
			person.push_back(i);
		list<int>::iterator now = person.begin();//���� ���� ���
		while (n > 2) {
			//1. kill
			now = person.erase(now);//now�� ���� ���� ���Ұ� now�� �����
			if (now == person.end())
				now = person.begin();
			n--;
			//2. find next person
			for (int i = 0; i < k - 1; i++) {
				now++;
				if (now == person.end())
					now = person.begin();
			}
		}
		cout << person.front() << " " << person.back() << "\n";
	}
}

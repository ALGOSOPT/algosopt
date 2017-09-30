
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
		list<int>::iterator now = person.begin();//이제 죽을 사람
		while (n > 2) {
			//1. kill
			now = person.erase(now);//now를 지운 다음 원소가 now에 저장됨
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

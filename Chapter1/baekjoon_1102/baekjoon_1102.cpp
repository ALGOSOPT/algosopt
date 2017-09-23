#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<string>

using namespace std;

//n이 16보다 작거나 같은 자연수임을 주목하자
//16자리로 표현이 가능해야함

int n, p;
int cost[16][16];
int cache[1 << 16] = { -1, };

int bitCount(int x) {
	if (x == 0) return 0;
	return x % 2 + bitCount(x / 2);
}

int solve(int on) {//on은 켜져있는 것
	//기저사례 : 만약 on의 갯수가 최소 켜져있어야 할 갯수를 충족하면 끝
	if (bitCount(on) >= p)
		return 0;

	int& ret = cache[on];
	if (ret != -1)
		return ret;

	ret = 50 * 16;
	
	//현재 켜져있는 것을 보면서 다른것을 하나씩 켜본다
	for (int i = 0; i < n; i++) {
		if (on & (1 << i)) {
			//켜져있으면
			for (int j = 0; j < n; j++) {//켜져있지 않은 다른 것 켜봄
				if ((on & (1 << j)) == 0)
					ret = min(ret, solve(on | (1 << j)) + cost[i][j]);
			}
		}
	}

	return ret;
}

int main() {
	
	cin >> n;
	memset(cache, -1, sizeof(cache));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> cost[i][j];

	string input_first;
	cin >> input_first;//처음 상태
	int first = 0;
	//비트마스크로 표현해야함
	for (int i = 0; i < input_first.length(); i++) {
		if (input_first[i] == 'Y')
			first |= (1 << i);
	}
	cin >> p;
	//cout << first << "\n";
	//불가능한 경우는 어떤 경우니...?
	if (!first | p>input_first.length())
		cout << -1;
	else
		cout << solve(first);
	
}
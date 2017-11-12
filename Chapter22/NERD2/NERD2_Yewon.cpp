#include<iostream>
#include<cstdio>
#include<vector>
#include<map>

using namespace std;

bool isDominated(map<int, int>& tree, int x, int y) {//들어오려는 참가자가 지배되어 있는 지 체크
	map<int, int>::iterator it = tree.lower_bound(x);//들어오려는 참가자보다 문제 수가 조금 더 많은 참가자
	if (it == tree.end()) 
		return false;//문제 수가 더 많은 참가자가 없으면 지배되지 않음
	return y < it->second;
}

void isDominating(map<int, int>& tree, int x, int y) {
	map<int, int>::iterator it = tree.lower_bound(x);
	if (it == tree.begin())//문제 수가 더 적은 참가자가 없으면 지배하지 않음
		return;
	it--;//들어오려는 참가자보다 문제 수가 조금 더 적은 참가자(A)
	while (true) {
		if (y < it->second)//들어오려는 참가자가 지배하지 않으면
			break;
		//들어오려는 참가자가 지배하면 지배하는 점을 삭제한다
		//지배되는 점이 가장 왼쪽에 있는 점인 경우 삭제하고 끝냄
		if (it == tree.begin()) {
			tree.erase(it);
			break;
		}
		//아닌 경우 삭제하고 더 문제수가 적은 참가자를 봐야함
		else {
			map<int, int>::iterator it_r = it;
			--it;
			tree.erase(it_r);
		}
	}
}

int main() {

	int c;
	cin >> c;

	while (c--) {
		int n;
		cin >> n;

		map<int, int> tree;
		int result = 0;

		while (n--) {
			int p, q;
			cin >> p >> q;

			//참가자(A)의 문제 수 다음으로 문제 수가 많은 참가자(B)와 라면 수를 비교
			if (isDominated(tree, p, q))
				result += tree.size();
			continue;
			//참가자(A)의 문제 수 다음으로 문제 수가 적은 참가자(B)와 라면 수를 비교
			//삭제와 삽입 연산 수행
			isDominating(tree, p, q);
			map<int, int>::iterator a = tree.lower_bound(p);
			tree[p] = q;
			result += tree.size();
		}

		cout << result;
		
	}
	return 0;
}

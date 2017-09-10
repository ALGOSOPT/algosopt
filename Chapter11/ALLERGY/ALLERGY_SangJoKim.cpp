#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

typedef long long int ll;

using namespace std;


int n, m;
//friends[string] = string이름을 같은 아이의 번호
map<string, int> friends;

//foods[i][j] 는 i번 음식을 먹을 수 있는 j번째 아이. 
vector<pair<int, ll> > foods;

//모든 친구가 음식을 다 먹었는지 check
ll checkAllFrientAte;
//정답
int best;


//완전탐색
//foodNumber 탐색하는 음식의 번호
//numCookedFood 요리를 한 음식의 수
//checkEatableFriends 지금까지 음식을 먹은 친구들(비트마스크)
void brute_force(int foodNumber,  int numCookedFood, ll checkEatableFriends) {

	//기저사례
	//모든 친구가 다 먹을 수 있으면 -> 답의 후보
	if (checkEatableFriends == checkAllFrientAte) {
		best = min(best, numCookedFood);
		return;
	}

	//모든 요리를 다했지만, 모든 친구가 먹을 수 없다. -> 답이 안됨
	if (foodNumber == m) {
		return;
	}

	//최적화.. 남은 음식들을 다 먹어도 한 명이라도 못먹는 경우가 있는 경우 그냥 리턴

	//최적화.. 지금까지 한 음식의 숫자가 best보다 크면 의미 없음
	if (numCookedFood >= best) return;
	//





	//foodNumber의 요리를 하는 경우
	ll EatableFriendsList = checkEatableFriends;
	EatableFriendsList |= foods[foodNumber].second;
	brute_force(foodNumber + 1, numCookedFood + 1, EatableFriendsList);


	//foodNumber의 요리를 하지 않는 경우
	brute_force(foodNumber + 1, numCookedFood, checkEatableFriends);


}
int main() {
	freopen("input.txt", "r", stdin);

	int TC; cin >> TC;
	//TC = 1;
	while (TC--) {
		//초기화
		
		friends.clear(); foods.clear();

		cin >> n >> m;
		//친구 이름 입력
		for (int i = 0; i < n; i++) {
			string temp; cin >> temp;
			friends[temp] = i;
		}
		
		int numDeleteFood = 0;
		//음식 입력
		for (int i = 0; i < m; i++) {
			int num; cin >> num;
			int candFood = 0;
			for (int j = 0; j < num; j++) {
				string temp; cin >> temp;
				candFood |= (1 << friends[temp]);
			}

			bool checkExistence = true;
			for (int j = 0; j < foods.size(); j++) {
				if (foods[j].second == candFood) {
					checkExistence = false;
					break;
				}
			}
			//최적화.. 먹을 수 있는 아이가 똑같은 음식인 경우 삭제 -> 탐색공간 줄이기
			if (!checkExistence) {
				numDeleteFood++;
			}
			else {
				foods.push_back(make_pair(-1 * __popcnt(candFood),candFood));
			}
		}

		m -= numDeleteFood;

		//최적화.. 음식을 먹을 수 있는 아이의 수대로 정렬 -> 탐색순서 바꾸기
		sort(foods.begin(), foods.end());
		


		checkAllFrientAte = (1 << n) - 1;
		best = 0x3f3f3f3f;

		/*for (int i = 0; i < foods.size(); i++) {
			for (int j = 0; j < foods[i].size(); j++) {
				cout << foods[i][j] << " ";
			}
			cout << endl;
		}*/

		brute_force(0, 0, 0);
		

		cout << best << endl;

		

	}
	return 0;
}
https://algospot.com/judge/problem/read/ALLERGY


이번 문제야 말로 최적화를 공부하기 좋은 문제입니다. 우리 이 문제를 통해 최적화에 대해 심도 있는 토의를 하고 인사이트를 얻어 봅시다.


### NP완비

<pre>
**11.9 알러지 문제를 해결하는 첫 번째 조합 탐색 알고리즘**
</pre>

```c++

int n, m;

//eaters[food] = food를 먹을 수 있는 친구들의 번호
vector<int> eaters[50];
int best;
//food : 이번에 고려해야할 음식의 번호
//edible : 지금까지 고른 음식 중 i번 친구가 먹을 수 있는 음식의 수
//chosen : 지금까지 고른 음식의 수

void slowSearch(int food, vector<int>& edible, int chosen){

	//간단한 가지치기
	if(chosen >= best) return;

	//기저사례 : 모든 음식에 대해 만들지 여부를 결정했으면,
	//모든 친구가 음식을 먹을 수 있는지 확인하고 그렇다면 최적해를 갱신한다.
	if(food == m){
		if(find(edible.begin(), edible.end(), 0) == edible.end())
			best = chosen;
		return;
	}


	//food를 만들지 않는 경우
	slowSearch(food + 1, edible, chosen);

	//food를 만드는 경우
	for(int i = 0; i < eaters[food].size(); i++){
		edible[eaters[food][j]]++;
	}

	slowSearch(food + 1, edible, chosen + 1);

}


```


<pre>
	Q. 이 코드에서 탐색을 하는 방법에 대해 그림으로 설명해봅시다.
	   왜 NP완비 문제인 걸까요?
	   
	Q. 이 코드에서 좀 더 최적화하는 방법은 무엇이 더 있을까요?


</pre>


### Q. 이 코드에서 좀 더 최적화하는 방법은 무엇이 더 있을까요?


__ 11.10 문제를 해결하는 두 번째 조합 탐색 알고리즘__

```c++
int n, m;

//canEat[i] : i번 친구가 먹을 수 있는 음식의 집합
//eaters[i] : i번 음식을 먹을 수 있는 친구들의 집합

vector<int> canEat[50], eaters[50];
int best;

//chosen : 지금까지 선택한 음식의 수
//edible[i] : 지금까지 고른 음식 중 i번 친구가 먹을 수 있는 음식의 수
void search(vector<int>& edible, int chosen){

	//간단한 가지치기
	if(chosen >= best) return;
	//아직 먹을 음식이 없는 첫 번째 친구를 찾는다.
	int first = 0;
	while(first < n && edible[first] > 0) first++;

	//모든 친구가 먹을 음식이 있는 경우 종료한다.
	if(first == n){
		best = chosen; 
		return;
	}

	for(int i = 0; i < canEat[first].size(); i++){
		int food = canEat[first][i];
		for(int j = 0; j < eaters[food].size(); j++){
			edible[eaters[food][j]]++;
		}
		search(edible, chosen + 1);
		for(int j = 0; j < eaters[food].size(); j++){
			edible[eaters[food][j]]++;
		}
	}
}

```
<pre>
	Q.//모든 친구가 먹을 음식이 있는 경우 종료한다.
	if(first == n){
		best = chosen; 
		return;
	}
	에서 왜 best = min(best, chosen)이 아닌가요?
	
	Q. search에서 food인자가 없어도 되는 이유에 대해 말해 봅시다
</pre>




# 우리가 논의했던 최적화 방법들을 모두 녹여 코드를 짜보는 시간을 가집시다.

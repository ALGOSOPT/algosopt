https://algospot.com/judge/problem/read/BOARDCOVER2


## 문제 요구 사항 파악
<pre>
이 문제를 모두 풀어보셨나요?
이 문제를 보고 나서 아 우선 완전 탐색을 해야겠구나라고 생각했으면 좋은 접근 순서입니다.
그런데 어떻게 완전 탐색을 하면 될지 머릿속에서는 떠올랐을텐데 막상 구현하려니 
뭘 어떻게 뭐부터 해야할지 헷갈리 셨을 것 입니다.

네 그렇습니다. 이 문제는 조합탐색의 가지치는 좋은 문제인 것 같지 않아요.
구현이 어려운 문제입니다. ㅜㅜ

하지만, 책에선 간단하게 가지치는 방법에 대해 소개하고 있습니다.
혹시 완전탐색의 탐색 범위를 이런 방법으로 줄여보았다라고 하는 분 있으면 말해봅시당.
 



이 문제를 책을 안보고 풀기에는 힘들었을 것입니다.
왜냐하면 구현해야할 요구사항이 많기 때문입니다.

구현 요구사항들이 무엇들이 있었는지 한 번 말해볼까용?
</pre>



### 전처리
<pre>

우선 입력받은 블록을 어떻게 처리하면 좋을까요?



회전을 한 것을 왜 미리 모아두는지 말해봅시다.
</pre>


__코드 11.7 블록의 회전된 형태를 계산하고 상대좌표의 목록으로 변환하기__
```c ++
//블록의 각 회전된 형태를 상대 좌표의 목록으로 저장해둔다.
vector<vector<pair<int, int> > > rotations;
//블록의 크기
int blockSize;
//2차원 배열 arr을 시계방향으로 90도 돌린 결과를 반환한다.
vector<string> rotate(const vector<string>& arr){
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for(int i = 0; i < arr.size(); i++){
		for(int j = 0; j < arr[0].size(); j++){
			ret[j][arr.size() - i - 1] = arr[i][j];
	return ret;
}

```
<pre>

Q. rotations을 pair<int, int>로 저장한 이유는 무엇입니까?

Q. 90도 회전하는 공식은 왜 저렇게 나오는 걸까요?


</pre>


__코드 11.7 블록의 회전된 형태를 계산하고 상대좌표의 목록으로 변환하기__

```c++

//block의 네가지 회전 형태를 만들고 이들의 상대 좌표릐 목록으로 변환한다.
void generateRotations(vector<string> block){
	rotations.clear();
	rotations.resize(4);
	for(int rot = 0; rot < 4; rot++){
		int originY = -1; int originX = -1;
		for(int i = 0; i < block.size(); i++)
			for(int j = 0; j < block[i].size(); j++)
				if(block[i][j] == '#'){
					if(originY == -1){
						//가장 윗줄 맨 왼쪽에 있는 칸이 '원점'이 된다.
						originY = i;
						originX = j;
					}
					//각 칸의 위치를 원점으로부터의 상대좌표로 표현한다.
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
			//블록을 시계 방향으로 90도 회전한다.
			block = rotate(block);
		}
	
	//네 가지 회전 형태 중 중복이 있을 경우 이를 제거한다.
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	//블록이 몇 칸 짜리인지 저장해 둔다.
	blockSize = rotations[0].size();
}
				

```

<pre>
Q. 그림 11.8의 4가지 회전에서 번호를 메겨볼까요?

Q. 왜 블록의 가장 맨 위 가장 맨 왼쪽 것이 0,0이 되었을까요?

</pre>



### 완전탐색

__코드 11.8 게임판 덮기 2 문제를 완전 탐색 알고리즘__

```c
//게임판의 정보
int boardH, boardW;
vector<string> board;

//게임판의 각 칸이 덮였는지를 나타낸다. 1이면 검은 칸이거나 이미 덮은 칸, 0이면 빈칸
int covered[10][10];

//지금까지 찾은 최적해
int best;

//(y, x)를 왼쪽 위칸으로 해서 주어진 블록을 delta = 1이면 놓고, -1이면 없댄다.
//블록을 놓을 때 이미 놓인 블록이나 검은 칸과 겹치면 거짓을, 아니면 참을 반환한다.
bool set(int y, int x, const vector<pair<int,int> >& cells, int delta) {
	bool ok = true;
	for(int i = 0; i < cells.size(); i++) {
		int cy = y + cells[i].first, cx = x + cells[i].second;
		if(cy < 0 || cx < 0 || cy >= boardH || cx >= boardW)
			ok = false;
		else {
			covered[cy][cx] += delta;
			if(covered[cy][cx] > 1) ok = false;
		}
	}
	return ok;
}


//placed : 지금까지 놓은 블록의 수
void search(int placed){
	//아직 채우지 못한 빈 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다.
	int y = -1, x = -1;
	for(int i = 0; i < boardH; i++){
		for(int j = 0; j < boardW; j++)
			if(covered[i][j] == 0){
				y = i;
				x = j;
				break;
			}
		if(y != -1) break;
	}

	//기저사례 : 게임판의 모든 칸을 처리한 경우
	if(y == -1){
		best = max(best, placed);
		return;
	}

	//이 칸을 덮는다.
	for(int i = 0; i < rotations.size(); i++){
		if(set(y, x, rotations[i], 1))
			search(placed + 1);
		set(y, x, rotations[i], -1);
	}

	//이 칸을 덮지 않고 '막아'둔다.
	covered[y][x] = 1;
	search(placed);
	covered[y][x] = 0;
}

int solve(){
	best = 0;

	//covered 배열을 초기화 한다.
	for(int i = 0; i < boardH; i++){
		for(int j = 0; j < boardW; j++){
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);
		}
	}
	search(0);
	return best;
}

```
<pre>

이 코드는 엄청나게 배울점이 많습니다. 차근차근 살펴보면서 실무에서도 우리가 쓸 수 있도록
우리의 것으로 만들어봅시다.

Q. set 함수의 동작을 설명해봅시다. 어떤 기능을 하죠? 이런 코드가 과연 좋은 코드인 걸까요?

Q. 이중 for문을 나오기 위해서 어떻게 코드를 짰는가 살펴봅시다.

Q. 기저 사례를 해석해봅시다.

Q. search(placed)를 하기전에 covered를 막는 이유는 무엇입니까?

</pre>



### 가지치기

<pre>
다음 코드를 해석해봅시다.
</pre>

```c++
// placed: 지금까지 놓은 블록의 수
// blanks: 남은 빈칸의 수
void search(int placed, int blanks) {
	// 빈칸 중 가장 윗줄 왼쪽에 있는
	int y = -1, x = -1;
	for(int i = 0; i < boardH; i++) {
		for(int j = 0; j < boardW; j++)
			if(covered[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if(y != -1) break;
	}
	// 기저 사례: 게임판의 모든 칸을 처리한 경우
	if(y == -1) {
		best = max(best, placed);
		return;
	}

	// 가지치기
	int upperBound = blanks / blockSize + placed;
	if(upperBound <= best) return;

	// 이 칸을 덮는다
	for(int i = 0; i < rotations.size(); i++) {
		if(set(y, x, rotations[i], 1))
			search(placed+1, blanks - blockSize);
		set(y, x, rotations[i], -1);
	}

	// 이 칸을 덮지 않고 막아 둔다
	covered[y][x]++;
	search(placed, blanks - 1);
	covered[y][x]--;
}
```

- 저자의 가지치기 말고는 또 어떤 아이디어가 있을 수 있을까요?

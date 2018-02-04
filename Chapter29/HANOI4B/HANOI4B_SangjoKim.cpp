#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
using namespace std;
int n;

struct State{
	vector<vector<int> > pillar;
	State(){
		pillar = vector<vector<int> >(4);
	}
	vector<State> getAdjacent(){
		vector<State> result;
		for(int from = 0; from < 4; from++){
			int f = pillar[from].back();
			for(int to = 0; to < 4; to ++){
				if(from != to){
					int t = pillar[to].back();
					if(t > f){
						State new_state = *this;
						new_state.pillar[from].pop_back();
						new_state.pillar[to].push_back(f);
						result.push_back(new_state);
					}
				}
			}
		}
	}
	bool operator < (const State& rhs) const{
		return this -> pillar < rhs.pillar;
	}
	bool operator == (const State& rhs) const{
		return this -> pillar == rhs.pillar;
	}
	bool operator = (const State& rhs){
		this -> pillar = rhs.pillar;
	}

};

typedef map<State, int> StateMap;

int sgn(int x){
	if(!x) return 0;
	return x > 0? 1 : -1;
}

int incr(int x){
	if(x < 0)	return x - 1;
	return x + 1;
}

int bidirectional(State start, State finish){

	map<State, int> c;

	queue<State> q;

	if(start == finish)	return 0;

	q.push(start); c[start] = 1;
	q.push(finish); c[finish] = -1;

	while(!q.empty()){
		State here = q.front();

		q.pop();
		vector<State> adjacent = here.getAdjacent();

		for(int i = 0; i < adjacent.size(); i++){
			map<State, int>::iterator it = c.find(adjacent[i]);
			printf("1\n");			

			if(it == c.end()){
				c[adjacent[i]] = incr(c[here]);
				q.push(adjacent[i]);
			}
			else if(sgn(it ->second) != sgn(c[here]))
				return abs(it -> second) + abs(c[here]) - 1;
		}

	}
	return -1;
}
int main(){
	freopen("input.txt","r",stdin);
	setbuf(stdout, NULL);

	int TC;	scanf("%d", &TC);

	while(TC--){
		scanf("%d", &n);
		State start;
		for(int i = 0; i < 4; i++){
			int buf; scanf("%d", &buf);
			for(int j = 0; j < buf; j++){
				int buf2; scanf("%d", &buf2);
				start.pillar[i].push_back(buf2);
			}
		}
		State finish;
		for(int i = n; i > 0; i--){
			finish.pillar[3].push_back(i);
		}
		printf("%d\n", bidirectional(start, finish));

	}

	return 0;
}
#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
#include<algorithm>
#include<vector>

using namespace std;

int c, n;

map<vector<int>, int> distance;

void bfs(int n){
	
	queue<vector<int> > q;
	
	vector<int> sorted(n);
	for(int i=0; i<n; i++)
		sorted[i] = i;
	
	distance[sorted] = 0;////////reference ambiguous
	q.push(sorted);
	
	while(!q.empty()){
		
		vector<int> now = q.front();
		q.pop();
		
		//if(now == sorted){
		//	return distance[now];
		//}
		
		int cost = distance[now];
		for(int i=0; i<n; i++){
			for(int j=i+2; j<=n; j++){
				reverse(now.begin()+i, now.begin()+j);
				if(distance.count(now) == 0){
					distance[now] = cost + 1;
					q.push(now);
				}
				reverse(now.begin()+i, now.begin()+j);
			}
		}
	}
}

int solve(vector<int> input){
	//상대적 크기를 계산함
	int n = input.size();
	vector<int> input2(n);
	for(int i=0; i<n; i++){
		int smaller = 0;
		for(int j=0; i<n; j++){
			if(input[i]>input[j])
				smaller++;
		}
		input2[i] = smaller;
	}
	return distance[input2];
}

int main(){
	
	cin >> c;
	
	//for(int i=1; i<=8; i++)
	//	bfs(i);
		
	while(c--){
		
		cin >> n;
		vector<int> input;
		int temp;
		for(int i=0; i<n; i++){
			scanf("%d", &temp);
			input.push_back(temp);
		}
		
		bfs(n);
		printf("%d\n", solve(input));
	}
} 

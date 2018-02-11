#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
const string im = "IMPOSSIBLE";
vector<vector<int> > adj;
void getEulerCirciut(int here, vector<int>& circiut){
	for(int there = 0; there < adj.size(); there++){
		while(adj[here][there] > 0){
			adj[here][there]--;
			adj[there][here]--;
			getEulerCirciut(there, circiut);
		}
	}
	circiut.push_back(here);
}
int main(){
	freopen("input.txt","r",stdin);
	setbuf(stdout, NULL);

	int TC;	scanf("%d", &TC);

	while(TC--){
		int N;	scanf("%d", &N);
		string word[101];
		for(int i = 0; i < N; i++){
			cin>>word[i];
		}
		adj.clear();
		adj = vector<vector<int> >(N, vector<int>(N,0));

		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				if(i == j) continue;

				if(word[i][word[i].size() -1 ] == word[j][0]){
					adj[i][j] = 1;
				}
			}
		}
		// for(int i = 0; i < N; i++){
		// 	for(int j = 0; j < N; j++){
		// 		cout<<adj[i][j]<<" ";
		// 	}
		// 	cout<<endl;
		// }
		// cout<<endl;
		vector<int> Euler;
		getEulerCirciut(0, Euler );

		if(Euler.size() != N){
			cout<<im<<endl;
		}
		else{
			reverse(Euler.begin(), Euler.end());
			for(int i = 0; i < N; i++){
				cout<<word[Euler[i]]<<" ";
			}
			cout<<endl;
		}
		// cout<<endl;

	}






	return 0;
}
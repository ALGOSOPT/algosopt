#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int> > adj;

void getEulerCircuit(int here, vector<int>& circuit){
	for(int there = 0; there < adj.size(); there++)
		while(adj[here][there] > 0){
			adj[here][there]--;
			adj[there][here]--;
			getEulerCircuit(there, circuit);
		}
	circuit.push_back(here);
}

int main(){
	
	//freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	
	adj = vector<vector<int> >(n);
	for(int i=0; i<n; i++){
		int degree = 0;
		for(int j=0; j<n; j++){
			int temp;
			scanf("%d", &temp);
			adj[i].push_back(temp);
			degree += temp;
		}	
		if(degree%2){
			printf("-1");
			return 0;	
		}
	}
		
	vector<int> result;
	getEulerCircuit(0, result);
	reverse(result.begin(), result.end());
	for(int i=0; i<result.size(); i++)
		printf("%d ", result[i]+1);
}

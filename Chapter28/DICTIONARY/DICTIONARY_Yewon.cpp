#include<iostream>
#include<vector>
#include<stack>
#include<string>

using namespace std;

vector<string> input;
vector<vector<char> > graph;
vector<bool> visit;
vector<bool> finish;
stack<char> s;

bool invalid;

void dfs(char x){
	visit[x-97] = true;
	for(int i=0; i<graph[x-97].size(); i++){
		char next = graph[x-97][i];
		if(!visit[next-97])
			dfs(next);
		else if(!finish[next-97]){
			invalid = true;			
		}
	}
	//더 들어갈 곳이 없으면
	s.push(x);
	finish[x-97] = true; 
}

void dfsALL(){
	for(int i=0; i<graph.size(); i++){
		if(!visit[i])
			dfs(i+97);
	}
}

int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		
		invalid = false;
		input = vector<string>();
		graph = vector<vector<char> >(26);
		visit = vector<bool>(26, false);
		finish = vector<bool>(26, false);
		s = stack<char>();
		
		for(int i=0; i<n; i++){
			string temp;
			cin >> temp;
			input.push_back(temp);
		}
					
		for(int i=0; i<n-1; i++){
			int j=0;
			while(j<input[i].size() && j<input[i+1].size()){
				if(input[i][j] != input[i+1][j]){
					graph[input[i][j]-97].push_back(input[i+1][j]);
					break;
				}
				j++;
			}
		}
		
		/*
		for(int i=0; i<graph.size(); i++){
			printf("%c : ", i+97);
			for(int j=0; j<graph[i].size(); j++)
				cout << graph[i][j] << " ";
			cout << "\n";
		}
		*/
			
		dfsALL();
		
		if(invalid){
			cout << "INVALID HYPOTHESIS\n";
			continue;
		}
		
		while(!s.empty()){
			printf("%c", s.top());
			s.pop();	
		}
		
		cout << "\n";
	}
}

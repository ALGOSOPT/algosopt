#include<iostream>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

//인접행렬로 구현 
vector<string> input[26][26];//간선 정보가 저장됨(input[a][e] = [apple, ace]  
int adj[26][26];//정점 사이의 간선 갯수

//trail 민들기 위해 필요 
int inedge[26];//정점마다 들어오는 간선 갯수
int outedge[26];//정점마다 나가는 간선 갯수 
 
vector<char> circuit;

void getEulerCircuit(int here, vector<char>& circuit){
	for(int there = 0; there < 26; there++){
		while(adj[here][there]>0){
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	}
	//더이상 갈 정점이 없으면 
	circuit.push_back(here);
}

int main(){
	
	int t;
	cin >> t;
	while(t--){
		
		int n;
		cin >> n;
		
		//전역변수 초기화 
		for(int i=0; i<26; i++)
			for(int j=0; j<26; j++)
				input[i][j].clear();
		memset(adj, 0, sizeof(adj));
		memset(inedge, 0, sizeof(inedge)); 
		memset(outedge, 0, sizeof(outedge));
		circuit = vector<char>();
		for(int i=0; i<n; i++){
			string temp;
			cin >> temp;
			input[temp[0] - 'a'][temp[temp.size()-1] - 'a'].push_back(temp);
			adj[temp[0]-'a'][temp[temp.size()-1]-'a']++;
			inedge[temp[temp.size()-1]-'a']++;
			outedge[temp[0]-'a']++;
		}
		
		bool invalid = false;
		char in = -1, out = -1;

		//circuit으로 만들어줌		
		vector<int> diff_edge = vector<int>();
		for(int i=0; i<26; i++){
			if(inedge[i] != outedge[i])
				diff_edge.push_back(i);
		} 
		
		if(diff_edge.size() == 2){
			int in = -1, out = -1;
			if(inedge[diff_edge[0]] + 1 == outedge[diff_edge[0]] && outedge[diff_edge[1]] + 1 == inedge[diff_edge[1]]){
				in = diff_edge[1], out = diff_edge[0];
			}else if(outedge[diff_edge[0]] + 1 == inedge[diff_edge[0]] && inedge[diff_edge[1]] + 1 == outedge[diff_edge[1]]){
				in = diff_edge[0], out = diff_edge[1];	
			}	
			if(in != -1 && out != -1){
				adj[in][out]++;
				getEulerCircuit(out, circuit);
				for(int i=circuit.size()-1; i>1; i--){
					cout << input[circuit[i]][circuit[i-1]][0] << " ";
					input[circuit[i]][circuit[i-1]].erase(input[circuit[i]][circuit[i-1]].begin());
				}
				cout << "\n";
				continue;	
			}
		}
		else if(diff_edge.size() == 0){
			int start;
	 		for(int i=0; i<26; i++)
	 			if(inedge[i] != 0){
	 				start = i;
	 				break;
			 	}
	 	
			getEulerCircuit(start, circuit);
			for(int i=circuit.size()-1; i>0; i--){
				cout << input[circuit[i]][circuit[i-1]][0] << " ";
				input[circuit[i]][circuit[i-1]].erase(input[circuit[i]][circuit[i-1]].begin());
			}
			cout << "\n";
			continue;
		}
		
		cout << "IMPOSSIBLE\n";	
		
	}
	
}

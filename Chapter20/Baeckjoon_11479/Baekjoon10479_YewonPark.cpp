#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

string S;

int N, d;

vector<int> SA;
vector<int> LCP;

vector<int> group;

bool cmp(int i, int j){
	if(group[i] != group[j])
		return group[i] < group[j];
		
	i += d;
	j += d;
	return (i<N && j<N) ? (group[i] < group[j]) : (i > j);
}

void constructSA(){
	
	for(int i=0; i<N; i++){
		SA[i] = i;
		group[i] = S[i];
	}
	
	for(d = 1; ; d *= 2){
		sort(SA.begin(), SA.end(), cmp);
		
		vector<int> newGroup(N, 0);
		
		for(int i=0; i< N-1; i++)
			newGroup[i+1] = newGroup[i] + cmp(SA[i], SA[i+1]);
			
		for(int i=0; i<N; i++)
			group[SA[i]] = newGroup[i];
			
		if(newGroup[N-1] == N-1)
			break;
	}
}

void getLCP(){
	
	for(int i=0, k=0; i<N; i++, k = max(k-1, 0)){
		if(group[i] == N-1)
			continue;
		for(int j=SA[group[i] + 1]; S[i+k] == S[j+k]; k++);
		LCP[group[i]] = k;
	}
}

int main(){
	
	cin >> S;
		N = S.size();
	
		SA = vector<int>(N);
		LCP = vector<int>(N-1);
		group = vector<int>(N);
	
		constructSA();
		getLCP();
		/*
		for(int i=0; i<N; i++){
			cout << SA[i] << " ";
		}
		cout << "\n";
		for(int i=0; i<N-1; i++){
			cout << LCP[i] << " ";
		}
		cout << "\n";
		*/
		

		long long result = N - SA[N-1];
		for(int i=0; i<N-1; i++){
			result += N - SA[i] - LCP[i];
		}	
		cout << result;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
const int INF = 987654321;
int N;
int P;
int cost[20][20];
string isRepair;
int cache[20][20];
int No_Num = 0;
int repair(int toFix);
int main(){

	freopen("input.txt","r",stdin);
	cin>>N;
	for(int i = 0 ; i < N; i++)
		for(int j = 0 ; j < N; j++)
			cin>>cost[i][j];

	cin>>isRepair>>P;
	for(int i = 0 ; i < N; i++)
		if(isRepair[i] == 'N')
			No_Num++;

	memset(cache, -1, sizeof(cache));
	// cout<<repair(0)<<endl;

	if(No_Num == N){
		cout<<-1<<endl;
	}
	else{
		cout<<repair(0)<<endl;
	}





	return 0;
}

int repair(int toFix){
	if(N - P <= No_Num) return 0;

	int ret = INF;
	
	for(int isFixed = 0; isFixed < N; isFixed++){
		if(isFixed == 'N'){
			isRepair[isFixed] = 'Y';	No_Num--;	
			ret = min(ret, repair(isFixed) + cost[toFix][isFixed]);
			isRepair[isFixed] = 'N'; No_Num++;
		}
	}
	return ret;
}
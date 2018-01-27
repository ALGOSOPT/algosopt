#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
 
using namespace std;
 
int d, n, m;

vector<int> nm;

long long bfs(){
 
    queue<long long> q;
 
    q.push(nm[0]);
 
    while(!q.empty()){
 
        long long now = q.front();
        q.pop();
 
 		if(now / n > 0 &&now % n == m)
 			return now;
 			
        for(int i = 0; i < nm.size(); i++){
            long long next = now * 10 + nm[i];
            q.push(next);
        }
    }
 
}

int main(){
 
    int c; 
	scanf("%d", &c);
 
    while(c--){
        scanf("%d %d %d", &d, &n, &m);
        if(d == 0){
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        nm = vector<int>();
        while(d != 0){
            nm.push_back(d%10);
            d /= 10;
        }
        sort(nm.begin(), nm.end());
        printf("%lld\n", bfs()); 
    }
 
    return 0;
}


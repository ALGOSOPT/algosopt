#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int MAX_N = 3e5;
typedef long long ll;
int n, k, c[MAX_N];
ll r;
pair<int, int> p[MAX_N];
priority_queue<int> pq;
int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d %d", &p[i].first, &p[i].second);
    for (int i = 0; i < k; i++) scanf("%d", c + i);
    sort(p, p + n);
    sort(c, c + k);
    for (int i = 0, j = 0; i < k; i++) {
        while (j < n && p[j].first <= c[i]) pq.push(p[j++].second);
        if (!pq.empty()) {
            r += pq.top();
            pq.pop();
        }
    }
    printf("%lld", r);
    return 0;
}
/*
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int n, k;
pair<int, int> jewel[300000];
int bag[300000];

int main(){

	priority_queue<int> heap = priority_queue<int>();
	
	scanf("%d%d", &n, &k);
	for(int i=0; i<n; i++){
		scanf("%d%d", &jewel[i].first, &jewel[i].second);
		heap.push(jewel[i].second);	
	}		
	for(int i=0; i<k; i++)
		scanf("%d", &bag[i]);
	
	sort(jewel, jewel+n);
	sort(bag, bag+k);

	long long result = 0;		
	//가방 갯수(k)만큼
	for(int i=0, j=0 ;i<k; i++){
		while(j<n && jewel[j].first <= bag[i]){
			cout << "push : " << jewel[j].second << " ";
			heap.push(jewel[j].second);	
			j++;
		}
		if(!heap.empty()){
			cout << "pop : "<< heap.top() <<" ";
			result += heap.top();
			heap.pop();
			cout << "top : " << heap.top() << " ";
		}
	}
	
	printf("%lld", result);
}*/

#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;

int n;

int main(){

	priority_queue<int, vector<int>, greater<int> > heap;
	
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		int temp;
		scanf("%d", &temp);
		heap.push(temp);		
	}
	
	int result = 0;
	while(heap.size()>1){
		int a = heap.top();
		heap.pop();
		int b = heap.top();
		heap.pop();
		result += a+b;
		heap.push(a+b);
	}
	printf("%d", result);
}

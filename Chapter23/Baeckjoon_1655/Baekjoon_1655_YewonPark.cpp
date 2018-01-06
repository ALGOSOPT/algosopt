#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

priority_queue<int, vector<int>, less<int> > maxHeap;
priority_queue<int, vector<int>, greater<int> > minHeap;
int arr[100000];

//중간값을 출력해야하므로 정수를 반환 
int getMedian(int n){
	int temp;
	if((n%2) == 0 && !maxHeap.empty()){//홀수번째
		if(minHeap.top() < arr[n]){
			temp = minHeap.top();
			minHeap.pop();
			maxHeap.push(temp);
			minHeap.push(arr[n]);
		}else
			maxHeap.push(arr[n]);
	}else if((n%2) != 0){//짝수번째
		if(maxHeap.top() > arr[n]){
			temp = maxHeap.top();
			maxHeap.pop();
			minHeap.push(temp);
			maxHeap.push(arr[n]);
		}else
			minHeap.push(arr[n]);
	}else if(maxHeap.empty()){
		maxHeap.push(arr[n]);
	}
	return maxHeap.top();
}

int main(){
	
		int n;
		scanf("%d", &n);
		
		maxHeap = priority_queue<int, vector<int>, less<int> >();
		minHeap = priority_queue<int, vector<int>, greater<int> >();
		
		for(int i=0; i<n; i++){
			scanf("%d", &arr[i]);
			printf("%d\n", getMedian(i));	
		}
}

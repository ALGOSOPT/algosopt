#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

priority_queue<int, vector<int>, less<int> > maxHeap;
priority_queue<int, vector<int>, greater<int> > minHeap;
int arr[200000];

//중간값을 출력해야하므로 정수를 반환 
int getMedian(int n){
	int temp;
	if((n%2) == 0 && !maxHeap.empty()){//홀수번째
		if(maxHeap.top() < arr[n]){
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
	
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; i++){
		int n, a, b;
		scanf("%d %d %d", &n, &a, &b);
		
		maxHeap = priority_queue<int, vector<int>, less<int> >();
		minHeap = priority_queue<int, vector<int>, greater<int> >();
		
		arr[0] = 1983;
		for(int i=1; i<n; i++)
			arr[i] = (arr[i-1]*(long long)a + b)%20090711; 
			
		int result = 0;
		for(int i=0; i<n; i++){
			result += getMedian(i);
			result %= 20090711;
			cout << result << " ";
		}
		printf("%d\n",result); 
	}
}

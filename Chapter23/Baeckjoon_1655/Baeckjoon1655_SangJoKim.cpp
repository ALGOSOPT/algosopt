#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n; scanf("%d", &n);
	priority_queue<int> maxHeap, minHeap;
	
	for (int i = 0; i < n; i++) {
		int inp; scanf("%d", &inp);
	
		if (maxHeap.size() == minHeap.size()) {
			maxHeap.push(inp);
		}
		else {
			minHeap.push(-inp);
		}
		if (!minHeap.empty() && !maxHeap.empty() && -minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = -minHeap.top();
			maxHeap.pop(), minHeap.pop();
			maxHeap.push(b);
			minHeap.push(-a);
		}
		printf("%d\n", maxHeap.top());
	}
	return 0;
}
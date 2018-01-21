#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
int n;

//min heap
vector<int> heap;

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void push(int add) {

	heap.push_back(add);

	int idx = heap.size() - 1;

	while (idx > 0 && heap[(idx - 1) / 2] > heap[idx]) {
		swap(heap[(idx - 1) / 2], heap[idx]);
		idx = (idx - 1) / 2;
	}
}

int pop() {

	int ret = heap[0];

	heap[0] = heap[heap.size() - 1];
	heap.pop_back();
	int here = 0, next = 0;
	while (1) {
		
		int left = here * 2 + 1, right = here * 2 + 2;

		if (left < heap.size() && heap[next] > heap[left])
			next = left;

		if (right < heap.size() && heap[next] > heap[right])
			next = right;

		if (next == here) break;

		swap(heap[next], heap[here]);

		here = next;

	}
	return ret;
}




int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	int ret = 0;

	for (int i = 0; i < n; i++) {
		int temp; scanf("%d", &temp);
		push(temp);
	}

	while (heap.size() >= 2) {
		
		int first = pop(), second = pop();

		ret += first + second;

		push(first + second);
	}
	//ret += heap[0] + heap[1];
	
	cout << ret << endl;
	return 0;
}
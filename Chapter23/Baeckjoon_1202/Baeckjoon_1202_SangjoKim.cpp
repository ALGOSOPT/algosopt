#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
class jewelry {
public :

	int value;
	int weight;

	jewelry() {};
	jewelry(int w, int v) : value(v), weight(w) {}

	bool operator < (jewelry &j) {
		return value < j.value;
	}
};

//max heap
vector<jewelry> heap;
vector<int> bag;
void swap(jewelry &a, jewelry &b) {
	jewelry temp = a;
	a = b;
	b = temp;
}
void push(jewelry j) {

	heap.push_back(j);

	int idx = heap.size() - 1;

	while (idx > 0 && heap[(idx - 1) / 2] < heap[idx]) {
		swap(heap[(idx - 1) / 2], heap[idx]);
		idx = (idx - 1) / 2;
	}
}



jewelry pop() {

	jewelry ret = heap[0];

	heap[0] = heap[heap.size() - 1];
	heap.pop_back();
	int next = 0,here = 0;

	while (1) {

		int left = here * 2 + 1, right = here * 2 + 2;

		if (left < heap.size() - 1 && heap[next] < heap[left])
			next = left;
		if (right < heap.size() - 1 && heap[next] < heap[right])
			next = right;

		if (here == next) break;

		swap(heap[here], heap[next]);
		here = next;
		
	}
	return ret;
}


int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d%d", &n, &k);

	bag.resize(k);

	for (int i = 0; i < n; i++) {
		int a, b; scanf("%d%d", &a, &b);
		push(jewelry(a, b));
	}

	long long int ret = 0;
	
	for (int i = 0; i < k; i++) {
		int newBag; scanf("%d", &newBag);
		
		vector<jewelry> tempBag;
		while (!heap.empty()) {
			jewelry temp = pop();
			//cout << temp.weight << endl;
			//담는다
			if (temp.weight <= newBag) {
				ret += temp.value;
				break;
			}
			//안담는다.
			else {
				tempBag.push_back(temp);
			}
		}

		for (int j = 0; j < tempBag.size(); j++) {
			push(tempBag[j]);
		}
	}

	printf("%lld\n", ret);

	return 0;
}
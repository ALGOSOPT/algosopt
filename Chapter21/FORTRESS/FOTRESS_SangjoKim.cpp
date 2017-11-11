#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>

using namespace std;

class Castle {
public:
	int x, y, r;
	Castle() {}
	Castle(int x, int y, int r) : x(x), y(y), r(r) {}
	void operator = (Castle b) {
		x = b.x; y = b.y; r = b.r;
	}
	bool operator < (Castle b) {
		return r < b.r;
	}
};
int N;
Castle castle[101];

class TreeNode {
public:
	int size = 0;
	TreeNode* children[101];
};

template <typename T>
void swap(int i, int j, T *arr) {
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

template <typename T>
T max(T a, T b) {
	return a > b ? a : b;
}

template <typename T>
void quickSort(T *ca, int left, int right) {

	int mid = (left + right) / 2;

	int i = left; int j = right;

	T pivot = ca[mid];

	while (left < j || i < right) {

		while (ca[i] < pivot) {
			i++;
		}
		while (pivot < ca[j]) {
			j--;
		}

		if (i <= j) {
			swap<T>(i, j, ca);
			i++; j--;
		}
		else {
			if (left < j)
				quickSort(ca, left, j);
			if (i < right)
				quickSort(ca, i, right);
			return;
		}
	}
}

//small이 big안에 있는지를 확인
bool isIn(Castle small, Castle big) {

	int sqDist = (small.x - big.x)*(small.x - big.x) + (small.y - big.y)*(small.y - big.y);

	int sqSubR = (big.r - small.r) * (big.r - small.r);
	return sqDist <= sqSubR;
}

TreeNode *node[101];

int longest;

int height(TreeNode * root) {

	int heights[101]; int size = 0;

	for (int i = 0; i < root->size; i++) {
		heights[size++] = height(root->children[i]);
	}

	if (size == 0) return 0;

	quickSort(heights, 0, size - 1);

	if (size >= 2)
		longest = max<int>(longest, heights[size - 2] + heights[size - 1]);
	return heights[size - 1] + 1;
}

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; scanf("%d", &TC);
	for (int test_case = 1; test_case <= TC; test_case++) {

		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			cin >> castle[i].x >> castle[i].y >> castle[i].r;
		}

		quickSort(castle, 0, N - 1);
		
		for (int i = 0; i < N; i++) {
			node[i] = new TreeNode();
		}

		for (int i = 0; i < N - 1; i++) {
			for (int j = i + 1; j < N; j++) {
				if (isIn(castle[i], castle[j])) {
					node[j]->children[node[j]->size++] = node[i];
					break;
				}
			}
		}
		longest = 0;
		//cout << node[N - 3]->size << endl << endl;

		int h = height(node[N - 1]);
		cout << max<int>(longest, h) << endl;

		for (int i = 0; i < N; i++) {
			delete node[i];
		}
	}
	
	return 0;
}



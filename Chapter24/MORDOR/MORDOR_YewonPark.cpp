#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

vector<int> max_tree;
vector<int> min_tree;
vector<int> a;
 
void init_max(int node, int start, int end){
	if(start == end)
		max_tree[node] = a[start];
	else{
		init_max(node*2, start, (start+end)/2);
		init_max(node*2+1, (start+end)/2+1, end);
		max_tree[node] = max(max_tree[node*2], max_tree[node*2+1]);
	}
}

void init_min(int node, int start, int end){
	if(start == end)
		min_tree[node] = a[start];
	else{
		init_min(node*2, start, (start+end)/2);
		init_min(node*2+1, (start+end)/2+1, end);
		min_tree[node] = min(min_tree[node*2], min_tree[node*2+1]);
	}
}

int max_height(int node, int start, int end, int left, int right){
	if(left > end || right < start)
		return -1;
	if(left<=start && end<=right)
		return max_tree[node];
	return max(max_height(node*2, start, (start+end)/2, left, right), max_height(node*2+1, (start+end)/2+1, end, left, right));
}

int min_height(int node, int start, int end, int left, int right){
	if(left > end || right < start)
		return 20001;
	if(left<=start && end<=right)
		return min_tree[node];
	return min(min_height(node*2, start, (start+end)/2, left, right), min_height(node*2+1, (start+end)/2+1, end, left, right));
}

int main(){
	
	int t;
	cin >> t;
	while(t--){
		
		int n, q;
		cin >> n >> q;
		
		a = vector<int>(n);
		int h = (int)ceil(log2(n));
		int tree_size = (1<<(h+1));
		max_tree = vector<int>(tree_size);
		min_tree = vector<int>(tree_size);
		
		for(int i=0; i<n; i++){
			cin >> a[i];
		}
		
		init_max(1, 0, n-1);//구간트리 만들기
		init_min(1, 0, n-1);
		
		for(int i=0; i<q; i++){
			int left, right;
			cin >> left >> right;
			cout << max_height(1, 0, n-1, left, right) - min_height(1, 0, n-1, left, right) << "\n";//구간트리에서 최대, 최솟값 찾기
			 
		} 
	}
}

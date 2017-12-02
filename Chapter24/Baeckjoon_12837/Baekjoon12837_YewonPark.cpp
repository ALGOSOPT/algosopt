#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

vector<long long> tree;
/*
vector<int> a;
 
void init(int node, int start, int end){
	if(start == end)
		tree[node] = 1;
	else{
		init(node*2, start, (start+end)/2);
		init(node*2+1, (start+end)/2+1, end);
		tree[node] = tree[node*2] + tree[node*2+1];
	}
}
*/

long long sum(int node, int start, int end, int left, int right){
	if(left > end || right < start)
		return 0;
	if(left<=start && end<=right)
		return tree[node];
	return sum(node*2, start, (start+end)/2, left, right) + sum(node*2+1, (start+end)/2+1, end, left, right);
}

void update(int node, int start, int end, int index, int diff){
	if(index < start || index > end)
		return;
	tree[node] += diff;
	if(start != end){
		update(node*2, start, (start+end)/2, index, diff);
		update(node*2+1, (start+end)/2+1, end, index, diff);
	}
}

int main(){
	
	int n, q;
	cin >> n >> q;
	
	//a = vector<int>(n, 0);
	int h = (int)ceil(log2(n));
	int tree_size = (1<<(h+1));
	tree = vector<long long>(tree_size, 0);
	
	//init(1, 0, n-1);//구간트리 만들기
	
	for(int i=0; i<q; i++){
		int input1, input2, input3;
		cin >> input1 >> input2 >> input3;
		if(input1 == 1){
			update(1, 0, n-1, input2-1, input3);
		}else if(input1 == 2){
			printf("%lld\n", sum(1, 0, n-1, input2-1, input3-1));
		}
	}
}

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int n;
int input[1025][1025];
int tree[1025][1025];

long long sum(int x, int y) {
    long long ans = 0;
    for(; x; x -= (x & -x))
    	for(int j=y; j; j -= (j & -j)){
    		//cout << "y : " << j << " tree : "<< tree[x][j] << "\n";
			ans += tree[x][j];	
		}
    return ans;
}

void update(int x, int y, int s) {
	for(; x<=n; x += (x&-x))
		for(int j=y; j<=n; j += (j&-j))
			tree[x][j] += s;
}

int main() {
    int m;
    cin >> n >> m;
    
    for(int i=1; i<=n; i++)
    	for(int j=1; j<=n; j++){
    		cin >> input[i][j];
			update(i, j, input[i][j]);	
		}
	/*
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n ;j++)
			cout << tree[i][j] << " ";	
		cout << "\n";	
	}*/
	for (int i = 0, w, a, b, c, d; i < m; i++) {
		cin >> w >> a >> b >> c;
        if (w) {
        	cin >> d;
        	//cout << sum(c, d) << " " << sum(a - 1, d) << " " << sum(c, b - 1) << " " << sum(a - 1, b - 1) << "\n";
        	cout << sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1) << "\n";
        }
        else{
        	update(a, b, c - input[a][b]); 
			input[a][b] = c;
		}
    }
    return 0;
}

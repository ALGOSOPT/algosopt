#include<iostream>
#include<cstdio>
#include<set>

using namespace std;
 
int main() {
 
 	//freopen("input.txt", "r", stdin);
 	
    int n;
    cin >> n;
    
    //트리의 정보를 담아둘 배열 선언(부모노드와 깊이 저장)
    int tree[100001][2];
	
	set<int> tree_;
	tree_.insert(1);
	
    int n1, n2;
    for(int i=0; i<n-1; i++){
    	cin >> n1 >> n2;
    	if(tree_.find(n1) != tree_.end()){
    		tree[n2][0] = n1;//부모노드 저장	
			tree_.insert(n2);
		}
		else{
			tree[n1][0] = n2;
			tree_.insert(n1);
		}
	}
	
	tree[1][0] = 1;//루트 
	tree[1][1] = 0;
	
	//깊이 계산
    for (int i = 2; i <= n; i++) {
        int now = i;
        int d = 1;
        while(tree[now][0] != 1) {
            now = tree[now][0];
            d++;
        }
        tree[i][1] = d + 1;
    }
 
 	int m;
	cin >> m;
	
	for(int i=0; i<m; i++){
			int n1, n2;
            cin >> n1 >> n2;
            
            int result = 0;
            int d1 = tree[n1][1];
            int d2 = tree[n2][1];
            
            //먼저 입력한 노드의 깊이가 더 깊으면 
            if(d1 > d2){
                do{
                    //n1을 올려준다
                    n1 = tree[n1][0];
                    d1--;
                }while(d1>d2);
            }
            //나중에 입력한 노드의 깊이가 더 깊으면 
            else if(d1 < d2){
                do{
                    //n2을 올려준다
                    n2 = tree[n2][0];
                    d2--;
                }while(d1<d2);
            }
            //부모노드가 같을 때 까지 올려준다 
            while(n1 != n2){ 
                n1 = tree[n1][0];
                n2 = tree[n2][0];
            }	
            
            cout << n1 << "\n";
	} 
    
    return 0;
}


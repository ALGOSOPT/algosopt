//
//  main.cpp
//  traversal
//
//  Created by smartgrid_aict on 2017. 11. 3..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAX = 101;
int in[MAX];
int n;
queue<int> pre;

// 전위를 하나씩 증가시키며(루트) 중위에서 왼쪽, 오른쪽을 결정한다.
void findRoot(int start, int end) {
    
    if(start == end) {
        return;
    }
    
    // 중위 돌면서 루트 찾기 구하기
    int index = -1;
    if(!pre.empty()) {
        int root = pre.front();
        
        for(int i = start; i < end; i++) {
            if(root == in[i]) {
                index = i;
                pre.pop();
                break;
            }
        }
        
        if(index != -1) {
            findRoot(start, index);
            // 오른쪽
            findRoot(index+1, end);
            
        }
        cout << root << " ";
        
    }
    
}
int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/traversal/traversal/input.txt", "r", stdin);
    int T;
    cin >> T;
    
    while(T--) {
        
        cin >> n;
        for(int i = 0 ; i < n ;  i++) {
            int t;
            cin >> t;
            pre.push(t);
        }
        for(int i = 0 ; i < n ;  i++) {
            cin >> in[i];
        }
        
        findRoot(0, n);
        cout << endl;
    }
    
    return 0;
}

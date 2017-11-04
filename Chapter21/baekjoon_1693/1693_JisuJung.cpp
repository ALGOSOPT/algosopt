//
//  main.cpp
//  1693
//
//  Created by smartgrid_aict on 2017. 11. 5..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//


#include <iostream>
#include <vector>
#include <math.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 100011;
const int INF = 0x3f3f3f3f;
vector<int> board[MAX];
// log2 N 종류 색만 필요함
int cache[MAX][18];
int visited[MAX];
int n;

// index 번 정점을 color로 칠했을 때 최소 비용
int calcMin(int index, int color) {
    
    int& ret = cache[index][color];
    
    if(ret != -1)
        return ret;
    
    visited[index] = 1;
    
    ret = color;
    
    for(int i = 0 ; i < board[index].size(); i++) {
        int nextt = board[index][i];
        if(!visited[nextt]) {
            int temp = INF;
            for(int j = 1 ; j < 18 ; j++) {
                if(j != color) {
                    temp = min(temp, calcMin(nextt, j));
                }
            }
            ret += temp;
        }
        
    }
    
    visited[index] = 0;
    
    return ret;
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/1693/1693/input.txt", "r", stdin);
    
    memset(cache, -1, sizeof(cache));
    
    cin >> n;
    
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        board[a].push_back(b);
        board[b].push_back(a);
    }
    
    
    int ret = INF;
    for(int i = 1 ; i < 18 ; i++) {
        ret = min(ret, calcMin(0, i));
    }
    
    cout << ret << endl;
    return 0;
}

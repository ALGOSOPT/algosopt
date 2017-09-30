//
//  main.cpp
//  1102
//
//  Created by smartgrid_aict on 2017. 10. 1..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
int cache[1<<16];
int board[17][17];
const int INF = 0x3f3f3f;
int n, k;

int bitCount(int x) {
    if(x == 0) return 0;
    return x % 2 + bitCount(x/2);
}

int calcMin(int plant) {
    
    if(bitCount(plant) >= k)
        return 0;
    
    int &ret = cache[plant];
    
    if(ret != -1) return ret;
    
    ret = INF;
    
    for(int i = 0; i < n; i++) {
        if(!(plant & (1<<i))) {
            for(int j = 0 ; j < n ; j++) {
                if(plant & (1<<j))
                    ret = min(ret, calcMin(plant | (1<<i)) + board[j][i]);
            }
        }
    }
                              
    return ret;
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/1102/1102/input.txt", "r", stdin);
    
    memset(cache, -1, sizeof(cache));
    string str;
    cin >> n;
    
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            cin >> board[i][j];
        }
    }
    
    cin >> str >> k;
    
    int make_plant = 0;
    for(int i = 0; i < n; i++) {
        if(str[i] == 'Y') {
            make_plant |= (1<<i);
        }
    }
    
    int result = calcMin(make_plant);
   
    if(result == INF) cout << -1 << endl;
    else cout << result << endl;
    
    return 0;
}

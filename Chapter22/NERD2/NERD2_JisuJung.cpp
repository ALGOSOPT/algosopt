//
//  main.cpp
//  nerd2
//
//  Created by smartgrid_aict on 2017. 11. 11..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <map>
using namespace std;
int n;

map<int, int> nerds;

// lower_bound(x) : 트리에 포함된 x 이상의 키 중 가장 작은 값을 돌려준다.

void removee(int p, int q) {
    map<int, int>::iterator it = nerds.lower_bound(p);
    
    if(it == nerds.begin()) return;
    
    it--;
    
    // 왼쪽에 있는 점 중 y 좌표가 작은 점만 지운다.
    while(1) {
        if(it->second > q) break;
        // 하나 이미 감소 시킨애가 begin 이면 지움
        if(it == nerds.begin()) {
            //cout << "before erase : " << it->first << " " << it->second << endl;
            nerds.erase(it);
            //cout << "after erase : " << it->first << " " << it->second << endl;
            break;
        } else {
            map<int, int>::iterator temp = it;
            temp--;
            //cout << "before erase : " << it->first << " " << it->second << endl;
            nerds.erase(it);
            it = temp;
            //cout << "after erase : " << it->first << " " << it->second << endl;
        }
    }
}

bool isDominate(int p, int q) {
    map<int, int>::iterator it = nerds.lower_bound(p);
    
    if(it == nerds.end()) return false;
    
    return q < it->second;
}


int check(int p, int q) {
    
    if(isDominate(p,q)) return (int)nerds.size();
    
    removee(p, q);
    
    //nerds[p] = q;
    nerds.insert(make_pair(p, q));
    
    return (int)nerds.size();
    
}
       
int main(int argc, const char * argv[]) {

    freopen("/Users/smartgrid_aict/Desktop/algorithm/nerd2/nerd2/input.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        int ret = 0;
        nerds.clear();
        for(int i = 0 ; i < n ; i++) {
            int p, q;
            cin >> p >> q;
            ret += check(p, q);
        }
        
         cout << ret << endl;
        
//        map<int, int>::iterator it = nerds.lower_bound(74);
//        cout << it->first << " " << it->second << endl;
        
    }
    return 0;
}

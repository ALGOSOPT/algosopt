//
//  main.cpp
//  sortgame
//
//  Created by smartgrid_aict on 2018. 1. 26..
//  Copyright © 2018년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

// key: 숫자 배열, value: 필요한 뒤집기 연산 수
map<vector<int>, int> toSort;

// 전처리: 모든 순열에 대해 필요한 뒤집기 연산 수 계산
void precalc(int n) {
    vector<int> perm(n);
    // 정렬된 상태
    for(int i = 0 ; i < n; i++) {
        perm[i] = i;
    }
    queue<vector<int> > q;
    q.push(perm);
    toSort[perm] = 0;
    while(!q.empty()) {
        vector<int> here = q.front();
        q.pop();
        
        int cost = toSort[here];
        
        for(int i = 0 ; i < n ; i++) {
            for(int j = i+2; j <= n; j++) {
                //cout << "start : " << i << ", end : " << j << endl;
                
                reverse(here.begin() + i, here.begin() + j);
                
                //                for(int k = 0 ; k < here.size(); k ++) {
                //                    cout << here[k] << " ";
                //                }
                //                cout << endl;
                
                // 뒤집은 순열이 없으면 큐에 넣어준다.
                if(toSort.count(here) == 0) {
                    toSort[here] = cost + 1;
                    //cout << "cost : " << cost + 1 << endl;
                    q.push(here);
                }
                // 원상복귀
                reverse(here.begin() + i, here.begin() + j);
                //                cout << "re " ;
                //                for(int k = 0 ; k < here.size(); k ++) {
                //                    cout << here[k] << " ";
                //                }
                //                cout << endl;
            }
        }
    }
}

// perm : 결과 순열
int solve(const vector<int>& perm) {
    int n = perm.size();
    vector<int> fixed(n);
    for(int i = 0; i < n; i++) {
        int smaller = 0;
        for(int j = 0 ; j < n; j++) {
            if(perm[j] < perm[i]) ++smaller;
        }
        fixed[i] = smaller;
    }
    
//    for(int i = 0; i < n; i++) {
//        cout << fixed[i] << " ";
//    }
//    cout << endl;
    
    return toSort[fixed];
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/sortgame/sortgame/input.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> temp(n);
        for(int i = 0 ; i < n ; i++) {
            cin >> temp[i];
        }
        precalc(n);
        
        cout << solve(temp) << endl;
    }
    return 0;
}

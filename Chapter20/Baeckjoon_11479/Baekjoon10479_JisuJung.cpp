//
//  main.cpp
//  11478
//
//  Created by smartgrid_aict on 2017. 12. 2..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 1000001;
string s;
int n, d, group[MAX];
// 접미사들을 알파벳 순으로 정렬해 놓은 것
vector<int> SA;
// 최장 공통 접두사, SA에서 인접한 두 접미사간의 최장 공통 접두사의 길이 저장
vector<int> LCP;

bool cmp(int i, int j) {
    // 같지 않으면 그냥 리턴
    if(group[i] != group[j]) return group[i] < group[j];
    
    i += d;
    j += d;
    
    return (i < n && j < n) ? (group[i] < group[j]) : (i > j);
}

void getSuffix() {
    
    for(int i = 0 ; i < n ; i++) {
        SA[i] = i;
        group[i] = s[i];
    }
    
    for(d = 1; ; d *= 2) {
        sort(SA.begin(), SA.end(), cmp);
        vector<int> newGroup(n, 0);
        for(int i = 0 ; i < n-1 ; i++) {
            newGroup[i+1] = newGroup[i] + cmp(SA[i], SA[i+1]);
        }
        
        for(int i = 0 ; i < n ; i++) {
            group[SA[i]] = newGroup[i];
        }
        
        if(newGroup[n-1] == n-1) break;
    }
    
}

void getLCP() {
    for(int i = 0, k = 0; i < n ; i++, k = max(k-1, 0)) {
        if(group[i] == n-1) continue;
        
        for(int j = SA[group[i] + 1]; s[i+k] == s[j+k]; k++);
        LCP[group[i]] = k;
        
    }
}

int main(int argc, const char * argv[]) {
    
    cin >> s;
    //s = "ababc";
    n = (int)s.size();
    SA = vector<int>(n);
    LCP = vector<int>(n-1);
    
    getSuffix();
    //    for(int i = 0 ; i < SA.size() ; i++) {
    //        cout << SA[i] << endl;
    //    }
    getLCP();
//    for(int i = 0 ; i < LCP.size() ; i++) {
//        cout << LCP[i] << endl;
//    }
    LCP.push_back(0);
    long long ret = 0;
    // 접미사 길이만큼 부분 문자열이 만들어짐
    // LCP개만큼 중복이다.
    for(int i = 0 ; i < LCP.size() ; i++) {
        ret += (n-SA[i]-LCP[i]);
    }
    
    cout << ret << endl;
    return 0;
}

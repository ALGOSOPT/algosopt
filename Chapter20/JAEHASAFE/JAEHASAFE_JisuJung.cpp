//
//  main.cpp
//  jaehasafe
//
//  Created by smartgrid_aict on 2017. 10. 27..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getPartialMatch(const string& N){
    
    int m = (int)N.size();
    vector<int> pi(m, 0);
    int begin = 1, match = 0;
    while(begin + match < m) {
        if(N[begin+match] == N[match]) {
            ++match;
            pi[begin+match-1] = match;
        } else {
            if(match == 0) {
                begin++;
            } else {
                begin += match - pi[match-1];
                match = pi[match-1];
            }
        }
    }
    return pi;
}

vector<int> kmpSearch(const string& H, const string& N) {
    int n = (int)H.size(), m = (int)N.size();
    vector<int> ret;
    vector<int> pi = getPartialMatch(N);
    int begin = 0, match = 0;
    while(begin <= n - m) {
        if(match < m && H[begin+match] == N[match]) {
            match++;
            if(match == m) ret.push_back(begin);
        } else {
            if(match == 0)
                ++begin;
            else {
                begin += match - pi[match-1];
                match = pi[match-1];
            }
        }
    }
    return ret;
}

int shifts(const string origin, const string tar) {
    return kmpSearch(origin+origin, tar)[0];
}
int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/jaehasafe/jaehasafe/input.txt", "r", stdin);
    int T;
    cin >> T;
    
    
    while(T--) {
        int n;
        cin >> n;
        
        vector<string> aa;
        for(int i = 0; i < n+1 ; i++) {
            string t ;
            cin >> t;
            aa.push_back(t);
        }
        
//        for(int i = 0; i < n+1 ; i++) {
//            cout << aa[i] << endl;
//        }
        
        int ret = 0;
        // 시계 짝수, 반시계 홀수
        for(int i = 1 ; i < n+1 ; i++) {
            int sizee = (int)aa[i-1].size();
            if(i % 2 == 0) {
                int next = shifts(aa[i-1], aa[i]);
                ret += next;
            } else {
                // 홀수
                int next = shifts(aa[i], aa[i-1]);
                ret += next;
            }
        }
        
        cout << ret << endl;
        
    }
    return 0;
}

//
//  main.cpp
//  christmas
//
//  Created by smartgrid_aict on 2017. 9. 30..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;
const int MOD = 20091101;

/*
 int rangeSum(int a, int b) {
 if(a == 0) return psum[b];
 return psum[b]-psum[a-1];
 }
 */

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/christmas/christmas/input.txt", "r", stdin);
    
    int T;
    cin >> T;
    while(T--) {
        vector<int> psum(1, 0);
        vector<int> box(MAX, 0);
        int n, k;
        cin >> n >> k;
        
        for(int i = 0; i < n; i++) {
            cin >> box[i];
            psum.push_back((box[i] + psum.back()) % k);
        }
        
        vector<long long> seen(k,0);
        for(int i = 0; i < psum.size(); i++) {
            seen[psum[i]]++;
        }
        
        //                for(int i = 0; i <= n; i++) {
        //                    cout<< psum[i] << endl;
        //                }
        //
        int ret = 0;
        
        for(int i = 0; i < k; i++) {
            if(seen[i] >= 2)
                ret = (ret + ((seen[i] * (seen[i]-1)) / 2)) % MOD;
        }
        
        

        vector<int> cond(psum.size(), 0);
        vector<int> prev(k, -1);
        for(int i = 0 ; i < psum.size() ; i++) {
            i>0 ? cond[i] = cond[i-1] : cond[i] = 0;
            int loc = prev[psum[i]];
            if(loc != -1) cond[i] = max(cond[i], cond[loc] + 1);
            prev[psum[i]] = i;
        }
        
        cout << ret << " " << cond.back() << endl;
        
    }
    return 0;
}

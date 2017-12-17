//
//  main.cpp
//  7469
//
//  Created by smartgrid_aict on 2017. 12. 16..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<pair<int, int> > nums;

int main(int argc, const char * argv[]) {
  
    int n, m, ii, j, k;
    
    cin >> n >> m;
  
    for(int i = 0 ; i < n ; i++) {
        int t;
        cin >> t;
        nums.push_back(make_pair(t, i));
    }
    
    sort(nums.begin(), nums.end());
    
//    for(int i = 0 ; i < nums.size(); i++) {
//        cout << nums[i].first << " " << nums[i].second << endl;
//    }
    
    for(int i = 0 ; i < m ; i++) {
        int cnt = 0;
        cin >> ii >> j >> k;
        for(int z = 0; z < n; z++) {
            if(nums[z].second >= ii-1 && nums[z].second < j) cnt++;
            if(cnt == k) {
                cout << nums[z].first << endl;
                break;
            }
        }
    }
    
    
    return 0;
}

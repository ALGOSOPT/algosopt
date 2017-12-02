//
//  main.cpp
//  mordor
//
//  Created by smartgrid_aict on 2017. 12. 3..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 0x3f3f3f3f;
vector<int> h;

struct RMQ {
    int n;
    vector<int> rangeMin;
    RMQ(const vector<int>& array) {
        n = (int)array.size();
        rangeMin.resize(n*4);
        init(array, 0, n-1, 1);
    }
    
    int init(const vector<int>& array, int left, int right, int node) {
        if(left == right) return rangeMin[node] = array[left];
        int mid = (left+right) / 2;
        int leftMin = init(array, left, mid, node*2);
        int rightMin = init(array, mid+1, right, node*2+1);
        return rangeMin[node] = min(leftMin, rightMin);
    }
    
    int query(int left, int right, int node, int nodeL, int nodeR) {
        if(right < nodeL || nodeR < left) return MAX;
        if(left <= nodeL && nodeR <= right) return rangeMin[node];
        int mid = (nodeL+nodeR)/2;
        return min(query(left, right, node*2, nodeL, mid),
                   query(left, right, node*2+1, mid+1, nodeR));
    }
    
    int query(int left, int right) {
        return query(left, right, 1, 0, n-1);
    }
};


int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/mordor/mordor/input.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        h.clear();
        int nn, q;
        cin >> nn >> q;
        for(int i = 0 ; i < nn ; i++) {
            int aa;
            cin >> aa;
            h.push_back(aa);
        }
        
        RMQ min(h);
        for(int i = 0; i < nn; i++) h[i] = -h[i];
        RMQ max(h);
        for(int i = 0; i < q; i++) {
            int f, l;
            cin >> f >> l;
            cout << -max.query(f, l)-min.query(f, l) << endl;
        }

    
    }
    
    return 0;
}

//
//  main.cpp
//  12837
//
//  Created by smartgrid_aict on 2017. 12. 3..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, Q;

struct RMQ {
    vector<long long> rangeMin;
    
    RMQ() {
        rangeMin.resize(N * 4);
    }
    
    void update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
        if(index < nodeLeft || nodeRight < index) return;
        
        rangeMin[node] += newValue;
        
        if(nodeLeft != nodeRight) {
            int mid = (nodeLeft+nodeRight)/2;
            update(index, newValue, node*2, nodeLeft, mid);
            update(index, newValue, node*2+1, mid+1, nodeRight);
        }
    }
    
    void update(int index, int newValue) {
        update(index, newValue, 1, 0, N-1);
    }
    
    long long sum(int node, int start, int end, int left, int right) {
        if (left > end || right < start) return 0;
        if (left <= start && right >= end) return rangeMin[node];
        
        return sum(node * 2, start, (start + end) / 2, left, right) + sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
    }
    
};



int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/12837/12837/input.txt", "r", stdin);
    cin >> N >> Q;
    int type, p, q;
    RMQ tree;
    for(int i = 0 ; i < Q ; i++) {
        cin >> type >> p >> q;
        if(type == 1) {
            tree.update(p-1, q);
        } else {
            cout << tree.sum(1, 0, N-1, p-1, q-1) << endl;
        }
    }
    
    return 0;
}

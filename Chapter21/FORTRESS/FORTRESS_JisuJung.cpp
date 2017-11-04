//
//  main.cpp
//  fortress
//
//  Created by smartgrid_aict on 2017. 11. 3..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
const int MAX = 101;
int n, y[MAX], x[MAX], radius[MAX];

struct TreeNode {
    int label;
    vector<TreeNode*> children;
};

int sqr(int a) {
    return a*a;
}

int sqrdist(int a, int b) {
    return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}

bool encloes(int a, int b) {
    // 반지름이 더 크고, 두 중점 사이의 거리가 두 반지름의 차보다 작으면 포함한다.
    // 직접 포함하는지는 모른다.
    return radius[a] > radius[b] && sqrdist(a,b) < sqr(radius[a] - radius[b]);
}

bool isChild(int parent, int child) {
    // 포함하지 않으면 자식이 아니다.
    if(!encloes(parent, child)) return false;
    for(int i = 0 ; i < n ; i++) {
        // parent, child 사이에 i 가 있으면 직접 연결된 자식이 아니다.
        if( i != parent && i != child && encloes(parent, i) && encloes(i, child))
            return false;
    }
    return true;
}

// root 성벽을 루트로 하는 트리를 생성
TreeNode* getTree(int root) {
    TreeNode* ret = new TreeNode();
    for(int i = 0 ; i < n ; i++) {
        if(isChild(root, i))
            ret->children.push_back(getTree(i));
    }
    return ret;
}

int longest;
int height(TreeNode* root) {
    vector<int> heights;
    for(int i = 0 ; i < root->children.size(); i++) {
        heights.push_back(height(root->children[i]));
    }
    
    if(heights.empty()) return 0;
    sort(heights.begin(), heights.end());
    if(heights.size() >= 2) {
        longest = max(longest, 2+heights[heights.size()-2] + heights[heights.size()-1]);
    }
    return heights.back() + 1;
    
}
int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/fortress/fortress/input.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 0 ; i < n ; i++) {
            cin >> x[i] >> y[i] >> radius[i];
        }
        
        TreeNode* tree = getTree(0);
        
        longest = 0;
        
        int h = height(tree);
        
        cout << max(longest, h) << endl;
    }
    return 0;
}

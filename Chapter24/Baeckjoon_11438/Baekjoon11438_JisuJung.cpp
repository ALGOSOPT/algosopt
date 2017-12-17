//
//  main.cpp
//  11438
//
//  Created by smartgrid_aict on 2017. 12. 16..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const int MAX = 100005;
int n;
int visited[MAX], dist[MAX], parent[MAX][18];
vector<int> tree[MAX];

void dfs(int here) {
    visited[here] = true;
    for(int i = 0 ; i < tree[here].size() ; i++) {
        int there = tree[here][i];
        if(!visited[there]) {
            parent[there][0] = here;
            dist[there] = dist[here]+1;
            dfs(there);
        }
    }
}

//2^n 에 해당하는 부모를 구해놓음
void makeParent() {
    for (int j = 1; j < 18; j++) {
        for (int i = 0; i < n; i++) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }
}

int lca(int x, int y) {
    if (dist[x] > dist[y])
        swap(x, y);
    for (int i = 17; i >= 0; i--) {
        // 깊이차 맞추기
        if (dist[y] - dist[x] >= (1 << i))
            y = parent[y][i];
    }
    
    if (x == y) return x;
    
    for (int i = 17; i >= 0; i--) {
        if (x == y) return x;
        if (parent[x][i] != parent[y][i]) {
            x = parent[x][i];
            y = parent[y][i];
        }
    }
    
    return parent[x][0];
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/11438/11438/in.txt", "r", stdin);
    
    scanf("%d", &n);
    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d %d", &a, &b);
        tree[a-1].push_back(b-1);
        tree[b-1].push_back(a-1);
    }
    
    //    for(int i = 0 ; i < n; i++) {
    //        for(int j = 0 ; j < tree[i].size(); j++) {
    //            cout << tree[i][j] << endl;
    //        }
    //    }
    
    dfs(0);
    makeParent();
    
    int m;
    cin >> m;
    int c, d;
    for(int i = 0 ; i < m ; i++) {
        scanf("%d %d", &c, &d);
        printf("%d\n", lca(c-1, d-1)+1 );
    }
    return 0;
}

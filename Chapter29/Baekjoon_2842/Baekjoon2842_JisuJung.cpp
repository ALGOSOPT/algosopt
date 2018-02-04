//
//  main.cpp
//  2842
//
//  Created by jeongji su on 2018. 2. 2..
//  Copyright © 2018년 jeongji su. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <functional>
using namespace std;
#define MAX 1000000
#define mp make_pair
#define P pair<int, pair<int, int> >
#define INF 0x3f3f3f3f
int dy[8] = {-1,-1,-1,0,0,1,1,1};
int dx[8] = {0,-1,1,1,-1,0,-1,1};
int n;
char board[51][51];
int tired[51][51];
vector<int> tired_sm;

bool inRange(int y, int x) {
    return y >= 0 && y < n && x >= 0 && x < n;
}

int bfs(int starty, int startx, int sm) {
    
    priority_queue<P, vector<P>, greater<P> > pq;
    
    int visited[51][51];
    memset(visited, 0, sizeof(visited));
    
    pq.push(mp(tired[starty][startx],mp(starty, startx)));
    visited[starty][startx] = 1;
    int ret = 0;
    
    while(!pq.empty()) {
        int yy = pq.top().second.first;
        int xx = pq.top().second.second;
        int cost = pq.top().first;
        pq.pop();
        //cout << "cost " << cost << endl;
        
        if(board[yy][xx] == 'K') {
            ret = max(ret, cost);
        }
        
        for(int i = 0; i < 8; i++) {
            int nexty = yy + dy[i];
            int nextx = xx + dx[i];
    
            if(inRange(nexty, nextx) && !visited[nexty][nextx]) {
                if(tired[nexty][nextx] >= sm) {
                    int nextc = max(tired[nexty][nextx], cost);
                    visited[nexty][nextx] = 1;
                    pq.push(mp(nextc, mp(nexty, nextx)));
                }
            }
        }
    }
    
    // 방문을 안한 집이 있는 경우 검사
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == 'K' && !visited[i][j])
                return INF;
        }
    }
    
    return ret;
}
int main(int argc, const char * argv[]) {
    
    freopen("/Users/JUNGJISU/Desktop/C++/2842/2842/input.txt", "r", stdin);
    cin >> n;
    
    int starty, startx;
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            char t;
            cin >> t;
            if(t == 'P') {
                starty = i;
                startx = j;
            }
            board[i][j] = t;
        }
    }
    
    //cout << starty << ", " << startx << endl;
    
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            cin >> tired[i][j];
            tired_sm.push_back(tired[i][j]);
        }
    }
    
    sort(tired_sm.begin(), tired_sm.end());
    tired_sm.erase(unique(tired_sm.begin(), tired_sm.end()), tired_sm.end());
    
   
    int ans = INF;
    
    //   for (int i = 0; i < tired_sm.size(); i++) {
    for (int i = 0; i < tired_sm.size() && tired_sm[i] <= tired[starty][startx]; i++) {
        int nn = bfs(starty, startx, tired_sm[i]) - tired_sm[i];
        //cout << "nn " << i << ", "<< nn << endl;
        ans = min(ans, bfs(starty, startx, tired_sm[i]) - tired_sm[i]);
    }

    cout << ans<< endl;
    
    
    return 0;
    
}

//
//  main.cpp
//  1194
//
//  Created by jeongji su on 2018. 2. 3..
//  Copyright © 2018년 jeongji su. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX 100000
#define mp make_pair
#define INF 0x3f3f3f3f
int dy[4] = {-1,0,1,0};
int dx[4] = {0,-1,0,1};
int n, m, ret = INF;
string board[51];
class Queue {
    pair<int,pair<int, int> > queue[MAX];
    int front;
    int rear;
    
public:
    bool Put(pair<int,pair<int, int> > _d) {
        if ((rear + 1) % MAX == front) {
            return false;
        }
        
        queue[rear] = _d;
        rear = ++rear % MAX;
        return true;
    }
    bool Get(pair<int,pair<int, int> > &_d) {
        if (front == rear) {
            return false;
        }
        _d = queue[front];
        front = ++front % MAX;
        return true;
    }
};

bool inRange(int y, int x) {
    return y >= 0 && y < n && x >= 0 && x < m;
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/JUNGJISU/Desktop/C++/1194/1194/input.txt", "r", stdin);
    cin >> n >> m;
    
    int visited[51][51][1<<7];
    memset(visited, 0, sizeof(visited));
    
    int startx, starty;
    for(int i = 0 ; i < n; i++) {
        cin >> board[i];
        for(int j = 0 ; j < m; j++) {
            if(board[i][j] == '0') {
                startx = j;
                starty = i;
            }
        }
    }
    
    Queue q;
    q.Put(mp(starty, mp(startx, 0)));
    visited[starty][startx][0] = 1;
    
    pair<int, pair<int, int> > d;
    
    while(q.Get(d)) {
        int yy = d.first,
        xx = d.second.first,
        keys = d.second.second;
        
        for(int i = 0 ; i < 4 ; i++) {
            int nexty = yy + dy[i];
            int nextx = xx + dx[i];
            
            if(inRange(nexty, nextx) && visited[nexty][nextx][keys] == 0) {
                if(board[nexty][nextx] == '1') {
                    ret = min(ret, visited[yy][xx][keys]);
                }
                else if(board[nexty][nextx] == '#') {
                    continue;
                }
                else if(board[nexty][nextx] >= 'a' && board[nexty][nextx] <= 'f') {
                    int kk = keys | (1<<(board[nexty][nextx]-'a'));
                    if(visited[nexty][nextx][kk] == 0) {
                        visited[nexty][nextx][kk] = visited[yy][xx][keys] + 1;
                        q.Put(mp(nexty, mp(nextx, kk)));
                    }
                } else if(board[nexty][nextx] >= 'A' && board[nexty][nextx] <= 'F') {
                    int kk = 1<<(board[nexty][nextx]-'A');
                    if((keys & kk) == kk) {
                        q.Put(mp(nexty, mp(nextx, keys)));
                        visited[nexty][nextx][keys] = visited[yy][xx][keys] + 1;
                    }
                } else {
                    //else if(board[nexty][nextx] == '.') {
                        visited[nexty][nextx][keys] = visited[yy][xx][keys] + 1;
                        q.Put(mp(nexty, mp(nextx, keys)));
                    //}
                }
            }
        }
    }
    
    cout << (ret == INF ? -1 : ret) << endl;
    
    return 0;
}

//
//  main.cpp
//  11559
//
//  Created by jeongji su on 2018. 2. 9..
//  Copyright © 2018년 jeongji su. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

string board[13];
int visited[13][7];
const int dy[] = {0,0,-1,1};
const int dx[] = {-1,1,0,0};
int ret = 0;
vector<pair<int, int> > path;
void printBoard() {
    for(int i = 0 ; i < 12; i++) {
        cout << board[i] << endl;
    }
}

bool inRange(int y, int x) {
    return y >= 0 && y < 12 && x >= 0 && x < 6;
}

// 한 알파벳만 터짐만 찾음
void dfs(int sy, int sx, int pre) {
    
    visited[sy][sx] = 1;
    path.push_back(make_pair(sy, sx));
    
    for(int i = 0 ; i < 4 ; i++) {
        int ny = sy + dy[i];
        int nx = sx + dx[i];
        if(inRange(ny, nx) && pre == board[ny][nx] && !visited[ny][nx]) {
            dfs(ny, nx, pre);
            //path.push_back(make_pair(ny, nx));
        }
    }
    
    visited[sy][sx] = 0;
    
}

void down() {
    // 내리기
    for(int j = 5 ; j >= 0; j--) {
        for(int i = 11 ; i >= 0; i--) {
            for(int k = i-1 ; k >= 0 ; k--) {
                if(board[i][j] == '.' && board[k][j] != '.') {
                    board[i][j] = board[k][j];
                    board[k][j] = '.';
                    break;
                }
//                cout << "down" << endl;
//                printBoard();
            }
        }
}
}
int main(int argc, const char * argv[]) {
    
    freopen("/Users/JUNGJISU/Desktop/C++/11559/11559/input.txt", "r", stdin);
    
    for(int i = 0; i < 12; i++) {
        cin >> board[i];
    }
    
//    for(int i = 0; i < 12; i++) {
//        cout << board[i] << endl;
//    }
    
    
    while(true) {
        memset(visited, 0, sizeof(visited));
        bool idBomb = false;
        for(int i = 11 ; i >= 0 ; i--) {
            for(int j = 5 ; j >= 0 ; j--) {
                if(board[i][j] != '.' && !visited[i][j]) {
                    dfs(i, j, board[i][j]);
                    // 지우기
                    if(path.size() >= 4) {
                        idBomb = true;
                        for(int i = 0 ; i < path.size(); i++) {
                            //cout << path[i].first << ", " << path[i].second << endl;
                            board[path[i].first][path[i].second] = '.';
                        }
//                        cout << "remove" << endl;
//                        printBoard();
                    }
                    path.clear();
                }
            }
        }
        down();
        if(idBomb) ret++;
        else break;
    }
    
    cout << ret << endl;
    
    
    return 0;
}

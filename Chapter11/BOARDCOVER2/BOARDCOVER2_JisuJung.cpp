//
//  main.cpp
//  boardcover2
//
//  Created by smartgrid_aict on 2017. 7. 17..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//
/*
 풀이과정
 1. 블럭을 회전시켜 4가지 모양을 좌표로 저장한다.
 2. 보드판에 블럭을 놓는다.
 3. 블럭을 놓으면서 최대값을 찾는다.
 4. 보드판에서 블럭을 떼어낸다.
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> block(10), board(10);
vector<vector<pair<int, int> > > coverType(4);
int r,c,h,w,best;

bool inRange(int y, int x) {
    return y >= 0 && y < h && x >= 0 && x < w;
}

vector<string> rotate1(vector<string>& block) {
    
    // ret의 길이를 잡아주지 않으면 값을 넣을 수 없지!
    vector<string> ret(block[0].size(), string(block.size(), ' '));
    for(int y = 0 ; y < block.size() ; y++) {
        for(int x = 0 ; x < block[0].size() ; x++) {
            ret[x][block.size()-y-1] = block[y][x];
        }
    }
    return ret;
}

// 무조건 붙이고 떼기
bool cover(int y, int x, int type) {
    bool possible = true;
    for(int j = 0; j < coverType[type].size(); j++) {
        int yy = y+coverType[type][j].first;
        int xx = x+coverType[type][j].second;
        if(!inRange(yy, xx)) {
            possible = false;
        } else if(board[yy][xx] == '#') {
            board[yy][xx] = '.';
            possible = false;
        } else if(board[yy][xx] == '.') {
            board[yy][xx] = '#';
        }
    }
    return possible;
}

void show() {
    for (int i = 0; i < board.size(); i++) {
        cout << board[i] << endl;
    }
    cout << endl;
}

// board의 y,x 위치에서 block 모양을 놓을때 최대로 놓을 수 있는 개수 반환
// blockFlag는 현재 위치에서 4가지 회전 블럭을 모두 사용헀는지 판단한다.
void backTracking(int num) {
    
    show();
    // 재귀를 들어왔을때, 한 블럭의 몇 번째 요소인지 판별 하는게 필요함
    // 4가지 블럭 중 몇 번째 회전 블럭인지도 판별해야함
    // 아니야, 6단원 문제처럼 type을 만들어서 한번에 놔야 한다.
    
    // 한 블럭의 다음 자리 검사는 재귀로
    // 현재 위치에서 새로운 모양 블럭 검사는 for로
    
    
    
    int yy = -1, xx = -1;
    
    for(int i = 0 ; i < h ; i++) {
        for(int z = 0 ; z < w ; z++) {
            if(board[i][z] == '.') {
                // 4가지 모양 검사
                yy = i;
                xx = z;
                break;
            }
        }
        if(yy != -1) break;
    }
    
    best = max(num, best);
    
    /*
     if(yy == -1) {
        
        return;
     }
    */
    for(int c = 0; c < 4; c++) {
        if(cover(yy, xx, c)) {
            backTracking(num + 1);
        }
        cover(yy, xx, c);
    }
    
}

int main(int argc, const char * argv[]) {
    
    
    freopen("/Users/smartgrid_aict/Desktop/JJS/algorithm/boardcover2/boardcover2/input.txt", "r", stdin);
    
    int T;
    scanf("%d", &T);
    
    while(T--) {
        
        board.clear();
        block.clear();
        coverType.clear();
        board.resize(10);
        block.resize(10);
        best = 0;
        
        scanf("%d %d %d %d", &h, &w, &r, &c);
        
        for(int i = 0; i< h; i++) {
            cin >> board[i];
        }
        
        for(int i = 0 ; i < r ; i++) {
            cin >> block[i];
        }
    
        // 전처리
        // 1. 블럭을 회전시켜 4가지 모양을 좌표로 저장한다. (how?)
        // 맨 윗줄 왼쪽 위치를 원점으로 좌표를 저장한다.
        for(int i = 0; i < 4; i++) {
            for(int j = 0 ; j < block.size() ; j++) {
                cout << block[j] << endl;
            }
            int y0 = -1, x0 = -1;
            for(int k = 0 ; k < block.size() ; k++) {
                for(int j = 0 ;  j < block[k].size() ; j++) {
                    if(block[k][j] == '#') {
                        if(y0 == -1) {
                            y0 = k;
                            x0 = j;
                        }
                        coverType[i].push_back(make_pair(k - y0, j - x0));
                        //cout << "(k, j) " << k - y0 << " " << j - x0 << endl;
                    }
                }
            }
            block = rotate1(block);
        }
        
        backTracking(0);
        
        cout << best << endl;
        /*
        sort(coverType.begin(), coverType.end());
        
        for(int j = 0; j < 4; j++) {
            cout << j << endl;
            for(int i = 0 ; i < coverType[j].size() ; i++) {
                cout << coverType[j][i].first << " " << coverType[j][i].second << endl;
                coverType.erase(unique(coverType.begin(), coverType.end()), coverType.end());
            }
        }
         */
        
    }
    
    return 0;
}

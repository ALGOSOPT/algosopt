#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX 101
#define mp make_pair
#define INF 0x3f3f3f3f
int dy[4] = {-1,0,1,0};
int dx[4] = {0,-1,0,1};
int n, ret = INF;

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
    return y >= 0 && y < n && x >= 0 && x < n;
}

int main() {
    
    string board[51];
    int visited[51][51][4];
    memset(visited, -1, sizeof(visited));
    freopen("/Users/smartgrid_aict/Desktop/algorithm/2151/2151/input.txt", "r", stdin);
    cin >> n;
    
    int starty = -1, startx = -1, endy = -1, endx = -1;
    for(int i = 0 ; i < n; i++) {
        cin >> board[i];
        for(int j = 0; j < n; j++) {
            if(board[i][j] == '#') {
                if(startx == -1) {
                    starty = i;
                    startx = j;
                } else if( endx == -1) {
                    endy = i;
                    endx = j;
                }
            }
        }
    }
    
//    cout << starty << " " << startx << endl;
//    cout << endy << " " << endx << endl;
    
    
    Queue q;
    // 시작은 4방향으로
    for(int i = 0 ; i < 4; i++) {
        int y = starty + dy[i];
        int x = startx + dx[i];
        if(inRange(y, x) && board[y][x] != '*') {
            q.Put(mp(y, mp(x, i)));
            visited[y][x][i] = 0;
        }
    }
    pair<int, pair<int, int> > d;
    
    while(q.Get(d)) {
        int yy = d.first;
        int xx = d.second.first;
        int dd = d.second.second; // 현재 방향
        
        //cout << yy << " " << xx << " " << dd << endl;
        
        if(yy == endy && xx == endx) {
            ret = min(ret, visited[yy][xx][dd]);
        }
        
        int nexty = yy + dy[dd];
        int nextx = xx + dx[dd];
        int nextd = dd;
        if(inRange(nexty, nextx) && (visited[nexty][nextx][dd] == -1 || visited[nexty][nextx][nextd] > visited[yy][xx][dd]) && board[nexty][nextx] != '*') {
            q.Put(mp(nexty, mp(nextx, dd)));
            visited[nexty][nextx][dd] = visited[yy][xx][dd];
            
        }
        // 거울이면 반사
        if(board[yy][xx] == '!') {
           // cout << "!!!!!" << yy << " " << xx << " " << dd << endl;
            if(dd % 2 == 0) {
                nexty = yy + dy[1];
                nextx = xx + dx[1];
                if(inRange(nexty, nextx) && (visited[nexty][nextx][1] == -1 || visited[nexty][nextx][1] > visited[yy][xx][dd]) &&  board[nexty][nextx] != '*') {
                    q.Put(mp(nexty, mp(nextx, 1)));
                    visited[nexty][nextx][1] = visited[yy][xx][dd] + 1;
                }
                nexty = yy + dy[3];
                nextx = xx + dx[3];
                if(inRange(nexty, nextx) && (visited[nexty][nextx][3] == -1 || visited[nexty][nextx][3] > visited[yy][xx][dd]) &&  board[nexty][nextx] != '*') {
                    q.Put(mp(nexty, mp(nextx, 3)));
                    visited[nexty][nextx][3] = visited[yy][xx][dd] + 1;
                }
            } else {
                nexty = yy + dy[0];
                nextx = xx + dx[0];
                if(inRange(nexty, nextx) && (visited[nexty][nextx][0] == -1 || visited[nexty][nextx][0] > visited[yy][xx][dd]) &&  board[nexty][nextx] != '*') {
                    q.Put(mp(nexty, mp(nextx, 0)));
                    visited[nexty][nextx][0] = visited[yy][xx][dd] + 1;
                }
                nexty = yy + dy[2];
                nextx = xx + dx[2];
                if(inRange(nexty, nextx) && (visited[nexty][nextx][2] == -1 || visited[nexty][nextx][2] > visited[yy][xx][dd]) &&  board[nexty][nextx] != '*') {
                    q.Put(mp(nexty, mp(nextx, 2)));
                    visited[nexty][nextx][2] = visited[yy][xx][dd] + 1;
                }
            }
        }
        
    }
    
    cout << ret << endl;
    
    return 0;
}

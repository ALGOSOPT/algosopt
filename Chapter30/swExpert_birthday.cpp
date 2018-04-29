#include <iostream>
using namespace std;

int map[1001][1001];
int opmap[1001][1001];
int N = 0;
int M = 0;
int X = 0;
int dist[1001];
int opdist[1001];
int totalDist[1001];


void initDistAndMap() {
    for (int x = 1; x <= N; x++) {
        for (int y = 1; y <= N; y++) {
            map[x][y] = 0;
            opmap[x][y] = 0;
        }
        dist[x] = 100000;
        opdist[x] = 100000;
    }
    dist[X] = 0;
    opdist[X] = 0;
}

void dijkstra(int start, bool isOp) {
    //int head = 0, tail = 0,
    //queue[tail++] = start;
    int visited[1001] = { 0 };
    int now = 0;
    int count = 0;
    int next = start;
    int min;
    while (count < N) {
        now = next;
        count++;
        min = 100000;
        visited[now] = 0;
        
        for (int i = 1; i <= N; i++) {
            if (!isOp) {
                if (map[now][i] != 0
                    && dist[i] > dist[now] + map[now][i]) {
                    dist[i] = dist[now] + map[now][i];
                    visited[i] = dist[i];
                }
            }
            else {
                if (opmap[now][i] != 0
                    && opdist[i] > opdist[now] + opmap[now][i]) {
                    opdist[i] = opdist[now] + opmap[now][i];
                    visited[i] = opdist[i];
                }
            }
        }
        
        for (int i = 1; i <= N; i++) {
            if (visited[i] != 0) {
                if (min > visited[i]) {
                    min = visited[i];
                    next = i;
                }
            }
        }
    }
}

int main(){
    int T = 0;
    int x, y, c = 0;
    
    freopen("/Users/JUNGJISU/Desktop/자료구조 정리/다익스트라+힙/다익스트라+힙/Text.txt", "r", stdin);
    cin >> T;
    
    for (int t = 0; t < T; t++) {
        cin >> N >> M >> X;
        
        // int map
        initDistAndMap();
        
        for (int i = 1; i <= M; i++) {
            cin >> x >> y >> c;
            map[x][y] = c;
            opmap[y][x] = c;
        }
        
        dijkstra(X, false);
        dijkstra(X, true);
        
        for (int i = 1; i <= N; i++) totalDist[i] = dist[i] + opdist[i];
        
        
        int max = totalDist[1];
        for (int i = 2; i <= N; i++)
            if (max < totalDist[i]) max = totalDist[i];
        
        printf("#%d %d\n", t + 1, max);
    }
}

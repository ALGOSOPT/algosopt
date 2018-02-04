#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

const int D[4][2] = {
    {0,1},{1,0},{0,-1},{-1,0}
};

int N,M;
char map[51][51];
int visited[51][51][1<<7];
int sX,sY;

struct Item {
    int y;
    int x;
    int key;
    int cost;
};
Item q[100000];

bool inRange(int y, int x) {
    return y >= 0 && y < N && x >= 0 && x < M;
}

int bfs()
{
    int front = 0;
    int rear = 0;
    visited[sY][sX][0] = 1;
    Item item = {sY,sX,0,1};
    // q[rear++] = item;
    queue<Item> q;
    q.push(item);

    // while(front < rear) {
    while(!q.empty()) {
        // int y = q[front].y;
        // int x = q[front].x;
        // int key = q[front].key;
        // int cost = q[front].cost;

        // front++;
        int y = q.front().y;
        int x = q.front().x;
        int key = q.front().key;
        int cost = q.front().cost;

        q.pop();

        if(map[y][x] == '1') {
            return visited[y][x][key];
        }

        for(int i=0; i<4; i++) {
            int nextX = x + D[i][0];
            int nextY = y + D[i][1];
            int nextCost = cost + 1;
            int nextKey = key;

            if(inRange(nextY, nextX) && map[nextY][nextX] != '#') {
                if('a' <= map[nextY][nextX] && map[nextY][nextX] <= 'f') {
                    nextKey |= (1 << (map[nextY][nextX]-'a'));
                }
                if('A' <= map[nextY][nextX] && map[nextY][nextX] <= 'F') {
                    if(((key >> (map[nextY][nextX]-'A')) & 1) == 0) continue;
                }

                if(visited[nextY][nextX][nextKey] != -1) continue;

                visited[nextY][nextX][nextKey] = nextCost;
                Item nextItem = {nextY,nextX,nextKey,nextCost};
                // q[rear++] = nextItem;
                q.push(nextItem);
            }
        }
    }
    return -1;
}

int main()
{
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++) {
        string s;
        cin >> s;
        for(int j=0; j<M; j++) {
            map[i][j] = s[j];
            if(s[j] == '0') {
                sY = i;
                sX = j;
            }
        }
    }

    memset(visited, -1, sizeof(visited));
    printf("%d\n", bfs()-1);
    return 0;
}

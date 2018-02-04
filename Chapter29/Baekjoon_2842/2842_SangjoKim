#include <cstdio>
#include <algorithm>
using namespace std;
 
int n;
char inputMap[55][55];
int height[55][55];
int range[2600];
int visit[55][55];
int ans = 1e9;
int dy[8] = { -1, 0, 0, 1, -1, -1, 1, 1 };
int dx[8] = { 0, -1, 1, 0, -1, 1, -1, 1 };
 
int dfs(int y, int x, int s, int e) {
    int res = 0;
 
    if (height[y][x] < s || height[y][x] > e)    return 0;
    if (inputMap[y][x] == 'K')                        
        res = 1;
 
    for (int i = 0; i < 8; i++) {
        int nexty = y + dy[i];
        int nextx = x + dx[i];
 
        if (nexty >= 0 && nexty < n && nextx >= 0 && nextx < n) {
            if (visit[nexty][nextx] == 0) {
                visit[nexty][nextx] = 1;
                res += dfs(nexty, nextx, s, e);
            }
        }
    }
    return res;
}
 
void solve()
{
    int sz = 0;
    int starty, startx;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (inputMap[i][j] == 'P') {
                starty = i;
                startx = j;
            }
            if (inputMap[i][j] == 'K')    sz++;
        }
    }
 
    sort(range, range + n * n);
 
    int cnt = 1;
    for (int i = 1; i < n * n; i++) {
        if (range[i - 1] != range[i])        range[cnt++] = range[i];
    }
    
    int s = 0, e = 0;
    while (e < cnt) {
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                visit[i][j] = 0;
            }
        }
 
        visit[starty][startx] = 1;
        if(dfs(starty, startx, range[s], range[e]) == sz) {
            if (range[e] - range[s] < ans)    ans = range[e] - range[s];
            s++;
        }
        else    e++;
    }
 
    printf("%d\n", ans);
}
 
int main()
{
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++) {
        scanf("%s", inputMap[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &height[i][j]);
            range[i * n + j] = height[i][j];
        }
    }
 
    solve();
 
    return 0;
}



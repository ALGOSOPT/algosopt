#include<stdio.h>
#include<vector>

using namespace std;
const int MAX_N = 5e5;
int n, m, d[MAX_N + 1], u[MAX_N + 1], cnt, w[MAX_N + 1], s[MAX_N + 1];
vector<int> adj[MAX_N + 1];

void dfs(int h) {
    d[h] = ++cnt;
    for (auto it : adj[h]) dfs(it);
    u[h] = cnt;
}

void update(int h, int x) { for (; h <= n; h += h&-h) s[h] += x; }
int query(int h) {
    int r = 0;
    for (; h; h -= h&-h) r += s[h];
    return r;
}

int main() {
    scanf("%d %d %d", &n, &m, w + 1);
    for (int i = 2, p; i <= n; i++) scanf("%d %d", w + i, &p), adj[p].push_back(i);
    dfs(1);
    for (int i = 1; i <= n; i++) update(d[i], w[i]), update(d[i] + 1, -w[i]);
    for (int i = 0, a, b; i < m; i++) {
        char c;
        scanf(" %c", &c);
        if (c == 'p') {
            scanf("%d %d", &a, &b);
            update(d[a] + 1, b);
            update(u[a] + 1, -b);
        }
        else {
            scanf("%d", &a);
            printf("%d\n", query(d[a]));
        }
    }
    return 0;
}

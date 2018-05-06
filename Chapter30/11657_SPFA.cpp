#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
struct Edge {
    int to, cost;
    Edge() {
    }
    Edge(int to, int cost) : to(to), cost(cost) {
    }
};
vector<Edge> a[501];
const int inf = 1000000000;
int d[501];
bool c[501];
int cnt[501];
int main() {
    int n, m;
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int from, to, cost;
        scanf("%d %d %d",&from, &to, &cost);
        a[from].push_back(Edge(to,cost));
    }
    for (int i=1; i<=n; i++) {
        d[i] = inf;
    }
    d[1] = 0;
    queue<int> q;
    q.push(1);
    c[1] = true;
    while (!q.empty()) {
        int from = q.front();
        c[from] = false;
        q.pop();
        for (Edge &e : a[from]) {
            int to = e.to;
            int cost = e.cost;
            if (d[to] > d[from] + cost) {
                d[to] = d[from] + cost;
                if (c[to] == false) {
                    q.push(to);
                    c[to] = true;
                    cnt[to] += 1;
                    if (cnt[to] >= n) {
                        printf("-1\n");
                        return 0;
                    }
                }
            }
        }
    }
    for (int i=2; i<=n; i++) {
        if (d[i] == inf) {
            printf("-1\n");
        } else {
            printf("%d\n",d[i]);
        }
    }
    return 0;
}

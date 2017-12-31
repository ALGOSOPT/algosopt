#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
 
#define swap(a,b){int t = a; a = b; b = t;}
#define MAX_NODE 40001
 
using namespace std;
 
// depth :: 노드의 깊이(레벨)
// ac[x][y] :: x의 2^y번째 조상을 의미
int depth[MAX_NODE];
int ac[MAX_NODE][20];
 
typedef pair<int, int> pii;
vector<pii> graph[MAX_NODE];
 
// 루트 노드(1)에서 x까지의 거리
long long dist[MAX_NODE];
 
int max_level;
 
// DP(ac)배열 만드는 과정
void getTree(int here, int parent, int val)
{
    // here의 깊이는 부모노드깊이 + 1
    depth[here] = depth[parent] + 1;
 
    // here이 1인 경우에는 dist[1] = 0
    // 그 외에 경우에는 루트노드에서 자신의 부모와의 거리 + 자신의 부모와 자신과의 거리를 담는다.
    if (here != 1)
        dist[here] += dist[parent] + val;
 
    // here의 1번째 조상은 부모노드
    ac[here][0] = parent;
    
    // MAX_NODE에 log2를 씌어 내림을 해준다.
    max_level = (int)floor(log2(MAX_NODE));
 
    for (int i = 1; i <= max_level; i++)
    {
        // tmp :: here의 2^(i-1)번째 조상
        int tmp = ac[here][i - 1];
        ac[here][i] = ac[tmp][i - 1];
    }
 
    // dfs 알고리즘
    int len = graph[here].size();
    for (int i = 0; i < len; i++)
    {
        int there = graph[here][i].first;
        if (there != parent)
            getTree(there, here, graph[here][i].second);
    }
}
 
int main()
{
    int n, m;
 
    scanf("%d", &n);
 
    // 양방향 그래프 형성
    for (int i = 1; i < n; i++)
    {
        int from, to, val;
        scanf("%d %d %d", &from, &to, &val);
        graph[from].push_back(pii(to,val));
        graph[to].push_back(pii(from, val));
    }
 
    // make_tree에 1,0이 들어가기때문에 0은 -1로 지정
    depth[0] = -1;
 
    // 루트 노드인 1번 노드부터 트리 형성
    getTree(1, 0, 0);
 
    // 쿼리문 시작
    scanf("%d", &m);
 
    while (m--)
    {
        int a, b;
        scanf("%d %d", &a, &b);
 
        // tmpa, tmpb는 a와 b의 원래 모습을 가지고 있는다.
        int tmpa = a;
        int tmpb = b;
 
        if (depth[a] != depth[b])
        {
            // depth[b] >= depth[a]가 되도록 swap
            if (depth[a] > depth[b])
                swap(a, b);
 
            // b를 올려서 depth를 맞춰준다.
            int j = 0;
            for (int i = max_level; i >= 0; i--)
            {
                if (depth[a] <= depth[ac[b][i]])
                    b = ac[b][i];
            }
        }
 
        int lca = a;
 
        if (a != b)
        {
            for (int i = max_level; i >= 0; i--)
            {
                if (ac[a][i] != ac[b][i])
                {
                    a = ac[a][i];
                    b = ac[b][i];
                }
                lca = ac[a][i];
            }
        }
 
        // 루트노드와 tmpa와의 거리 - 루트노드와 lca와의 거리 
        //                                 +
        // 루트노드와 tmpb와의거리 - 루트노드와 lca와의 거리
        printf("%lld\n", dist[tmpa] + dist[tmpb]- 2*dist[lca] );
    }
    return 0;
}

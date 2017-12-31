#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
 
#define swap(a,b){int t = a; a = b; b = t;}
#define MAX_NODE 40001
 
using namespace std;
 
// depth :: ����� ����(����)
// ac[x][y] :: x�� 2^y��° ������ �ǹ�
int depth[MAX_NODE];
int ac[MAX_NODE][20];
 
typedef pair<int, int> pii;
vector<pii> graph[MAX_NODE];
 
// ��Ʈ ���(1)���� x������ �Ÿ�
long long dist[MAX_NODE];
 
int max_level;
 
// DP(ac)�迭 ����� ����
void getTree(int here, int parent, int val)
{
    // here�� ���̴� �θ������ + 1
    depth[here] = depth[parent] + 1;
 
    // here�� 1�� ��쿡�� dist[1] = 0
    // �� �ܿ� ��쿡�� ��Ʈ��忡�� �ڽ��� �θ���� �Ÿ� + �ڽ��� �θ�� �ڽŰ��� �Ÿ��� ��´�.
    if (here != 1)
        dist[here] += dist[parent] + val;
 
    // here�� 1��° ������ �θ���
    ac[here][0] = parent;
    
    // MAX_NODE�� log2�� ���� ������ ���ش�.
    max_level = (int)floor(log2(MAX_NODE));
 
    for (int i = 1; i <= max_level; i++)
    {
        // tmp :: here�� 2^(i-1)��° ����
        int tmp = ac[here][i - 1];
        ac[here][i] = ac[tmp][i - 1];
    }
 
    // dfs �˰���
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
 
    // ����� �׷��� ����
    for (int i = 1; i < n; i++)
    {
        int from, to, val;
        scanf("%d %d %d", &from, &to, &val);
        graph[from].push_back(pii(to,val));
        graph[to].push_back(pii(from, val));
    }
 
    // make_tree�� 1,0�� ���⶧���� 0�� -1�� ����
    depth[0] = -1;
 
    // ��Ʈ ����� 1�� ������ Ʈ�� ����
    getTree(1, 0, 0);
 
    // ������ ����
    scanf("%d", &m);
 
    while (m--)
    {
        int a, b;
        scanf("%d %d", &a, &b);
 
        // tmpa, tmpb�� a�� b�� ���� ����� ������ �ִ´�.
        int tmpa = a;
        int tmpb = b;
 
        if (depth[a] != depth[b])
        {
            // depth[b] >= depth[a]�� �ǵ��� swap
            if (depth[a] > depth[b])
                swap(a, b);
 
            // b�� �÷��� depth�� �����ش�.
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
 
        // ��Ʈ���� tmpa���� �Ÿ� - ��Ʈ���� lca���� �Ÿ� 
        //                                 +
        // ��Ʈ���� tmpb���ǰŸ� - ��Ʈ���� lca���� �Ÿ�
        printf("%lld\n", dist[tmpa] + dist[tmpb]- 2*dist[lca] );
    }
    return 0;
}

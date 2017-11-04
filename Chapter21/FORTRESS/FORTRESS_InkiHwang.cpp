#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int oo = 0x3f3f3f3f;

struct Circle{
    int x;
    int y;
    int r;
    vector<int> children;
};

// parent가 child의 부모가 되는지 확인
bool isParent(Circle* tree, int child, int parent);
// n 노드의 서브트리 높이를 구한다
int getHeight(Circle* tree, int n);
int main()
{
    int testCase;
    scanf("%d", &testCase);
    while(testCase--) {
        Circle tree[101];
        int n;
        int root = 0;
        scanf("%d", &n);
        for(int i=1; i<=n; i++) {
            int x,y,r;
            scanf("%d %d %d", &x, &y, &r);
            tree[i].x = x;
            tree[i].y = y;
            tree[i].r = r;
        }

        for(int i=1; i<=n; i++) {
            int parent = 0;
            int d = oo;
            for(int j=1; j<=n; j++) {
                if(i == j) continue;
                // i가 j 원 안에 있으면서 가장 가까이 있으면 부모는 j가 된다
                if(isParent(tree, i, j) && d > tree[j].r - tree[i].r) {
                    d = tree[j].r - tree[i].r;
                    parent = j;
                }
            }
            // 부모가 없으면 i노드를 루트다
            if(parent == 0) root = i;
            else {
                tree[parent].children.push_back(i);
            }
        }

        int ret;
        // 트리의 depth를 구한다
        ret = getHeight(tree, root);
        // 각 노드들의 서브트리 최대 높이 2개를 구하고 더한다
        for(int i=1; i<=n; i++) {
            if(tree[i].children.size() >= 2) {
                int max1=0, max2=0;
                for(int j=0; j<tree[i].children.size(); j++) {
                    int tmp = getHeight(tree, tree[i].children[j]);
                    if(tmp > max1 || tmp > max2) {
                        if(max1 > max2) max2 = tmp;
                        else max1 = tmp;
                    }
                }
                ret = max(ret, max1+max2+2);
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}

bool isParent(Circle* tree, int child, int parent)
{
    int sqx = (tree[parent].x-tree[child].x)*(tree[parent].x-tree[child].x);
    int sqy = (tree[parent].y-tree[child].y)*(tree[parent].y-tree[child].y);
    int sqr = (tree[parent].r-tree[child].r)*(tree[parent].r-tree[child].r);
    if(tree[parent].r > tree[child].r && sqx + sqy <= sqr) {
        return true;
    }
    return false;
}

int getHeight(Circle* tree, int n)
{
    if(tree[n].children.size() == 0) {
        return 0;
    }

    int ret = 0;
    for(int i=0; i<tree[n].children.size(); i++) {
        ret = max(ret, getHeight(tree, tree[n].children[i])+1);
    }
    return ret;
}

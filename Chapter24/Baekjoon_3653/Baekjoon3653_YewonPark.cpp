#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX_N 100000

using namespace std;

int seg[800000], a[200001];

int update(int pos, int val, int node, int left, int right) {
    if (right < pos || pos < left)
        return seg[node];
    if (left == right)
        return seg[node] = val;
    int mid = (left + right) / 2;
    return seg[node] = update(pos, val, node * 2, left, mid) + update(pos, val, node * 2 + 1, mid + 1, right);
}

int query(int lo, int hi, int node, int left, int right) {
    if (right < lo || hi < left)
        return 0;
    if (lo <= left&&right <= hi)
        return seg[node];
    int mid = (left + right) / 2;
    return query(lo, hi, node * 2, left, mid) + query(lo, hi, node * 2 + 1, mid + 1, right);
}

int main() {
    
	int t;
	scanf("%d", &t);
    while (t--) {
    	
    	int n, m, num;
        memset(a, 0, sizeof(a));
        memset(seg, 0, sizeof(seg));
        
		scanf("%d %d", &n, &m);
        
		int idx = m + 1;
        
		for (int i = idx; i <= n + m; i++) {
            update(i, 1, 1, 1, n + m);
            a[i - m] = i;//위치 저장해둠 
        }
        
		idx = m;
        
		for (int i = 0; i < m; i++) {
            scanf("%d", &num);
            printf("%d ", query(1, a[num] - 1, 1, 1, n + m));
            update(a[num], 0, 1, 1, n + m);
            a[num] = idx;
            idx--;
            update(a[num], 1, 1, 1, n + m);
        }
        printf("\n");
    }
    return 0;
}

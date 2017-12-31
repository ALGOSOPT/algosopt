#include<cstdio>
#include<algorithm>

using namespace std;

int n, a[1000000], sz, x;
int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &x);
        int p = lower_bound(a, a + sz, x) - a;
        sz += p == sz;
        a[p] = x;
    }
    printf("%d", sz);
    return 0;
}

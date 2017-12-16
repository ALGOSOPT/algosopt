#include <cstdio>
#include <algorithm>
using namespace std;
 
class Number {
    int value, idx;
};
 
int n;
Number number[100001];
 
bool cmp(const Number &first, const Number &second)
{
    return first.value < second.value;
}
 
int main()
{
    scanf("%d %d", &n, &m);
 
    for (int i = 0; i <= n; i++) {
        scanf("%d", &num[i].value);
        num[i].idx = i;
    }
 
    sort(number, number + n, cmp);
 
    for (int i = 0; i < m; i++) {
        int s, e, k;
        scanf("%d %d %d", &s, &e, &k);
        s--, e--, k--;
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (number[j].idx >= s && number[j].idx <= e)
              cnt++;
            if (cnt == k)    {
                printf("%d\n", number[j].value);
                break;    
            }
        }
    }
 
    return 0;
}

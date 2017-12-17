#include <iostream>
#include <cstdio>
#include <algorithm>
 
using namespace std;
 
struct _arr
{
    int num;
    int idx;
};
 
bool comp(_arr const& a, _arr const& b) {
    return a.num < b.num;
}
 
 
_arr arr[5000001];
 
int main()
{
    int n, k, i, j;
    int cnt = 0;
    int start, end, target;
 
 	cin >> n >> k;
 
    for (i = 0; i < n; i++)
    {
    	cin >> arr[i].num;
        arr[i].idx = i+1;
    }
 
    std::sort(arr, arr+n, comp);
 
    for (i = 0; i < k; i++)
    {
    	cin >> start >> end >> target;
        
        for (j = 0; j < n; j++)
        {
            if (start <= arr[j].idx && arr[j].idx <= end)
                cnt++;
 
            if(cnt == target)
            {
                cout << arr[j].num << "\n";
                break;
            }
 
        }
        cnt = 0;
 
    }
}

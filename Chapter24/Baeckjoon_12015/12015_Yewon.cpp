#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
 
vector<int> v;
 
const int MAX = 1000001;

int main()
{
    int n;
    cin >> n;
 
    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        v.push_back(temp);
    }
 
    vector<int> lis(n + 1, MAX);
    
 
    for (int i = 0; i < n; i++){
        auto iter = lower_bound(lis.begin(), lis.end(), v[i]) - lis.begin();
        lis[iter] = v[i];
    }
 
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (lis[i] != MAX)
            cnt++;
 
    cout << cnt;
 
    return 0;
}

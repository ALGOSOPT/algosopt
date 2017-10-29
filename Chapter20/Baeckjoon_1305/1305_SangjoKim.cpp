#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
vector<int> pi;
int n;
string x;
void getpi(){
    int j = 0;
    for (int i = 1; i < n; i++)
    {
        while (j > 0 && x[i] != x[j])
            j = pi[j - 1];
        if (x[i] == x[j])
            pi[i] = ++j;
    }
}
int main(){
    scanf("%d", &n);
    pi.resize(n + 1);
    cin >> x;
    getpi();
    printf("%d\n", n - pi[n - 1]);
    return 0;
}



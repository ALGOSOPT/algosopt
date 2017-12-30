#include <iostream>
#include <algorithm>
using namespace std;
 
int arr[1000001], L[1000001], P[1000001], len, N;
void backtrace(int idx, int num) {
    if(idx == 0)
        return;
    if(P[idx] == num) {
        backtrace(idx - 1, num - 1);
        //cout << arr[idx] << " ";
    }
    else {
        backtrace(idx - 1, num);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin >> N;
    for(int i = 1; i <= N; ++i) {
        cin >> arr[i];
        auto pos = lower_bound(L + 1, L + len + 1, arr[i]);
        *pos = arr[i];
        P[i] = distance(L, pos);
        if(pos == L + len + 1)
            len++;
    }
    cout << len << "\n";
    backtrace(N, len);
    return 0;
}
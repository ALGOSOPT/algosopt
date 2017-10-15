#include <iostream>
#include <cstdio>
#include <deque>
#include <cmath>
#include <queue>

using namespace std;
typedef long long ll;


ll nextSignal(ll before){
	return (before * 214013u + 2531011u) % (ll)pow(2, 32);
}

int main(){
	freopen("input.txt","r",stdin);

	int TC; cin>>TC;
	while(TC--){

		ll k, n;
		cin>>k>>n;
		// cout<<k<<" "<<n<<endl;
		ll before = 1983;
		ll sum  = 0;
		ll ret = 0;
		queue<ll> q;
		for(int i = 0; i < n; i++){
			ll now = before % 10000u + 1u;
			before = nextSignal(before);

			while(!q.empty() && sum + now > k){
				sum -= q.front();
				q.pop();
			}

			sum += now;
			ret += (sum == k);
			q.push(now);
		}
		cout<<ret<<endl;
	}
	return 0;
}
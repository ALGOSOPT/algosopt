// 당연히 TLE

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> init(vector<long long>& a, vector<vector<long long> >& tree, int node, int start, int end) {
    if(start == end) {
      tree[node].push_back(a[start]);
      return tree[node];
    }
    int mid = (start+end)/2;
    vector<long long> tmp1 = init(a, tree, node*2, start, mid);
    vector<long long> tmp2 = init(a, tree, node*2+1, mid+1, end);
    vector<long long> ret;
    for(int i=0; i<tmp1.size(); i++) {
      ret.push_back(tmp1[i]);
    }
    for(int i=0; i<tmp2.size(); i++) {
      ret.push_back(tmp2[i]);
    }
    return tree[node] = ret;
}

vector<long long> query(vector<vector<long long> >& tree,  int node, int start, int end, int left, int right) {
    if(start > right || end < left) {
      return vector<long long>(0);
    }
    if(left <= start && end <= right) {
      return tree[node];
    }
    int mid = (start+end)/2;
    vector<long long> tmp1 = query(tree, node*2, start, mid, left, right);
    vector<long long> tmp2 = query(tree, node*2+1, mid+1, end, left, right);
    vector<long long> ret;
    for(int i=0; i<tmp1.size(); i++) {
      ret.push_back(tmp1[i]);
    }
    for(int i=0; i<tmp2.size(); i++) {
      ret.push_back(tmp2[i]);
    }
    return ret;
}

int main()
{
  int n,m;
  scanf("%d %d", &n, &m);
  vector<long long> a(n);
  vector<vector<long long> > tree(4*n);
  for(int i=0; i<n; i++) {
    scanf("%lld", &a[i]);
  }
  init(a, tree, 1, 0, n-1);
  for(int i=0; i<m; i++) {
    int u,v,q;
    scanf("%d %d %d", &u, &v, &q);
    vector<long long> tmp = query(tree, 1, 0, n-1, u-1, v-1);
    sort(tmp.begin(), tmp.end());
    printf("%lld\n", tmp[q-1]);
  }
  return 0;
}

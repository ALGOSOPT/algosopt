#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string H;
string N;

vector<int> getpi()
{
  int n = N.size();
  vector<int> pi(n, 0);

  int j=0;
  for(int i=1; i<n; i++) {
    while(j>0 && N[i] != N[j]) {
      j = pi[j-1];
    }
    if(N[i] == N[j]) {
      pi[i] = ++j;
    }
  }
  return pi;
}

vector<int> kmp()
{
  int h = H.size();
  int n = N.size();

  vector<int> pi = getpi();
  vector<int> ret;

  int j=0;
  for(int i=0; i<h; i++) {
    while(j>0 && H[i] != N[j]) {
      j = pi[j-1];
    }
    if(H[i] == N[j]) {
      j++;
      if(j == n) {
        ret.push_back(i-n+1);
        j = pi[j-1];
      }
    }
  }
  return ret;
}

int main()
{
  getline(cin, H);
  getline(cin, N);
  vector<int> ret = kmp();
  printf("%d\n", ret.size());
  for(int i=0; i<ret.size(); i++) {
    printf("%d\n", ret[i]+1);
  }
  return 0;
}

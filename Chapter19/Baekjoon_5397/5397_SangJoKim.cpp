#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

int main(){
	freopen("input.txt","r",stdin);

	int TC; cin>>TC;
	while(TC--){
		string inp; cin>>inp;
		stack<char> st1, st2;

		for(int i = 0; i < inp.size(); i++){
			if(inp[i] == '<'){
				if(!st1.empty()){
					st2.push(st1.top());
					st1.pop();
				}
			}
			else if(inp[i] == '>'){
				if(!st2.empty()){
					st1.push(st2.top());
					st2.pop();
				}
			}
			else if(inp[i] == '-'){
				if(!st1.empty()){
					st1.pop();
				}
			}
			else{
				st1.push(inp[i]);				
			}
		}

		while(!st2.empty()){
			st1.push(st2.top());
			st2.pop();
		}

		string ret = "";
		while(!st1.empty()){
			ret += st1.top(); st1.pop();
		}

		reverse(ret.begin(), ret.end());
		cout<<ret<<endl;

	}
	return 0;
}
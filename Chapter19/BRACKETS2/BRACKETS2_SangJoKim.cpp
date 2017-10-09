#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <string>
#include <map>

using namespace std;

int main(){
	freopen("input.txt","r",stdin);

	int TC; cin>>TC;
	string opening = "[{(", closing  = "]})";
	while(TC--){

		string sentence;
		cin>>sentence;
		stack<int> st;
		bool ans = true;
		for(int i = 0; i < sentence.size(); i++){
			char This = sentence[i];
			bool isOpening = false; 

			int number;

			for(int j = 0; j < opening.size(); j++){
				if(This == opening[j]){
					st.push(j);
					isOpening = true;
					number = j;
					break;
				}
			}

			if(isOpening) continue;
			int Top = st.top();
			
			number = closing.find(This);
			if(st.empty() || Top != number){
				ans = false;
				break;
			}
			st.pop();
		}

		if(!st.empty()){
			ans = false;
		}
		if(ans)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;

	}
	return 0;
}
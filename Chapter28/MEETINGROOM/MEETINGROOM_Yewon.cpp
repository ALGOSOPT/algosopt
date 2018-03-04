#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;
 
vector<vector<int> > adj;
vector<int> sccId;
vector<int> discovered, finished;
stack<int> st;
int sccCounter, vertexCounter;
 
bool disjoint(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second <= b.first || b.second <= a.first;
}
 
void makeGraph(const vector<pair<int, int> >& meeting_time) {
    int vars = meeting_time.size();
 
    adj.clear(); 
    adj.resize(vars * 2);
 
    for (int i = 0; i < vars; i += 2) {
        int j = i + 1;
        adj[i * 2 + 1].push_back(j * 2);
        adj[j * 2 + 1].push_back(i * 2);
    }
 
    for (int i = 0; i < vars; i++)
        for (int j = 0; j < i; j++) {
            
            if (!disjoint(meeting_time[i], meeting_time[j])) {
                adj[i * 2].push_back(j * 2 + 1);
                adj[j * 2].push_back(i * 2 + 1);
            }
        }
}
 
int scc(int here) {
    int ret = discovered[here] = vertexCounter++;
    
    st.push(here);
    for (int i = 0; i < adj[here].size(); ++i) {
        int there = adj[here][i];
        
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        
        else if (discovered[there] < discovered[here] && finished[there] != 1)
            ret = min(ret, discovered[there]);
    }
    
    
    if (ret == discovered[here]) {
        
        while (true) {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if (t == here) break;
        }
        ++sccCounter;
    }
    finished[here] = 1;
    return ret;
}
 
vector<int> tarjanSCC() {
    sccId = vector<int>(adj.size(), -1);
    discovered = vector<int>(adj.size(), -1);
    finished = vector<int>(adj.size(), -1);
    
    sccCounter = vertexCounter = 0;
    for (int i = 0; i < adj.size(); i++)
        if (discovered[i] == -1)
            scc(i);
    return sccId;
} 
 
vector<int> solve(const vector<pair<int, int> >& meeting_time) {
    int n = meeting_time.size();
 
    makeGraph(meeting_time);
 
    vector<int> label = tarjanSCC();
 
    for (int i = 0; i < 2 * n; i += 2)
        if (label[i] == label[i + 1])
            return vector<int>();
 
    vector<int> value(2 * n, -1);
 
    vector<pair<int, int> > order;
    for (int i = 0; i < 2 * n; i++)
        order.push_back(make_pair(-label[i], i));
    sort(order.begin(), order.end());
 
    for (int i = 0; i < 2 * n; ++i) {
        int vertex = order[i].second;
        int variable = vertex / 2; 
        int isTrue = vertex % 2 == 0;
        if (value[variable] != -1) 
            continue;
        value[variable] = !isTrue;
    }
 
    return value;
}
 
int main(){
	int c;
	scanf("%d", &c);
	while(c--){
		int n;
		scanf("%d", &n);
		vector<pair<int, int> > meetings;
		for(int i=0; i<n; i++){
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			meetings.push_back(make_pair(a, b));
			meetings.push_back(make_pair(c, d)); 
		}
		vector<int> result = solve(meetings);
		if(result.size() == 0){
			printf("IMPOSSIBLE\n");
			continue;	
		}
		printf("POSSIBLE\n");
		for(int i=0; i<n*2; i++){
			if(result[i] == 1)
				printf("%d %d\n", meetings[i].first, meetings[i].second);
		}
	}
}

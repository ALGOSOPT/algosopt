#include<cstdio>
#include<vector>
#include<stack>

using namespace std;

vector<vector<int> > adj;
vector<int> sccId;
vector<int> discovered, finished;
stack<int> st;
int sccCounter, vertexCounter; 
//vertexCounter은 방문순서
 
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

vector<int> tarjanSCC(){
	sccId = discovered = vector<int>(adj.size(), -1);
	 finished = vector<int>(adj.size(), -1);
	sccCounter = vertexCounter = 0;
	for(int i=0; i<adj.size(); i++)
		if(discovered[i] == -1)
			scc(i);
	return sccId;
} 

int main(){
	int t;
	scanf("%d", &t);
	while(t--){ 
		int n, m;
		scanf("%d%d", &n, &m);
		adj = vector<vector<int> >(n);
		for(int i=0; i<m; i++){
			int a, b;
			scanf("%d%d", &a, &b);
			adj[a-1].push_back(b-1);
		}
		//indegree가 0인 component를 찾아야함 
		vector<int> label = tarjanSCC();
		for(int i=0; i<label.size(); i++)
			printf("%d ", label[i]);
			
		vector<int> indegree(n);
		for(int i=0; i<n; i++){
			for(int j=0; j<adj[i].size(); j++)
				if(sccId[i] != sccId[j])
					indegree[sccId[j]]++;
		}
		int result = 0;
		for(int i=0; i<sccCounter; i++)
			if(indegree[i] == 0)
				result++;
		printf("%d", result);
	}
}

#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

const int MAX_DISC = 12;

//현재 상태와 원판의 번호를 인자로 받고 몇 번째 기둥에 있는 지 반환 
int get(int state, int index){
	return (state >> (index*2)) & 3; 
}

int set(int state, int index, int value){
	return (state&~(3<<(index*2))) | (value<<(index*2));
}

int c(1<<MAX_DISC*2);//비트마스크(각 원반이 어디 위치하는 지 저장) 

int sgn(int x){
	if(!x)
		return 0;
	return x>0?1:-1;
} 

int incr(int x){
	if(x<0)
		return x-1;
	return x+1;
}

int bfs(int discs, int begin, int end){
	if(begin==end)
		return 0;
	
	queue<int> q;
	memset(c, 0, sizeof(c));
	q.push(begin);
	q.push(end);
	c[begin] = 1;
	c[end] = =1;
	while(!q.empty()){
		int here = q.front();
		q.pop();
		int top[4] = {-1, -1, -1, -1};
		for(int i=i=discs-1; i>=0; --i)
			top[get(here, i)] = i;
		for(int i=0; i<4; ++i)
			if(top[i] != -1)
				for(int j=0; j<4; ++j)
					if(i != j && (top[j] == -1 || top[j]>top[i])){
						int there = set(here, top[i], j);
						if(c[there] == 0){
							c[there] = incr(c[here]);
							q.push(there);
						}
						else if(sgn(c[there] != sgn(c[there])))
							return abs(c[there]) + abs(c[here]) - 1;
					}
	}
	return -1;
}

int main()
{
    int testCase;
    scanf("%d", &testCase);
    while(testCase--) {
        int begin = 0;
        int n;
        scanf("%d", &n);
        // begin
        for(int i=0; i<4; i++) {
            int num;
            scanf("%d", &num);
            for(int j=0; j<num; j++) {
                int d;
                scanf("%d", &d);
                begin = set(begin, d-1, i);
            }
        }
        
        int end = 0;
        // end
        for(int i=0; i<4; i++) {
            int num;
            scanf("%d", &num);
            for(int j=0; j<num; j++) {
                int d;
                scanf("%d", &d);
                end = set(end, d-1, i);
            }
        }
        int ret = bfs(n, begin, end);
        printf("%d\n", ret);
    }
    return 0;
}


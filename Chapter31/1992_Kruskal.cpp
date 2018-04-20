#include <cstdio>
#include <algorithm>
using namespace std;
 
int uf[1000]; // union-find 배열
 
// union-find의 find 연산
int find(int a){
    if(uf[a] < 0) return a;
    return uf[a] = find(uf[a]);
}
 
// union-find의 union 연산
bool merge(int a, int b){
    a = find(a);
    b = find(b);
    if(a == b) return false;
    uf[b] = a;
    return true;
}
 
// 간선 구조체. w 기준으로 정렬됨
struct Edge{
    int u, v, w;
    Edge(): Edge(-1, -1, 0){}
    Edge(int u1, int v1, int w1): u(u1), v(v1), w(w1){}
    bool operator <(const Edge& O)const{ return w < O.w; }
};
 
int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Edge e[100000];
    for(int i=0; i<M; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        e[i] = Edge(a-1, b-1, c);
    }
    // 간선을 가중치 기준으로 오름차순 정렬
    sort(e, e+M);
 
    // result: 가중치합, cnt: 뽑은 간선 수
    int result = 0, cnt = 0;
    fill(uf, uf+N, -1);
    for(int i=0; ; i++){
        if(merge(e[i].u, e[i].v)){
            result += e[i].w;
            if(++cnt == N-1) break; // N-1개 간선을 뽑으면 나감
        }
    }
    printf("%d\n", result);
}



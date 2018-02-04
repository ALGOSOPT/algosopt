#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int MAX_DISCS = 12;
int c[1<<(MAX_DISCS*2)];

int get(int state, int index) {
    return (state >> (index * 2)) & 3;
}
int set(int state, int index, int value) {
    return (state & ~(3 << (index * 2))) | (value << (index * 2));
}

int sgn(int x) { if(x < 0) return -1; if(x > 0) return 1; return 0; }

int incr(int x) { if(x < 0) return x-1; return x+1; }

int bidir(int discs, int begin, int end) {
    if(begin == end) return 0;
    queue<int> q;
    memset(c, 0, sizeof(c));
    q.push(begin); c[begin] = 1;
    q.push(end); c[end] = -1;
    while(!q.empty()) {
        int here = q.front();
        q.pop();
        
        int top[4] = { -1, -1, -1, -1 };
        for(int i = discs-1; i >= 0; --i)
            top[get(here, i)] = i;
        
        for(int i = 0; i < 4; ++i)
            if(top[i] != -1)
                for(int j = 0; j < 4; j++)
                    if(i != j && (top[j] == -1 || top[j] > top[i])) {
                        int there = set(here, top[i], j);
                        if(c[there] == 0) {
                            c[there] = incr(c[here]);
                            q.push(there);
                        }
                        else if(sgn(c[there]) != sgn(c[here]))
                            return abs(c[there]) + abs(c[here]) - 1;
                    }
    }
    return -1;
}


int main(int argc, char* argv[]) {
    
    freopen("/Users/JUNGJISU/Desktop/C++/HANOI4/HANOI4/in.txt", "r", stdin);
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
        int begin = 0;
        int discs;
        cin >> discs;
        for(int i = 0; i < 4; i++) {
            int n;
            cin >> n;
            for(int j = 0; j < n; j++) {
                int d;
                cin >> d;
                begin = set(begin, d-1, i);
                //cout << "i = " << i << " : " << begin << endl;
            }
        }
        
        int end = 0;
        for(int i = 0; i < discs; i++)
            end = set(end, i, 3);
        
        cout << bidir(discs, begin, end) << endl;
    }
    
    return 0;
}


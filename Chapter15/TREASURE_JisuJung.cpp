//
//  main.cpp
//  treasure
//
//  Created by smartgrid_aict on 2017. 9. 9..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

//
//  main.cpp
//  treasure
//
//  Created by smartgrid_aict on 2017. 9. 9..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// 2차원 벡터를 표현하는 클래스
const double PI = 2.0 * acos(0.0);
const double EPSILON = 1e-9;


struct vector2 {
    double x, y;
    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    
    bool operator == (const vector2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator < (const vector2& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
    vector2 operator + (const vector2& rhs) const {
        return vector2(x + rhs.x , y + rhs.y);
    }
    vector2 operator - (const vector2& rhs) const {
        return vector2(x - rhs.x , y - rhs.y);
    }
    vector2 operator * (double rhs) const {
        return vector2(x * rhs , y * rhs);
    }
    
    // 벡터 길이 반환
    double norm() const {
        return hypot(x, y);
    }
    
    // 단위벡터
    vector2 normalize() const {
        return vector2(x / norm(), y / norm());
    }
    
    // 극각도
    double polar() const { return fmod(atan2(y,x) + 2*PI, 2*PI); }
    
    double dot(const vector2& rhs) const { return x*rhs.x + y*rhs.y; }
    
    double cross(const vector2& rhs) const { return x*rhs.y - rhs.x*y; }
    
    // 사영
    // rhs.dot(*this)*(1/rhs.norm()) 를 벡터로 계산
    // 단위벡터에 단위벡터랑 내적한 값을 실수배
    vector2 project(const vector2& rhs) const {
        vector2 r =  rhs.normalize();
        return r * r.dot(*this);
        //return r * r.dot(*this);
    }
    
};


typedef vector<vector2> poly;
int n;

double ccw(vector2 a, vector2 b) {
    return a.cross(b);
}

// 점 p를 기준으로 b가 a의 반시계 방향이면 양수, 시계 방향이면 음수
double ccw(vector2 p, vector2 a, vector2 b) {
    return ccw(a-p, b-p);
}

double lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
    double det = (b-a).cross(d-c);
    if(fabs(det) < EPSILON) return false;
    x = a + (b-a) * ((c-a).cross(d-c) / det );
    return true;
}


// 직선의 반평면에 포함되는 다각형 벡터를 구한다.
poly cutpoly(poly& p, vector2& a, vector2& b) {
   
    // 1) 각 점이 반평면 내에 있는지 여부 확인
    // 길이를 새로 계산 하는 이유는?
    int nn = (int)p.size();
    
    vector<bool> inside(nn);
    for(int i = 0; i < nn; i++) {
        inside[i] = ccw(a,b,p[i]) >= 0;
    }
    
    poly ret;
    // 2) 반평면에 속하는 점은 결과에 포함
    for(int i = 0 ; i < nn ; i++) {
        if(inside[i])
            ret.push_back(p[i]);
        
        // 3) 직선ab가 변pi,pj를 관통하면 교차점은 결과에 포함
        int j = (i+1)%nn;
        // 직선이 변을 관통하면
        if(inside[i] != inside[j]) {
            vector2 point;
            lineIntersection(p[i], p[j], a, b, point);
            ret.push_back(point);
        }
    }
    
    return ret;
}

// 주어진 사각형으로 다각형을 자른다.
poly intersection(poly& p, double x1, double y1, double x2, double y2) {
    
    // 사각형의 꼭지점을 시계방향으로
    vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
    poly ret = cutpoly(p, a, b);
    //cout << "a" << ret.size() << endl;
    ret = cutpoly(ret, b, c);
    //cout << "b" << ret.size() << endl;
    ret = cutpoly(ret, c, d);
    //cout << "c" << ret.size() << endl;
    ret = cutpoly(ret, d, a);
    //cout << "d" << ret.size() << endl;
    
    return ret;
}

double area(poly& p) {
    double ret = 0;
    for(int i = 0 ; i < p.size() ; i++) {
        int j = (i+1) % p.size();
        ret += p[i].cross(p[j]);
    }
    return fabs(ret) / 2;
}


int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/treasure/treasure/input.txt", "r", stdin);
    
    int T;
    cin >> T;
    while(T--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2 >> n;
        
        // poly polygon(101) -> 전역으로 선언하면 안된다. 
        poly polygon(n);
        for(int i = 0 ; i < n ; i++) {
            cin >> polygon[i].x >> polygon[i].y;
        }
        
//        for(int j = 0 ; j < n ; j++) {
//            cout << polygon[j].x << " " << polygon[j].y << endl;
//        }
        
        poly result = intersection(polygon, x1, y1, x2, y2);
        
        printf("%.10lf\n", area(result));
    }
    return 0;
}

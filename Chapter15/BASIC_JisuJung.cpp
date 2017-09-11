//
//  main.cpp
//  15. 계산기하
//
//  Created by smartgrid_aict on 2017. 9. 8..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

// 2차원 벡터를 표현하는 클래스
const double PI = 2.0 * acos(0.0);

struct vector2 {
    double x, y;
    explicit vector2(double x_, double y_) : x(x_), y(y_){}
    
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

/* 
 외적의 역할2 - 방향 판별
 두 벡터 사이의 각이 반시계 방향으로 얼마나 회전해야 하는가를 나타내기 때문
 ccw 가 양수이면 a기준 b가 반시계 방향에, 음수이면 a기준 b가 시계 방향에 존재
 */
double ccw(vector2 a, vector2 b) {
    return a.cross(b);
}

// 점 p를 기준으로 b가 a의 반시계 방향이면 양수, 시계 방향이면 음수
double ccw(vector2 p, vector2 a, vector2 b) {
    return ccw(a-p, b-p);
}

const double EPSILON = 1e-9;

double lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
    double det = (b-a).cross(d-c);
    if(fabs(det) < EPSILON) return false;
    // a : 한 점, b-a : 방향, ((c-a).cross(d-c) / det ) : p에 대해 푼 연립방정식 값
    x = a + (b-a) * ((c-a).cross(d-c) / det );
    return true;
}

// 두 선분이 평행할 때, 한 점에서 겹치는가?
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
    if(b<a) swap(a,b);
    if(d<c) swap(c,d);
    
    // ccw로 왜 한직선 위에 있는것이 판단 가능한가?
    if(ccw(a,b,c) != 0 || b<c || d<a) return false;
    
    // 더 오른쪽에 있는 선분의 시작점에서 겹침
    if(a<c) p = c; else p = a;
    return true;
}

// a,b,p 가 일직선상에 있다고 가정했을 때, ab를 대각선으로 하는 사각형 안에 들어오는지 확인한다.
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b) {
    if(b<a) swap(a, b);
    return p == a || p == b || (a<p && p<b);
}

bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
    // 평행인 경우 예외 처리
    if(!lineIntersection(a, b, c, d, p))
        return parallelSegments(a, b, c, d, p);
    
    return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
}

// 인자가 3개인 ccw, 즉 기준이 있는 ccw에서 0이 반환되면 한 직선 위에 있음을 뜻함
// 교차 여부만 확인
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
    double ab = ccw(a,b,c) * ccw(a,b,d);
    double cd = ccw(c,d,a) * ccw(c,d,b);
    if(ab == 0 && cd == 0) {
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab <= 0 && cd <= 0;
}

vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
    return a + (p-a).project(b-a);
}

double pointToLine(vector2 p, vector2 a, vector2 b) {
    return (p - perpendicularFoot(p, a, b)).norm();
}

int main(int argc, const char * argv[]) {
    const double PI = 2.0 * acos(0.0);
    
    cout << acos(0.0) << endl;
    cout << PI << endl;
    
    return 0;
}

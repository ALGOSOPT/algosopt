// 오답
// Q1. 선분과 사각형 한 변의 끝점이 만날 경우와 평행할 경우를 못나누겠음.
// Q2. 꼭지점에서 겹칠 경우는 없나..?
#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double PI = 2.0 * acos(0.0);
const double EPSILON = 0.001;

struct vector2 {
    int x, y;

    explicit vector2(int x_ = 0, int y_ = 0) : x(x_), y(y_){

    }

    bool operator == (const vector2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    // x 좌표를 비교하고 y 좌표를 비교한다
    bool operator < (const vector2& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }

    // x 좌표끼리 y 좌표끼리 더한 후 vector2를 반환한다
    vector2 operator + (const vector2& rhs) const {
        return vector2(x + rhs.x, y + rhs.y);
    }

    // x좌표끼리 y 좌표끼리 뺀 후 vector2를 반환한다
    vector2 operator - (const vector2& rhs) const {
        return vector2(x - rhs.x, y - rhs.y);
    }

    // x좌표와 y좌표에 각각 rhs배 만큼 한 vector2를 반환한다
    vector2 operator * (int rhs) const {
        return vector2(x * rhs, y * rhs);
    }

    // hypot : square root (x*x + y*y)
    // 원점(0, 0)에서부터 (x, y)까지의 거리를 반환한다
    double norm() const {
        return hypot(x, y);
    }

    // 원점과 (x, y)를 포함하는 직선의 단위벡터를 반환한다
    vector2 normalize() const {
        return vector2(x / norm(), y / norm());
    }

    // fmod : double형 나눗셈의 나머지
    // atan2 : vector가 x축과 이루는 각을 반환한다 : atan2(y, x) : return -PI ~ PI
    // 반시계 방향을 유지하기 위해 2*PI를 더해준다
    // x축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도 : return 0 ~ 1
    double polar() const {
        return fmod(atan2(y, x) + 2*PI, 2*PI);
    }

    // vector 내적
    // 직각 확인(내적 값 0), 벡터의 사영
    double dot(const vector2& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    // vector 외적
    // = |a|*|b|sin쎄타
    // 면적 계산하기(평행사변형의 넓이 / 2 = 삼각형의 넓이),
    // 두 벡터의 방향 판별 : axb 값이 양수라면 b는 a에서 반시계방향으로 180도 안에 있다
    double cross(const vector2& rhs) const {
        return x * rhs.y - rhs.x * y;
    }

    // 이 벡터를 rhs에 사영한 결과
    // this 벡터를 rhs 벡터에 끼워맞춘다
    // 사영 벡터 크기 = |a|cos쎄타 = (a*b) / |b| = a*b/|b| = a*b단위벡터
    // 사영 벡터 방향 = b단위벡터
    vector2 project(const vector2& rhs) const {
        // rhs 벡터의 단위벡터
        vector2 r = rhs.normalize();
        // rhs 단위벡터와 this 벡터를 내적하고 rhs 단위벡터를 곱해준다(방향).
        return r * r.dot(*this);
    }
};

double ccw(vector2 a, vector2 b) {
  return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
  return ccw(a-p, b-p);
}

bool segmentIntersects(vector2 a, vector2 b,
                      vector2 c, vector2 d) {
    // ab == 0 : ccw(a, b, c)가 0이라면 점 a, b, c는 한 직선에 있다 따라서 ab == 0은 4개의 점 중 3개 점이 한 직선상에 있다는 걸 의미한다
    // ab > 0 : 점 c와 d가 직선 ab를 기준으로 같은 공간에 있는 것을 의미한다
    // ab < 0 : 점 c와 d가 직선 ab를 기준으로 다른 공간에 있는 것을 의미한다
    double ab = ccw(a, b, c) * ccw(a, b, d);
    double cd = ccw(c, d, a) * ccw(c, d, b);

    // 두 선분이 한 직선에 있거나 끝점이 겹칠 경우
    if(ab == 0 && cd == 0) {
        if(b < a) {
            swap(a, b);
        }
        if(d < c) {
            swap(c, d);
        }
        // 두 선분이 평행할 경우, 선분의 초점 c 또는 a가 다른 선분의 종점 b 또는 d보다 멀리 있으면 두 선분은 평행하지만 교차점은 없다
        // 두 선분이 평행하지 않을 경우, ab와 cd가 모두 0이 되기 위해서는 ab의 관점에서 점 c 또는 d가 같은 직선에 있고 cd의 관점에서도 a 또는 b가 같은 직선에 있어야 하는데
        // 이를 만족하면서 아래 조건식을 만족하는 경우는 끝점이 겹치는 경우밖에 없다
        return !(b < c || d < a);
    }
    // ab와 cd가 모두 음수라면 두 선분은 교차한다
    // ab 또는 cd 둘 중 하나가 0인 경우는 두 선분 중 하나의 끝점이 다른 선분에 닿아있을 경우이다 따라서 이 경우에도 교차한다고 볼 수 있다
    return ab <= 0 && cd <= 0;
}

int main()
{
  int testCase;
  scanf("%d", &testCase);
  for(int tc=1; tc<=testCase; tc++) {
    int xmin,ymin,xmax,ymax;
    scanf("%d %d %d %d", &xmin, &ymin, &xmax, &ymax);
    int x1,y1,x2,y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    vector2 a = vector2(x1,y1);
    vector2 b = vector2(x2,y2);

    vector<pair<vector2,vector2> > rect;
    rect.push_back(make_pair(vector2(xmin,ymin),vector2(xmax,ymin)));
    rect.push_back(make_pair(vector2(xmax,ymin),vector2(xmax,ymax)));
    rect.push_back(make_pair(vector2(xmax,ymax),vector2(xmin,ymax)));
    rect.push_back(make_pair(vector2(xmin,ymax),vector2(xmin,ymin)));

    int result = 0;
    for(int i=0; i<rect.size(); i++) {
      result += segmentIntersects(a, b, rect[i].first, rect[i].second);
    }
    if(result > 4) result = 4;
    printf("%d\n", result);
  }
  return 0;
}

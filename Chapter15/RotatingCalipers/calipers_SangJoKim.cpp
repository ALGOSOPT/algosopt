#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;


const double PI = 2.0 * acos(0.0);
const double EPSILON = 1e-7;
const double INFTY = 1e200;

struct vector2 {

	double x, y;

	vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

	//두 벡터의 비교
	bool operator == (const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}

	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, rhs.y + y);
	}
	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}
	vector2 operator * (double rhs) const {
		return vector2(x * rhs, y * rhs);
	}

	double norm() const {
		return hypot(x, y);
	}

	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}

	double polar() const {
		return fmod(atan2(y, x) + 2 * PI, 2 * PI);
	}

	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	double cross(const vector2& rhs) const {
		return x * rhs.y - y * rhs.x;
	}

	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}

};


double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}
double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}


//(a, b)를 포함하는 선과 (c, d)를 포함하는 선의 교점을 x에 반환한다.
//두 선이 평행이면(겹치는 경우를 포함) 거짓을, 아니면 참을 반환한다.
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {

	double det = (b - a).cross(d - c);
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}

//(a, b)와 (c, d)가 평행한 두 선분일 때 이들이 한 점에서 겹치는지 확인한다.
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	//한 직선 위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다.
	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	//두 선분은 확실히 겹친다. 교차점을 하나 찾자.
	if (a < c) p = c; else p = a;
	return true;
}


//p가 (a, b)를 감싸면서 각 변이 x, y축에 평행한 최소 사각형 내부에 있는지 확인한다.
//a, b ,p는 일직선 상에 있다고 가정한다.
bool inBoudingRectangle(vector2 p, vector2 a, vector2 b) {
	if (b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}


//(a, b) 선분과 (c, d)선분의 교점을 p에 반환한다.
//교점이 여러 개일 경우 아무 점이나 반환한다.
//두 선분이 교차하지 않을 경우 false를 반환한다.
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {

	//두 직선이 평행인 경우를 우선 예외로 처리한다.
	if (!lineIntersection(a, b, c, d, p))
		return parallelSegments(a, b, c, d, p);

	return inBoudingRectangle(p, a, b) && inBoudingRectangle(p, c, d);
}


//두 선분이 서로 접촉하는지 여부를 반환한다.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

//점 p에서 (a, b) 직선에 내린 수선의 발을 구한다.
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
	return a + (p - a).project(b - a);
}

//점 p와 (a, b) 직선 사이의 거리를 구한다.
double pointToLine(vector2 p, vector2 a, vector2 b) {
	return (p - perpendicularFoot(p, a, b)).norm();
}

double area(const vector<vector2>&p) {
	double ret = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		ret += p[i].x * p[j].y - p[j].x * p[i].y;
	}
	return fabs(ret) / 2.0;
}

bool isInside(vector2 q, const vector<vector2>& p) {
	int crosses = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();

		if ((p[i].y > q.y) != (p[j].y > q.y)) {

			double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}

typedef vector<vector2> polygon;

//시계 반대 방향으로 주어진 볼록 다각형에서 가장 먼 꼭지점 쌍 사이의 거리를 반환한다
double diameter(const polygon& p) {

	int n = p.size();

	//우선 가장 왼쪽에 있는 점과 오른쪽에 있는 점을 찾는다.
	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();

	//p[left]와 p[right]에 각각 수직선을 붙인다. 두 수직선은 서로 정반대 방향을 가리키므로,
	//A의 방향만을 표현하면 된다.
	vector2 calipersA(0, 1);
	double ret = (p[right] - p[left]).norm();

	//toNext[i] = p[i]에서 다음 점까지의 방향을 나타내는 단위 벡터
	vector<vector2> toNext(n);
	for (int i = 0; i < n; i++)
		toNext[i] = (p[(i + 1) % n] - p[i]).normalize();

	//a와 b는 각각 두 선분이 어디에 붙은 채로 회전하고 있는지를 나타낸다.
	int a = left, b = right;

	//반 바퀴 돌아서 두 선분이 서로 위치를 바꿀 때까지 계속한다.
	while (a != right || b != left){
		//a에서 다음 점까지의 각도와 b에서 다음 점까지의 각도 중 어느 쪽이 작은지 확인
		double cosThetaA = calipersA.dot(toNext[a]);
		double cosThetaB = -calipersA.dot(toNext[b]);
		if (cosThetaA > cosThetaB) { // thetaA < thetaB
			calipersA = toNext[a];
			a = (a + 1) % n;
		}
		else {
			calipersA = -toNext[b];
			b = (b + 1) % n;
		}

		ret = max(ret, (p[a] - p[b]).norm());

	}
	return ret;
}
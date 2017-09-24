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

	//µÎ º¤ÅÍÀÇ ºñ±³
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

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {

	double det = (b - a).cross(d - c);
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}

bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	if (a < c) p = c; else p = a;
	return true;
}

bool inBoudingRectangle(vector2 p, vector2 a, vector2 b) {
	if (b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}

bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {

	if (!lineIntersection(a, b, c, d, p))
		return parallelSegments(a, b, c, d, p);

	return inBoudingRectangle(p, a, b) && inBoudingRectangle(p, c, d);
}


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

vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
	return a + (p - a).project(b - a);
}

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


int N;

typedef vector<vector2> polygon;

pair<vector2, vector2> diameter(const polygon& p) {

	int  n = p.size();
	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();


	vector2 calipersA(0, 1);

	double ret = (p[right] - p[left]).norm();

	vector<vector2> toNext(n);

	for (int i = 0; i < n; i++)
		toNext[i] = (p[(i + 1) % n] - p[i]).normalize();

	int a = left, b = right;
	pair<vector2, vector2> result(make_pair(p[a],p[b]));
	while (a != right || b != left) {

		double cosThetaA = calipersA.dot(toNext[a]);
		double cosThetaB = -calipersA.dot(toNext[b]);

		if (cosThetaA > cosThetaB) {
			calipersA = toNext[a];
			a = (a + 1) % n;
		}
		else {
			calipersA = toNext[b] * -1;
			b = (b + 1) % n;
		}

		if (ret < (p[a] - p[b]).norm()) {
			ret = (p[a] - p[b]).norm();
			result.first = p[a];
			result.second = p[b];

		}
	}
	return result;
}

polygon giftWrap(const vector<vector2>& points){

	polygon hull;

	vector2 pivot = *min_element(points.begin(), points.end());

	int  n = points.size();

	hull.push_back(pivot);

	while (true) {

		vector2 ph = hull.back(), next = points[0];

		for (int i = 1; i < n; i++) {

			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();

			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}

		if (next == pivot) break;
		hull.push_back(next);
	}
	return hull;
}

int main() {


	freopen("input.txt", "r", stdin);

	int TC; cin >> TC;

	while (TC--)
	{
		cin >> N;

		polygon poly;

		for (int i = 0; i < N; i++) {
			int tempX, tempY;
			cin >> tempX >> tempY;

			poly.push_back(vector2(tempX, tempY));
		}

		poly = giftWrap(poly);
		pair<vector2, vector2> ret = diameter(poly);

		cout << ret.first.x << " " << ret.first.y << " " << ret.second.x << " " << ret.second.y << endl;
	}


	return 0;
}
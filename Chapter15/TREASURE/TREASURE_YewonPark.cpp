#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

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
		return vector2(x + rhs.x, y + rhs.y);
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

	double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }

	double dot(const vector2& rhs) const { return x*rhs.x + y*rhs.y; }

	double cross(const vector2& rhs) const { return x*rhs.y - rhs.x*y; }

	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}

};


typedef vector<vector2> poly;
int n;

double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}

double lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}

poly cutpoly(poly& p, vector2& a, vector2& b) {

	int nn = (int)p.size();

	vector<bool> inside(nn);
	for (int i = 0; i < nn; i++) {
		inside[i] = ccw(a, b, p[i]) >= 0;
	}

	poly ret;
	for (int i = 0; i < nn; i++) {
		if (inside[i])
			ret.push_back(p[i]);

		int j = (i + 1) % nn;
		if (inside[i] != inside[j]) {
			vector2 point;
			lineIntersection(p[i], p[j], a, b, point);
			ret.push_back(point);
		}
	}

	return ret;
}

poly intersection(poly& p, double x1, double y1, double x2, double y2) {

	vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
	poly ret = cutpoly(p, a, b);
	ret = cutpoly(ret, b, c);
	ret = cutpoly(ret, c, d);
	ret = cutpoly(ret, d, a);

	return ret;
}

double area(poly& p) {
	double ret = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		ret += p[i].cross(p[j]);
	}
	return fabs(ret) / 2;
}


int main() {

	int T;
	cin >> T;
	while (T--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2 >> n;

		poly polygon(n);
		for (int i = 0; i < n; i++) {
			cin >> polygon[i].x >> polygon[i].y;
		}

		poly result = intersection(polygon, x1, y1, x2, y2);

		printf("%.10lf\n", area(result));
	}
	return 0;
}
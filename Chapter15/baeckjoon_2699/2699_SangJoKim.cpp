#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;


int N;



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
		return y == rhs.y ? x < rhs.x : y > rhs.y;
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


//(a, b)¸¦ Æ÷ÇÔÇÏ´Â ¼±°ú (c, d)¸¦ Æ÷ÇÔÇÏ´Â ¼±ÀÇ ±³Á¡À» x¿¡ ¹ÝÈ¯ÇÑ´Ù.
//µÎ ¼±ÀÌ ÆòÇàÀÌ¸é(°ãÄ¡´Â °æ¿ì¸¦ Æ÷ÇÔ) °ÅÁþÀ», ¾Æ´Ï¸é ÂüÀ» ¹ÝÈ¯ÇÑ´Ù.
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {

	double det = (b - a).cross(d - c);
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}

//(a, b)¿Í (c, d)°¡ ÆòÇàÇÑ µÎ ¼±ºÐÀÏ ¶§ ÀÌµéÀÌ ÇÑ Á¡¿¡¼­ °ãÄ¡´ÂÁö È®ÀÎÇÑ´Ù.
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	//ÇÑ Á÷¼± À§¿¡ ¾ø°Å³ª µÎ ¼±ºÐÀÌ °ãÄ¡Áö ¾Ê´Â °æ¿ì¸¦ ¿ì¼± °É·¯³½´Ù.
	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	//µÎ ¼±ºÐÀº È®½ÇÈ÷ °ãÄ£´Ù. ±³Â÷Á¡À» ÇÏ³ª Ã£ÀÚ.
	if (a < c) p = c; else p = a;
	return true;
}


//p°¡ (a, b)¸¦ °¨½Î¸é¼­ °¢ º¯ÀÌ x, yÃà¿¡ ÆòÇàÇÑ ÃÖ¼Ò »ç°¢Çü ³»ºÎ¿¡ ÀÖ´ÂÁö È®ÀÎÇÑ´Ù.
//a, b ,p´Â ÀÏÁ÷¼± »ó¿¡ ÀÖ´Ù°í °¡Á¤ÇÑ´Ù.
bool inBoudingRectangle(vector2 p, vector2 a, vector2 b) {
	if (b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}


//(a, b) ¼±ºÐ°ú (c, d)¼±ºÐÀÇ ±³Á¡À» p¿¡ ¹ÝÈ¯ÇÑ´Ù.
//±³Á¡ÀÌ ¿©·¯ °³ÀÏ °æ¿ì ¾Æ¹« Á¡ÀÌ³ª ¹ÝÈ¯ÇÑ´Ù.
//µÎ ¼±ºÐÀÌ ±³Â÷ÇÏÁö ¾ÊÀ» °æ¿ì false¸¦ ¹ÝÈ¯ÇÑ´Ù.
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {

	//µÎ Á÷¼±ÀÌ ÆòÇàÀÎ °æ¿ì¸¦ ¿ì¼± ¿¹¿Ü·Î Ã³¸®ÇÑ´Ù.
	if (!lineIntersection(a, b, c, d, p))
		return parallelSegments(a, b, c, d, p);

	return inBoudingRectangle(p, a, b) && inBoudingRectangle(p, c, d);
}


//µÎ ¼±ºÐÀÌ ¼­·Î Á¢ÃËÇÏ´ÂÁö ¿©ºÎ¸¦ ¹ÝÈ¯ÇÑ´Ù.
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

//Á¡ p¿¡¼­ (a, b) Á÷¼±¿¡ ³»¸° ¼ö¼±ÀÇ ¹ßÀ» ±¸ÇÑ´Ù.
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
	return a + (p - a).project(b - a);
}

//Á¡ p¿Í (a, b) Á÷¼± »çÀÌÀÇ °Å¸®¸¦ ±¸ÇÑ´Ù.
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

polygon giftWrap(const vector<vector2>& points) {

	int n = points.size();

	polygon hull;

	vector2 pivot = *min_element(points.begin(), points.end());

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

		vector<vector2> points;
		for (int i = 0; i < N; i++) {
			int tempX, tempY;
			cin >> tempX >> tempY;
			points.push_back(vector2(tempX, tempY));
		}

		polygon convexHull = giftWrap(points);

		cout << convexHull.size() << endl;
		for (int i = 0; i < convexHull.size(); i++) {

			cout << convexHull[i].x << " " << convexHull[i].y << endl;

		}
	}


	return 0;
}
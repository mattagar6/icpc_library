const double EPS = 1e-9;
const double PI = acos(-1);

struct point_i { long long x, y;
	point_i() { x = y = 0; }
	point_i(long long _x, long long _y) : x(_x), y(_y) {} };
	
struct point { double x, y;
	point() { x = y = 0; }
	point(double _x, double _y) : x(_x), y(_y) {} 
	// use EPS = 1e-9 when comparing equality of floating points
	bool operator == (point other) const {
		return fabs(x - other.x) < EPS && fabs(y - other.y) < EPS; } };

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y); }

double DEG_to_RAD(double x) {
	return x * PI / 180.0; }

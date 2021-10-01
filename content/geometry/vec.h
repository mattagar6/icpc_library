#include "point.h"
#include "line.h"

struct vec { double x, y;
	vec() { x = y = 0; }
	vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {	// a -> b
	return vec(b.x - a.x, b.y - a.y); }

vec scale(vec v, double a) {
	return vec(v.x * a, v.y * a); }

vec rotate(vec v, double theta) { // radians, counter-clockwise!
	return vec(v.x * cos(theta) - v.y * sin(theta), v.x * sin(theta) + v.y * cos(theta)); }
	
point translate(point p, vec v) {	// translate p according to v
	return point(p.x + v.x, p.y + v.y); }

double dot(vec a, vec b) { return a.x * b.x + a.y * b.y; }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in c
double distToLine(point p, point a, point b, point& c) {
	// formula: c = a + u * ab
	vec ap = toVec(a, p), ab = toVec(a, b);
	double u = dot(ap, ab) / norm_sq(ab);
	c = translate(a, scale(ab, u));
	return dist(p, c); }
	
// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in c
double distToLineSegment(point p, point a, point b, point& c) {
	if(a == b) { c = a; return dist(p, a); }
	vec ap = toVec(a, p), ab = toVec(a, b);
	double u = dot(ap, ab) / norm_sq(ab);
	if(u < 0.0) { c = point(a.x, a.y);	// closer to a 
		return dist(p, a); }
	if(u > 1.0) { c = point(b.x, b.y);	// closer to b
		return dist(p, b); }
	return distToLine(p, a, b, c); }

double angle(point a, point o, point b) { 	// returns angle aob in rad
	vec oa = toVec(o, a), ob = toVec(o, b);
	return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

// positive -> a turns counter-clockwise to b
// negative -> a turns clockwise to b	
double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, change '> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
	return cross(toVec(p, q), toVec(p, r)) > 0; }

// returns true if r is on the same line as the line pq
bool collinear(point p, point q, point r) {
	return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }

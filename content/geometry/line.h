#include "point.h"

struct line { double a, b, c; }; // ax + by + c == 0
// IMPORTANT: fix b = 1, unless vertical!!!

void pointsToLine(point p1, point p2, line& l) {
	if (fabs(p1.x - p2.x) < EPS) { // vertical
		l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;
	} else {
		l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
		l.b = 1.0;
		l.c = -(double)(l.a * p1.x) - p1.y;
}   }

bool areParallel(line l1, line l2) {	// check coefficients a and b
	return fabs(l1.a - l2.a) < EPS && fabs(l1.b - l2.b) < EPS; }
	
bool areSame(line l1, line l2) {	// also check coefficient c
	return areParallel(l1, l2) && fabs(l1.c - l2.c) < EPS; }

// returns true (+ intersection point) if the two lines intersect
bool areIntersect(line l1, line l2, point& p) {
	if(areParallel(l1, l2)) return false; // no intersection
	// solve system of 2 linear equations with 2 unknowns
	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	// special case: test for vertical line to avoid division by zero
	if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
	else                  p.y = -(l2.a * p.x + l2.c);
	return true; }
	

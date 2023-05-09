#include <list>
#include <vector>
#include <algorithm>

#include "point.h"

point evaluate (float t, std::list<point> P) {

	std::list<point> Q = P;

	while (Q.size () > 1) {
		std::list<point> R;

		std::list<point>::iterator p1 = Q.begin ();

		for (std::list<point>::iterator p2 = Q.begin (); p2 != Q.end (); p2++) {
			point p = ((1 - t) * (*p1)) + (t * (*p2++));
			R.push_back (p);

			std::cout << p1->x << std::endl;
			std::cout << p2->x << std::endl;
		}

		Q.clear ();
		Q = R;
	}

	return Q.front ();
}

std::vector<point> EvaluateBezierCurve (std::vector<point>ctrl_points, int num_evaluations) {
	std::list<point> ps (ctrl_points.begin (), ctrl_points.end ());
	std::vector<point> curve;

	float offset = 1 / num_evaluations;

	curve.push_back (ps.front ());
	for (int e = 0; e < num_evaluations - 1; e++) {
		point p = evaluate (offset * (e + 1), ps);
		curve.push_back (p);
	}
	return curve;
}

float* MakeFloatsFromVector (std::vector<point> curve, int& num_verts, int& num_floats, float r, float g, float b) {
	num_verts = curve.size ();

	if (num_verts == 0) {
		return NULL;
	}

	num_floats = num_verts * 6;

	float* vertices = (float*)malloc (num_floats);

	int count = 0;

	for (int i = 0; i < curve.size (); i++) {
		vertices[count] = curve[i].x;
		vertices[count + 1] = curve[i].y;
		vertices[count + 2] = curve[i].z;
		vertices[count + 3] = r;
		vertices[count + 4] = g;
		vertices[count + 5] = b;

		count += 6;
	}

	return vertices;
}

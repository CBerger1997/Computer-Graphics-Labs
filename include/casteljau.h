#include <list>
#include <vector>
#include <algorithm>

#include "point.h"

point evaluate (float t, std::list<point> P)
{
	std::list<point> Q = P;

	while (Q.size () > 1)
	{
		std::list<point> R;

		std::list<point>::iterator p1 = Q.begin ();
		std::list<point>::iterator p2 = Q.begin ();

		p2++;

		for (int i = 0; i < Q.size() - 1; i++)
		{
			point p = ((1 - t) * (*p1)) + (t * (*p2));
			R.push_back (p);

			p1++;
			p2++;
		}

		Q.clear ();
		Q = R;
	}

	return Q.front ();
}

std::vector<point> EvaluateBezierCurve (std::vector<point>ctrl_points, int num_evaluations)
{
	std::list<point> ps (ctrl_points.begin (), ctrl_points.end ());
	std::vector<point> curve;

	float offset = 1 / (float)num_evaluations;

	curve.push_back (ps.front ());

	for (int e = 0; e < num_evaluations - 1; e++)
	{
		point p = evaluate (offset * (e + 1), ps);
		curve.push_back (p);
	}

	curve.push_back (ps.back ());

	return curve;
}

float* MakeFloatsFromVector (std::vector<point> curve, int& num_verts, int& num_floats, float r, float g, float b)
{
	num_verts = curve.size ();

	if (num_verts == 0)
	{
		return NULL;
	}

	num_floats = num_verts * 6;

	float* vertices = (float*)malloc (sizeof (float) * num_floats);

	int count = 0;

	for (int i = 0; i < curve.size (); i++)
	{
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

#include <LEDA/core/d_array.h>
#include <LEDA/core/list.h>
#include <LEDA/core/string.h>
#include <LEDA/graphics/window.h>

using std::cin;
using std::cout;
using std::endl;
using leda::string;
using leda::d_array;
using leda::window;
using leda::point;
using leda::list;
using leda::list_item;

// Function prototypes
void SortPoints(list<point> *points);
int ComparePoints(const point &p1, const point &p2);
void DrawConvexHull(window *W, list<point> *points);
void ClearScreen(window *W, list<point> *points);

int main()
{
	window W(600, 600, "Convex Hull Demo");
	int btnCalcConvexHull = W.button("Calc. Convex Hull");
	int btnClear = W.button("Clear");
	int btnExit = W.button("Exit");
	
	W.display(window::center, window::center);

	list<point> points;

	while (true)
	{
		point p;
		
		// Read mouse and save point in p
		int btnClick = W.read_mouse(p);
		if (btnClick == btnExit)
		{
			W.close();
			break;
		}

		if (btnClick == btnCalcConvexHull) 
		{ 
			SortPoints(&points);
			DrawConvexHull(&W, &points); 
			continue;
		}

		if (btnClick == btnClear) 
		{ 
			ClearScreen(&W, &points); 
			continue;
		}
			
		// Draw point
		W.draw_point(p, leda_blue);

		// Store point in linked list
		points.append(p);
	}

	return 0;
}

void SortPoints(list<point> *points)
{
	(*points).sort(ComparePoints);
}

int ComparePoints(const point &p1, const point &p2)
{
	if (p1.xcoord() < p2.xcoord())
	{
		return -1;
	}
	else if (p1.xcoord() > p2.xcoord())
	{
		return 1;
	} 
	else
	{
		return 0;
	}
}

void DrawConvexHull(window *W, list<point> *points)
{
	// Iterate over list and connect points using segments
	list<point> pts = *points;
	
	if (pts.size() >= 2)
	{
		list_item item = pts.get_item(0);
		point p = pts.contents(item);

		for (int i = 1; i < pts.size(); i++)
		{
			list_item item = pts.get_item(i);
			point q = pts.contents(item);

			// Connect points
			(*W).draw_segment(p, q, leda_red);

			p = q;
		}
	}
}

void ClearScreen(window *W, list<point> *points)
{
	(*points).clear();
	(*W).clear();
}
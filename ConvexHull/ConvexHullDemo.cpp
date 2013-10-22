/*
Convex Hull Demo
Copyright (C) 2013 André Gasser

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <LEDA/core/list.h>
#include <LEDA/graphics/window.h>
#include "ConvexHull.h"

// Function prototypes
void DrawConvexHull(leda::window *W, leda::list<leda::point> *points);
void Reset(leda::window *W, leda::list<leda::point> *points);
void ClearScreen(leda::window *W);
void ClearPoints(leda::list<leda::point> *points);

/// <summary>
/// Entry point for application.
/// </summary>
void main()
{
	leda::window W(600, 600, "Convex Hull Demo");
	int btnCalcConvexHull = W.button("Calc. Convex Hull");
	int btnClear = W.button("Clear");
	int btnExit = W.button("Exit");
	
	W.display(leda::window::center, leda::window::center);

	leda::list<leda::point> points;

	while (true)
	{
		leda::point p;
		
		// Read mouse and save point in p
		int btnClick = W.read_mouse(p);
		
		// Handle buttons
		if (btnClick == btnExit)
		{
			W.close();
			return;
		}

		if (btnClick == btnCalcConvexHull) 
		{ 
			//DumpList(&points);
			leda::list<leda::point> convexHull;
			CalcConvexHull(&convexHull, &points);
			DebugText("Before Draw");
			DumpList(&convexHull);
			
			DrawConvexHull(&W, &convexHull); 
			continue;
		}

		if (btnClick == btnClear) 
		{ 
			Reset(&W, &points); 
			continue;
		}
			
		// Draw point
		W.draw_point(p, leda_blue);

		// Store point in linked list
		points.append(p);
	}
}

/// <summary>
/// Draws the convex hull.
/// </summary>
/// <param name="W">The window handle.</param>
/// <param name="points">The points.</param>
void DrawConvexHull(leda::window *W, leda::list<leda::point> *points)
{
	if (points->size() >= 2)
	{
		leda::list_item item = points->get_item(0);
		leda::point p = points->contents(item);

		for (int i = 1; i < points->size(); i++)
		{
			leda::list_item item = points->get_item(i);
			leda::point q = points->contents(item);

			// Connect points
			W->draw_segment(p, q, leda_red);

			p = q;
		}
	}
}

/// <summary>
/// Resets the application state.
/// </summary>
/// <param name="W">The window handle.</param>
/// <param name="points">The points.</param>
void Reset(leda::window *W, leda::list<leda::point> *points)
{
	ClearScreen(W);
	ClearPoints(points);
}

/// <summary>
/// Clears the drawing surface
/// </summary>
/// <param name="W">The window handle.</param>
void ClearScreen(leda::window *W)
{
	(*W).clear();
}

/// <summary>
/// Clears the list of points.
/// </summary>
/// <param name="points">The points.</param>
void ClearPoints(leda::list<leda::point> *points)
{
	(*points).clear();
}
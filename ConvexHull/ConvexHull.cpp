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

#include "ConvexHull.h"

/// <summary>
/// Calculates the convex hull.
/// </summary>
/// <param name="points">The points.</param>
/// <returns>Returns a list containing the points of the convex hull in clockwise order.</returns>
leda::list<leda::point>* CalcConvexHull(leda::list<leda::point> *points)
{
	leda::list<leda::point> l_upper, l_lower, l;
	leda::list_item item;
	leda::point p1, p2, p_i;
	
	// We must first sort the points along the x-axis
	SortPoints(points);

	// Build upper hull
	item = points->get_item(0);
	p1 = points->contents(item);
	l_upper.append(p1);
	std::wstringstream wss;
	wss << "p1.xcoord() = " << p1.xcoord() << "\n";
	OutputDebugString(wss.str().c_str());
	
	item = points->get_item(1);
	p2 = points->contents(item);
	l_upper.append(p2);
	std::wstringstream wss2;
	wss2 << "p2.xcoord() = " << p2.xcoord() << "\n";
	OutputDebugString(wss2.str().c_str());
	
	for (int i = 2; i < points->size(); i++)
	{
		// Append point p_i to l_upper
		item = points->get_item(i);
		p_i = points->contents(item);
		std::wstringstream wss3;
		wss3 << "p_" << i << ".xcoord() = " << p_i.xcoord() << "\n";
		OutputDebugString(wss3.str().c_str());
				
		l_upper.append(p_i);

		// Check if l_upper has at least three points. Also check if the last three points
		// in the list make a left turn. If both conditions are true, we must remove the middle
		// point of the last three points.
		while (HasMoreThanTwoPoints(&l_upper) && LastThreePointsTurnLeft(&l_upper))
		{
			DeleteMiddleOfLastThree(&l_upper);
		}


	}



	// Build lower hull


	return &l_upper;
}

/// <summary>
/// Sorts a list of points by x-axis value in ascending order.
/// </summary>
/// <param name="points">The points.</param>
void SortPoints(leda::list<leda::point> *points)
{
	points->sort(ComparePoints);

	for (int i = 0; i < points->size(); i++)
	{
		leda::list_item item = points->get_item(i);
		leda::point p = points->contents(item);
		std::wstringstream wss;
		wss << p.xcoord() << "\n";
		OutputDebugString(wss.str().c_str());
	}
}

/// <summary>
/// Compares two point objects by their x-coords.
/// </summary>
/// <param name="p1">The p1.</param>
/// <param name="p2">The p2.</param>
/// <returns>Returns -1 if p1 &lt; p2, 1 if p1 &gt; p2 and 0 if p1 == p2.</returns>
int ComparePoints(const leda::point &p1, const leda::point &p2)
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

/// <summary>
/// Determines whether the list has at least three points.
/// </summary>
/// <param name="points">The points.</param>
/// <returns>Returns <code>true</code> if the list contains at least three points; otherwise <code>false</code>.</returns>
bool HasMoreThanTwoPoints(leda::list<leda::point> *points)
{
	return points->size() > 2;
}

/// <summary>
/// Determines if the last three points in the list represent a left turn. 
/// We check this by calculating the cross product of two vectors.
/// </summary>
/// <param name="points">The points.</param>
/// <returns>Returns <code>true</code> if the last three points in the list represent a left turn; otherwise <code>false</code>.</returns>
bool LastThreePointsTurnLeft(leda::list<leda::point> *points)
{
	leda::list_item item;
	int lastElemIndex = points->size() - 1;
	
	// Get last three points from list
	item = points->get_item(lastElemIndex - 2);
	leda::point p1 = points->contents(item);
	item = points->get_item(lastElemIndex - 1);
	leda::point p2 = points->contents(item);
	item = points->get_item(lastElemIndex);
	leda::point p3 = points->contents(item);

	// Calculate the angle between the two vectors (p1,p2) and (p1,p3).
	// This is required to determine, if they represent a left turn or not.
	// We also report a left turn, if the vectors are collinear.
	bool left_turn = leda::left_turn(p1, p2, p3);
	bool collinear = leda::collinear(p1, p2, p3);
	
	return left_turn || collinear;
}

/// <summary>
/// Determines the last three points in the list and deletes the one in the middle.
/// </summary>
/// <param name="points">The points.</param>
void DeleteMiddleOfLastThree(leda::list<leda::point> *points)
{
	leda::list<leda::point> p = (*points);
	p.erase(p.get_item(p.size() - 2));
}
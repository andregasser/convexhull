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
/// <param name="l_hull">The l_hull.</param>
/// <param name="points">The points.</param>
void CalcConvexHull(leda::list<leda::point> *l_hull, leda::list<leda::point> *points)
{
	leda::list<leda::point> l_upper, l_lower;
	leda::list_item item;
	leda::point p1, p2, p_i;
	
	// We must first sort the points along the x-axis
	SortPoints(points);

	// Build upper hull
	item = points->get_item(0);
	p1 = points->contents(item);
	l_upper.append(p1);
	
	item = points->get_item(1);
	p2 = points->contents(item);
	l_upper.append(p2);
	
	for (int i = 2; i < points->size(); i++)
	{
		// Append point p_i to l_upper
		item = points->get_item(i);
		p_i = points->contents(item);
		l_upper.append(p_i);

		// Check if the last three points in the list make a left turn. 
		// If yes, we must remove the middle point of the last three points.
		while (LastThreePointsTurnLeft(&l_upper))
		{
			DeleteMiddleOfLastThree(&l_upper);
		}
	}

	// Build lower hull
	item = points->get_item(points->size() - 1);
	p1 = points->contents(item);
	l_lower.append(p1);
	
	item = points->get_item(points->size() - 2);
	p2 = points->contents(item);
	l_lower.append(p2);

	for (int i = points->size() - 3; i >= 0; i--)
	{
		// Append point p_i to l_lower
		item = points->get_item(i);
		p_i = points->contents(item);
		l_lower.append(p_i);

		// Check if the last three points in the list make a left turn. 
		// If yes, we must remove the middle point of the last three points.
		while (LastThreePointsTurnLeft(&l_lower))
		{
			DeleteMiddleOfLastThree(&l_lower);
		}
	}

	// Remove first an last point from l_lower to aoi duplication
	// where the points of upper and lower hull meet.
	l_lower.erase(l_lower.get_item(0));
	l_lower.erase(l_lower.get_item(l_lower.size() - 1));

	// Build convex hull by concatenating upper and lower hull.
	l_hull->conc(l_upper);
	l_hull->conc(l_lower);
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
bool HasAtLeastThreePoints(leda::list<leda::point> *points)
{
	return points->size() >= 3;
}

/// <summary>
/// Determines if the last three points in the list represent a left turn. 
/// We check this by calculating the cross product of two vectors.
/// </summary>
/// <param name="points">The points.</param>
/// <returns>Returns <code>true</code> if the last three points in the list represent a left turn; otherwise <code>false</code>.</returns>
bool LastThreePointsTurnLeft(leda::list<leda::point> *points)
{
	if (!HasAtLeastThreePoints(points)) return false;
	
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
	points->erase(points->get_item(points->size() - 2));
}

/// <summary>
/// Dumps the list.
/// </summary>
/// <param name="points">The points.</param>
void DumpList(leda::list<leda::point> *points)
{
	for (int i = 0; i < points->size(); i++)
	{
		std::wstringstream wsstream;
		leda::list_item item = points->get_item(i);
		leda::point p = points->contents(item);
		wsstream << "Point " << i << ": " << "X:" << p.xcoord() << ", Y:" << p.ycoord() << "\n";
		OutputDebugString(wsstream.str().c_str());
	}
}

/// <summary>
/// Debugs the text.
/// </summary>
/// <param name="text">The text.</param>
void DebugText(char* text)
{
	std::wstringstream wsstream;
	wsstream << text << "\n";
	OutputDebugString(wsstream.str().c_str());
}
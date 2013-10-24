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

#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <Windows.h>
#include <sstream>
#include <string>
#include <LEDA/graphics/window.h>
#include <LEDA/core/list.h>

void CalcConvexHull(leda::list<leda::point> *l_hull, leda::list<leda::point> *points);
void SortPoints(leda::list<leda::point> *points);
int ComparePoints(const leda::point &p1, const leda::point &p2);
bool HasMoreThanTwoPoints(leda::list<leda::point> *points);
bool LastThreePointsTurnRight(leda::list<leda::point> *points);
void DeleteMiddleOfLastThree(leda::list<leda::point> *points);
void DumpList(leda::list<leda::point> *points);
void DebugText(char* text);

#endif
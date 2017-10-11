/*
 * The project is about sweep-line algorithm. The description of the algorith can be found behind the link:
 * http://jeffe.cs.illinois.edu/teaching/algorithms/2009/notes/xo-sweepline.pdf
 *
 * The algorithm is very useful in order to solve complex geometric problems in time complexity O(NlogN).
 * The program concernes rectangle intersections. One assumption was undertaken to make the problem easier -
 * - all rectangles are axis alligned - there is no rotation.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include "point.h"
#include "rectangle.h"

using namespace std;

std::ostream& operator<<(std::ostream &out, Point point) {
    out << "(" << point.m_x << ", " << point.m_y << ")";
    return out;
}

std::ostream& operator<<(std::ostream &out, const Rectangle &r) {
    out << "Left bottom point: " << r.m_leftBottom << '\n'
        << "Right top point: " << r.m_rightTop << '\n';
    return out;
}

bool rectCompare(const Rectangle &r1, const Rectangle &r2) {
    return r1.getLeftCoordinate().getX() < r2.getLeftCoordinate().getX();
}

bool cmp(int *i1, int *i2) {
    return *i1 > *i2;
}

int main()
{
    /*
     * Set of rectangles
     */
    Rectangle r1(Point(-10,4), Point(-2,8));
    Rectangle r2(Point(-3,-1), Point(3,5));
    Rectangle r3(Point(1,-3), Point(5,1));
    Rectangle r4(Point(-11,-5), Point(-4,-2));
    Rectangle r5(Point(3,-8), Point(7,-6));
    Rectangle r6(Point(6,-7), Point(9,-5));
    Rectangle r7(Point(5,5), Point(8,8));
    Rectangle r8(Point(8,8), Point(10,10));

    //Sorting set of rectangles in terms of x-axis
    vector<Rectangle> setOfRectangles{r1, r2, r3, r4, r5, r6, r7, r8};
    sort(setOfRectangles.begin(),setOfRectangles.end(), rectCompare);

    for(const auto v : setOfRectangles) {
        cout << v << endl;
    }

    cout << "Found " << Rectangle::findIntersections(setOfRectangles) << " intersections." << endl;

    return 0;
}

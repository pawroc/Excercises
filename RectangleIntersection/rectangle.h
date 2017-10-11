#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include <memory>

#include "point.h"

//It is assumed that rectangles are axis-alligned (there is no rotation yet)
class Rectangle
{
private:
    Point m_leftBottom, m_rightTop;

    /*
     * Tho function comparePointsX is used in order to sort endpoints in rising x-coordinate order
     */
    static bool comparePointsX(const std::pair<Point, long long> &p1, const std::pair<Point, long long> &p2);

    /*
     * The function comparePointsY is used in order to ensure proper order of labels inserted to a BST.
     * It assures that insertion of the new rectangle (label) will be executed always first and after that
     * the ereasing will be executed (if at the same time there were two endpoints (left and right)).
     */
    static bool comparePointsY(std::pair<long long, long long> y1, std::pair<long long, long long> y2);
public:
    Rectangle(Point leftBottom, Point rightTop);
    void print() const;

    /*
     * getters
     */
    void getCoordinates(Point &leftBottom, Point &rightTop) const;
    Point getLeftCoordinate() const;
    Point getRightCoordinate() const;

    /*
     * setters
     */
    void setCoordinates(Point leftBottom, Point rightTop);

    /*
     * searching for intersection
     */
    bool doIntersect(const Rectangle &r) const;

    /*
     * Function counts the number of intersection in given set of rectangles. The function requires
     * the input to be sorted in rising x-coordinate order. If the input is not sorted properly, the
     * output is wrong.
     */
    static int findIntersections(const std::vector<Rectangle> &setOfRectangles);

    friend std::ostream& operator<<(std::ostream &out, const Rectangle &r);
};

#endif // RECTANGLE_H

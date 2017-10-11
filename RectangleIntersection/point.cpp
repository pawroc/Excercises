#include "point.h"
#include <iostream>

using namespace std;

Point::Point(int x, int y) : m_x(x), m_y(y)
{

}

void Point::print() const
{
    cout << "( " << m_x << ", " << m_y << ")";
}

int Point::getX() const
{
    return m_x;
}

int Point::getY() const
{
    return m_y;
}

#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
private:
    //coordinates
    int m_x, m_y;
public:
    Point(int x, int y);
    void print() const;
    int getX() const;
    int getY() const;
    friend std::ostream& operator<<(std::ostream &out, Point point);
};

#endif // POINT_H

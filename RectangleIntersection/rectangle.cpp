#include "rectangle.h"
#include <iostream>
#include <set>
#include <memory>
#include <map>
#include <algorithm>

using namespace std;

bool Rectangle::comparePointsX(const pair<Point, long long> &p1, const pair<Point, long long> &p2)
{
    if(p1.first.getX() == p2.first.getX())
        return abs(p1.second) > abs(p2.second);
    return p1.first.getX() < p2.first.getX();
}

bool Rectangle::comparePointsY(pair<long long, long long> y1, pair<long long, long long> y2)
{
    return y1.first > y2.first;
}


Rectangle::Rectangle(Point leftBottom, Point rightTop) : m_leftBottom(leftBottom), m_rightTop(rightTop)
{

}

void Rectangle::print() const
{
    cout << "Left bottom point: " << m_leftBottom << '\n'
         << "Right top point: " << m_rightTop << '\n';
}

void Rectangle::getCoordinates(Point &leftBottom, Point &rightTop) const
{
    leftBottom = m_leftBottom;
    rightTop = m_rightTop;
}

Point Rectangle::getLeftCoordinate() const
{
    return m_leftBottom;
}

Point Rectangle::getRightCoordinate() const
{
    return m_rightTop;
}

void Rectangle::setCoordinates(Point leftBottom, Point rightTop)
{
    m_leftBottom = leftBottom;
    m_rightTop = rightTop;
}

bool Rectangle::doIntersect(const Rectangle &r) const
{
    if(this->m_leftBottom.getX() > r.m_rightTop.getX() ||
            r.m_leftBottom.getX() > this->m_rightTop.getX() ||
            this->m_leftBottom.getY() > r.m_rightTop.getY() ||
            r.m_leftBottom.getY() > this->m_rightTop.getY())
        return false;
    else
        return true;
}

int Rectangle::findIntersections(const vector<Rectangle> &setOfRectangles)
{
    long long counter = 0;

    //Prepare a map of the points -> mostleft and mostright
    vector<pair<Point, long long> > mapOfPoints;
    pair<Point, long long> label(setOfRectangles[0].getLeftCoordinate(), 1);
    mapOfPoints.push_back(label);
    label = pair<Point, long long>(setOfRectangles[0].getRightCoordinate(), -1);
    mapOfPoints.push_back(label);

    for(long long i = 1; i < setOfRectangles.size(); ++i) {
        label = pair<Point, long long>(setOfRectangles[i].getLeftCoordinate(), i+1);
        mapOfPoints.push_back(label);
        label = pair<Point, long long>(setOfRectangles[i].getRightCoordinate(), -(i+1));
        mapOfPoints.push_back(label);
    }

    for(auto &v : mapOfPoints) {
        cout << v.second << " -> " << v.first << endl;
    }

    //Sort the map of points in terms of x-axis
    bool(*cmpPtr)(const pair<Point, long long>&,const pair<Point, long long>&) = comparePointsX;
    sort(mapOfPoints.begin(), mapOfPoints.end(), cmpPtr);

    cout << "\n\n================\n\n";

    for(auto &v : mapOfPoints) {
        cout << v.second << " -> " << v.first << endl;
    }

    cout << "\n\n================\n\n";

    //Sweep-line algorithm - searching for intersection
    bool(*cmpYAxisPtr)(pair<long long, long long>, pair<long long, long long>) = comparePointsY;
    set<pair<long long, long long>, bool(*)(pair<long long, long long>, pair<long long, long long>)> labelBST(cmpYAxisPtr);
    pair<set<pair<long long, long long> >::iterator,bool> it;
    pair<long long, long long> l(mapOfPoints[0].first.getY(),mapOfPoints[0].second);
    labelBST.insert(l);

    for(size_t i = 1; i < mapOfPoints.size(); ++i) {
        l = pair<long long, long long>(mapOfPoints[i].first.getY(),mapOfPoints[i].second);
        cout << "NOW: " << l.second << endl;
        long long predecessor, successor;
        if(l.second > 0) {
            //Left endpoint
            it = labelBST.insert(l);
            long long x = (*(it.first)).second;

            if(it.first == --labelBST.end()) {
                if(it.first != labelBST.begin()) {
                    //Last and not exclusive label
//                    cout << "THIS IS LAST LABEL!" << endl;
                    cout << "I inserted " << x << endl;
                    predecessor = (*(--it.first)).second;
//                    cout << "Predecessor label: " << predecessor << endl;
                    if(setOfRectangles[l.second - 1].doIntersect(setOfRectangles[predecessor - 1])) {
                        cout << x << " and " << predecessor << " intersect!" << endl;
                        ++counter;
                    }
                }else {
                    //the exclusive label
//                    cout << "ONLY ONE LABEL!"<< endl;
                    cout << "I inserted " << x << endl;
                }
            }else {
                if(it.first != labelBST.begin()) {
                    //neither first nor last label
//                    cout << "THIS IS NOT FIRST AND NOT LAST LABEL!" << endl;
                    cout << "I inserted " << x << endl;
                    predecessor = (*(--it.first)).second;
//                    cout << "Predecessor: " << predecessor << endl;
                    ++it.first;
                    successor = (*(++it.first)).second;
//                    cout << "Successor: " << successor << endl;
                    if(setOfRectangles[l.second - 1].doIntersect(setOfRectangles[predecessor - 1])) {
                        cout << x << " and " << predecessor << " intersect!" << endl;
                        ++counter;
                    }
                    if(setOfRectangles[l.second - 1].doIntersect(setOfRectangles[successor - 1])) {
                        cout << x << " and " << successor << " intersect!" << endl;
                        ++counter;
                    }
                } else {
                    //first label
//                    cout << "THIS IS FIRST LABEL!" << endl;
                    cout << "I inserted " << x << endl;
                    successor = (*(++it.first)).second;
//                    cout << "Successor: " << successor << endl;
                    if(setOfRectangles[l.second - 1].doIntersect(setOfRectangles[successor - 1])) {
                        cout << x << " and " << successor << " intersect!" << endl;
                        ++counter;
                    }
                }
            }
        }else {
            //Right endpoint
            //Restore information about left endpoint of l label in order to find and erease respective label from labelBST
            l.second = abs(l.second);
            l.first = setOfRectangles[l.second - 1].getLeftCoordinate().getY();

            cout << "l.second = " << l.second  << ", Y = " << l.first << endl;

            set<pair<long long, long long> >::iterator iter = labelBST.find(l);
            cout << "I am ereasing " << (*iter).second << endl;
            if(iter != labelBST.end()) {
                //label l found
                iter = labelBST.erase(iter);
                if(labelBST.size() >= 2) {
                    //There are at least 2 labels -> test against intersection
                    predecessor = (*iter).second;
                    successor = (*(++iter)).second;
                    if(setOfRectangles[predecessor - 1].doIntersect(setOfRectangles[successor - 1])) {
                        cout << predecessor << " and " << successor << " intersect!" << endl;
                        ++counter;
                    }
                }
            }
        }
        cout << "\n------\n";
    }

    return counter;
}


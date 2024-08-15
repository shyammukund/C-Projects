#pragma once
#include <ostream>

struct Point{
    double x; 
    double y;

    Point() 
        :x(-1), y(-1) {}

    Point(double a, double b )
        : x(a), y (b)
    {
        // emptyI
    }

    // Overload the < operator
    bool operator<(const Point& other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }


     // Overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const Point& pt) {
        os << "(" << pt.x << ", " << pt.y << ")";
        return os;
    }



};


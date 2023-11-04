#pragma once
#include <iostream>
#include <vector>
#include <complex>


using namespace std;


template<typename T>
struct Point {
    T x;
    T y;
};

template<typename T>
class Polyline {
private:
    vector<Point<T>> points;

public:
    Polyline();
    Polyline(T x, T y);
    Polyline(int numPoints);
    Polyline(vector<Point<T>>& inputPoints);
    ~Polyline();
    Point<T>& operator[](int index);
    Polyline<T> operator+(const Polyline<T>& other);
    Polyline<T> operator+(const Point<T>& point);
    friend Polyline<T> operator+(const Point<T>& point, const Polyline<T>& lines);
    double Length() const;
};

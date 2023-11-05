#pragma once
#include <iostream>
#include <complex>
#include <stdexcept>
#include <random>

using namespace std;

template<typename T>
struct Point {
    T x;
    T y;
    Point(T x, T y) : x(x), y(y) {}
};

template<typename T>
class Polyline {
    Point<T>* points;
    int size;
public:
    Polyline();
    Polyline(const Point<T>& point);
    Polyline(const int& count);
    Polyline(const int& size, const Point<T>& m1, const Point<T>& m2);
    ~Polyline();
    Point<T>& operator[](const int& index);
    Polyline<T>& operator+(const Polyline<T>& other);
    Polyline<T>& operator+(const Point<T>& point);
    Polyline<T>& operator+(const Point<T>& point, const Polyline<T>& lines);
    double length() const;
};



#pragma once
#include <iostream>
#include <complex>
#include <stdexcept>
#include <ctime>


using namespace std;

template<typename T>
struct Point {
    T x;
    T y;
    Point() {
        x = 0;
        y = 0;
    }
    Point(T x, T y) : x(x), y(y) {}
    T get_x() const {
        return x;
    }
    T get_y() const {
        return y;
    }
    void set_x(T newX) {
        x = newX;
    }
    void set_y(T newY) {
        y = newY;
    }
};

template<typename T>
class Polyline {
    Point<T>* points;
    int size;
public:
    int Size() {
        return size;
    }
    Polyline() : points(nullptr), size(0) {};
    Polyline(const int& _size){
        size = _size;
        points = new Point<T>[size];
    }

    Polyline(const Point<T>& other){
        size = other._size();
        points = new Point<T>[size];
        for (int i = 0; i < size; ++i)
        {
            points[i] = other[i];
        }
    }
    
    Polyline(const int& _size, const T& m1, const T& m2) : size(0),points(nullptr) {
        if (_size > 0){
            size = _size;
            points = new Point<T>[size];
            srand(static_cast<unsigned>(time(nullptr)));
            Point<T> temp;
            for (int i = 0; i < size; ++i){
                temp.set_x(static_cast<T>(m1 + rand() / (RAND_MAX / (m2 - m1 + 1.0))));
                temp.set_y(static_cast<T>(m1 + rand() / (RAND_MAX / (m2 - m1 + 1.0))));
                points[i] = temp;
            }
        }
    }

    ~Polyline() {
        delete[] points;
    }
    void add(const Point<T>& point) {
        Point<T>* newElements = new Point<T>[size + 1];
        for (int i = 0; i < size; ++i)
        {
            newElements[i] = points[i];
        }
        newElements[size] = point;
        delete[] points;
        points = newElements;
        size += 1;
    }
    Point<T>& operator[](const int& index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return points[index];
    }
    Polyline<T>& operator+(const Polyline<T>& other) {
        Polyline<T> res(size + other.size);
        for (int i = 0; i < size; ++i) {
            res.points[i].x = points[i].x;
            res.points[i].y = points[i].y;
        }
        for (int i = size; i < size + other.size; ++i) {
            res.points[i].x = other.points[i - size].x;
            res.points[i].y = other.points[i - size].y;
        }
        return res;
    }

    Polyline<T>& operator+(const Point<T>& point) {
        Polyline<T> res(*this);
        res.add(point);
        return res;
    }
 
   /* Polyline<T>& operator+(const Point<T>& point) {
        Polyline<T> res(size + 1);
        for (int i = 0; i < size; ++i) {
            res.points[i + 1].x = points[i].x;
            res.points[i + 1].y = points[i].y;
        }
        res.points[0] = point;
        return res;
    }*/

    double length() const {
        double length = 0;
        for (size_t i = 1; i < size; i++) {
            double dx = static_cast<double>(points[i].x) - static_cast<double>(points[i - 1].x);
            double dy = static_cast<double>(points[i].y) - static_cast<double>(points[i - 1].y);
            length += std::sqrt(dx * dx + dy * dy);
        }
        return length;
    }

    
    
    
    
};
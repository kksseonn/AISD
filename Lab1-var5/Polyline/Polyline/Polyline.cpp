#pragma once
#include <iostream>
#include <complex>
#include <stdexcept>
#include <random>
#define PI 3.14159265358979323846

using namespace std;

template<typename T>
struct Point {
    T x;
    T y;
    Point() : x(0), y(0) {}
    Point(T _x, T _y) : x(_x), y(_y) {}
};

template<typename T>
class Polyline {
    Point<T>* points;
    int size;
public:
    Polyline();
    Polyline(int _size);
    Polyline(const Point<T>& other);
    Polyline(int _size, const T& m1, const T& m2);
    ~Polyline();

    void add(const Point<T>& point);

    Point<T>& operator[](const int& index);
    Polyline<T>& operator+(const Polyline<T>& other);
    Polyline<T>& operator-(const Point<T>& point);
    Polyline<T>& operator+(const Point<T>& point);
    double length() const;
    void createRegularPolygon(int _size, T radius);

    friend ostream& operator<<(ostream& os, const Polyline<T>& polyline) {
        for (int i = 0; i < polyline.size; i++) {
            os << "(" << polyline.points[i].x << ", " << polyline.points[i].y << ") ";
        }
        return os;
    }
};

template<typename T>
Polyline<T>::Polyline() : points(nullptr), size(0) {}

template<typename T>
Polyline<T>::Polyline(int _size) : size(_size) {
    points = new Point<T>[size];
}

template<typename T>
Polyline<T>::Polyline(const Point<T>& other) : size(1) {
    points = new Point<T>[size];
    points[0] = other;
}

template<typename T>
Polyline<T>::Polyline(int _size, const T& m1, const T& m2) : size(_size) {
    points = new Point<T>[size];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> distrib(m1, m2);
    for (int i = 0; i < size; i++) {
        T randomX = distrib(gen);
        T randomY = distrib(gen);
        points[i] = Point<T>(randomX, randomY);
    }
}

template<typename T>
Polyline<T>::~Polyline() {
    delete[] points;
}

template<typename T>
void Polyline<T>::add(const Point<T>& point) {
    Point<T>* newElements = new Point<T>[size + 1];
    for (int i = 0; i < size; ++i) {
        newElements[i] = points[i];
    }
    newElements[size] = point;
    delete[] points;
    points = newElements;
    size += 1;
}

template<typename T>
Point<T>& Polyline<T>::operator[](const int& index) {
    return points[index];
}

template<typename T>
Polyline<T>& Polyline<T>::operator+(const Polyline<T>& other) {
    int newSize = size + other.size;
    Point<T>* newPoints = new Point<T>[newSize];
    for (int i = 0; i < size; i++) {
        newPoints[i] = points[i];
    }
    for (int i = 0; i < other.size; i++) {
        newPoints[size + i] = other.points[i];
    }
    delete[] points;
    points = newPoints;
    size = newSize;
    return *this;
}

template<typename T>
Polyline<T>& Polyline<T>::operator-(const Point<T>& point) {
    Point<T>* newPoints = new Point<T>[size + 1];
    newPoints[0] = point;
    for (int i = 0; i < size; i++) {
        newPoints[i + 1] = points[i];
    }
    delete[] points;
    points = newPoints;
    size++;
    return *this;
}

template<typename T>
Polyline<T>& Polyline<T>::operator+(const Point<T>& point) {
    Point<T>* newPoints = new Point<T>[size + 1];
    for (int i = 0; i < size; i++) {
        newPoints[i] = points[i];
    }
    newPoints[size] = point;
    delete[] points;
    points = newPoints;
    size++;
    return *this;
}

template<typename T>
double Polyline<T>::length() const {
    double totalLength = 0.0;
    for (int i = 0; i < size - 1; i++) {
        // –ассто€ние между точками i и i+1
        T dx = points[i + 1].x - points[i].x;
        T dy = points[i + 1].y - points[i].y;
        double segmentLength = std::sqrt(static_cast<double>(dx * dx + dy * dy));
        totalLength += segmentLength;
    }
    return totalLength;
}

template<typename T>
void Polyline<T>::createRegularPolygon(int _size, T radius) {
    if (_size <= 2) {
        throw out_of_range("_size should be greater than 2");
    }
    else {
        delete[] points;
        size = 0;
        points = new Point<T>[_size];
        double angle = 2 * PI / _size;  
        T centerX = static_cast<T>(0);  
        T centerY = static_cast<T>(0);

        for (int i = 0; i < _size; i++) {
           
            T x = centerX + radius * cos(i * angle);
            T y = centerY + radius * sin(i * angle);

            add(Point<T>(x, y));
        }
    }
}

int main() {
    Polyline<int> polyline(4); 
    polyline[0] = Point<int>(0, 0);
    polyline[1] = Point<int>(1, 1);
    polyline[2] = Point<int>(2, 3);
    polyline[3] = Point<int>(4, 5);
    cout << "Polyline: " << polyline << endl;

    polyline.add(Point<int>(6, 7)); 
    cout << "Polyline after adding a point: " << polyline << endl;

    double len = polyline.length(); 
    cout << "Length of the polyline: " << len << endl;
    


    // проверка создани€ правильного многоугольника
    Polyline<int> polygon;
    polygon.createRegularPolygon(4, 2);

    cout << "Coordinates of the regular polygon: " << endl;
    cout << polygon << endl;

    return 0;
}



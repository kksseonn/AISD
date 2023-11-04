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

template <typename T>
Polyline<T>::Polyline() : points(nullptr), size(0) {};

template <typename T>
Polyline<T>::Polyline(const Point<T>& point) : size(1) {
    points = new Point<T>[size];
    points[0] = point;
};

template <typename T>
Polyline<T>::Polyline(const int& count) : size(count){
    if (size < 3) throw std::invalid_argument("Invalid number of points");
    points = new Point<T>[size];
}

template <typename T>
Polyline<T>::Polyline(const int& size, const Point<T>& m1, const Point<T>& m2) : size(size){
    if (size < 3) throw std::invalid_argument("Invalid number of points");
    points = new Point<T>[size];
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<T> disX(m1.x, m2.x);
    uniform_real_distribution<T> disY(m1.y, m2.y);
    for (int i = 0; i < size; ++i) {
        T x = disX(gen);
        T y = disY(gen);
        points[i] = Point<T>(x, y);
    }
}

template<typename T>
Polyline<T>::~Polyline() {
    delete[] points;
}

template<typename T>
Point<T>& Polyline<T>::operator[](const int& index){
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    return points[index];
}

template <typename T>
Polyline<T>& Polyline<T>::operator+(const Polyline<T>& other) {
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

template <typename T>
Polyline<T>& Polyline<T>::operator+(const Point<T>& point) {
    Polyline<T> res(size + 1);
    for (int i = 0; i < size; ++i) {
        res.points[i + 1].x = points[i].x;
        res.points[i + 1].y = points[i].y;
    }
    res.points[0].x = point.x;
    res.points[0].y = point.y;
    return res;
}

template <typename T>
Polyline<T>& Polyline<T>::operator+(const Point<T>& point, const Polyline<T>& lines) {
    Polyline<T> result(lines.size + 1);
    result.points[0] = point;
    for (size_t i = 0; i < lines.size; i++) {
        result.points[i + 1] = lines.points[i];
    }
    return result;
}

template <typename T>
double Polyline<T>::length() const {
    double length = 0;
    for (size_t i = 1; i < size; i++) {
        double dx = static_cast<double>(points[i].x) - static_cast<double>(points[i - 1].x);
        double dy = static_cast<double>(points[i].y) - static_cast<double>(points[i - 1].y);
        length += std::sqrt(dx * dx + dy * dy);
    }
    return length;
}

int main() {
    int size = 5; // Задаем число вершин

    try {
        Polyline<float> polyline(size); // Создаем ломаную в виде правильного N-угольника
        for (int i = 0; i < size; i++) {
            std::cout << "Vertex " << i << ": (" << polyline[i].x << ", " << polyline[i].y << ")" << std::endl;
        }
        std::cout << "Length: " << polyline.length() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid number of points: " << e.what() << std::endl;
    }

    return 0;
}


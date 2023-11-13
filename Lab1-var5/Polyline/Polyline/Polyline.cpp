#pragma once
#include <iostream>
#include <complex>
#include <stdexcept>
#include <cmath>
#include <random>
#define PI 3.14159265358979323846

using namespace std;

template<typename T>
struct Point {
	T x;
	T y;
	Point() : x(0), y(0) {}
	Point(T _x, T _y) : x(_x), y(_y) {}
	Point(complex<T> _x, complex<T> _y) : x(_x), y(_y) {}
	friend ostream& operator<<(ostream& os, const Point<T>& point) {
		os << "(" << point.x << ", " << point.y << ") ";
		return os;
	}
};

template<typename T>
class Polyline {
	Point<T>* points;
	int size;
public:
	Polyline();
	Polyline(int _size);
	Polyline(Polyline<T>& other);
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

	Polyline(const Point<complex<T>>& other);
	Polyline(int _size, const complex<T>& m1, const complex<T>& m2);

	void add(const Point<complex<T>>& point);

	Polyline<T>& operator+(const Polyline<complex<T>>& other);
	Polyline<T>& operator-(const Point<complex<T>>& point);
	Polyline<T>& operator+(const Point<complex<T>>& point);

	void createRegularPolygon(int _size, complex<T> radius);


};


template<typename T>
Polyline<T>::Polyline() : points(nullptr), size(0) {}

template<typename T>
Polyline<T>::Polyline(int _size) : size(_size) {
	points = new Point<T>[size];
}

template<typename T>
Polyline<T>::Polyline(Polyline<T>& other) {
	size = other.size;
	points = new Point<T>[size];
	for (int i = 0; i < size; ++i)
	{
		points[i] = other[i];
	}
}
template<typename T>
Polyline<T>::Polyline(const Point<complex<T>>& other) : size(1) {
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
Polyline<T>::Polyline(int _size, const complex<T>& m1, const complex<T>& m2) : size(_size) {
	points = new Point<T>[size];
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<T> real_distrib(m1.real(), m2.real());
	uniform_real_distribution<T> imag_distrib(m1.imag(), m2.imag());
	for (int i = 0; i < size; i++) {
		T randomX = real_distrib(gen);
		T randomY = imag_distrib(gen);
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
void Polyline<T>::add(const Point<complex<T>>& point) {
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
Polyline<T>& Polyline<T>::operator+(const Polyline<complex<T>>& other) {
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
Polyline<T>& Polyline<T>::operator-(const Point<complex<T>>& point) {
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
Polyline<T>& Polyline<T>::operator+(const Point<complex<T>>& point) {
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
		// Расстояние между точками i и i+1
		T dx = points[i + 1].x - points[i].x;
		T dy = points[i + 1].y - points[i].y;

		double segmentLength;

		if constexpr (is_same<T, complex<float>>::value || is_same<T, complex<double>>::value) {
			segmentLength = abs(points[i + 1].x - points[i].x);
			segmentLength += abs(points[i + 1].y - points[i].y);
		}
		else {
			segmentLength = sqrt(static_cast<double>(dx * dx + dy * dy));
		}

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
template<typename T>
void Polyline<T>::createRegularPolygon(int _size, complex<T> radius) {
	if (_size <= 2) {
		throw out_of_range("_size should be greater than 2");
	}
	else {
		delete[] points;
		size = 0;
		points = new Point<T>[_size];
		double angle = 2 * PI / _size;
		T centerX = static_cast<T>(radius.real());
		T centerY = static_cast<T>(radius.imag());

		for (int i = 0; i < _size; i++) {
			T x = centerX + radius.real() * cos(i * angle);
			T y = centerY + radius.imag() * sin(i * angle);

			add(Point<T>(x, y));
		}
	}
}

int main() {
	// Создание объекта Polyline типа int
	Polyline<int> polyline_int;
	
	// Использование конструктора по умолчанию
	Polyline<int> polyline_default;
	cout << "polyline_default: " << endl;
	cout << polyline_default << endl;
	// Использование конструктора с указанием размера
	Polyline<int> polyline_with_size(5);
	cout << "polyline_with_size: " << endl;
	cout << polyline_with_size << endl;
	
	// Использование конструктора с размером и значениями
	Polyline<int> polyline_with_values(3, 1, 2);
	cout << "polyline_with_values: " << endl;
	cout << polyline_with_values << endl;
	// Использование конструктора копирования
	Polyline<int> polyline_copy(polyline_with_values);
	cout << "polyline_copy: " << endl;
	cout << polyline_copy << endl;

	// Добавление точки в Polyline
	Point<int> new_point(3, 4);
	polyline_copy.add(new_point);
	cout << "polyline_add_point: " << endl;
	cout << polyline_copy << endl;

	// Использование оператора []
	cout << "retrieved_point: " << endl;
	cout << polyline_copy[3] << endl;

	// Использование оператора сложения Polyline
	Polyline<int> other_polyline;
	Polyline<int> combined_polyline = polyline_with_values + polyline_copy;
	cout << "combined_polyline: " << endl;
	cout << combined_polyline << endl;

	// Использование оператора сложения точки с Polyline в начало
	Polyline<int> point_polyline = combined_polyline - new_point;
	cout << "point_polyline: " << endl;
	cout << point_polyline << endl;
	// Использование оператора сложения точки с Polyline в конец !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Polyline<int> polyline_point = combined_polyline + new_point;
	cout << "polyline_point: " << endl;
	cout << polyline_point << endl;

	// Вычисление длины Polyline
	double combined_polyline_poly_length = combined_polyline.length();
	cout << "combined_polyline_poly_length: " << endl;
	cout << combined_polyline_poly_length << endl;

	// Создание правильного многоугольника
	Polyline<int> polygon;
	polygon.createRegularPolygon(4, 2);
	cout << "Coordinates of the regular polygon: " << endl;
	cout << polygon << endl;



	return 0;
}



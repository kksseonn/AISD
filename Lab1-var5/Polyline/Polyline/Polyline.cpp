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
	Polyline() : points(nullptr), size(0) {}
	Polyline(int _size) : size(_size) {
		points = new Point<T>[size];
	}
	Polyline(Polyline<T>& other) {
		size = other.size;
		points = new Point<T>[size];
		for (int i = 0; i < size; ++i)
		{
			points[i] = other[i];
		}
	}
	Polyline(int _size, const T& m1, const T& m2) : size(_size) {
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
	~Polyline() {
		delete[] points;
	}

	void add(const Point<T>& point) {
		Point<T>* newElements = new Point<T>[size + 1];
		for (int i = 0; i < size; ++i) {
			newElements[i] = points[i];
		}
		newElements[size] = point;
		delete[] points;
		points = newElements;
		size += 1;
	}

	Point<T>& operator[](const int& index) {
		return points[index];
	}
	Polyline<T>& operator+(const Polyline<T>& other) {
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
	Polyline<T>& operator-(const Point<T>& point) {
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
	Polyline<T>& operator+(const Point<T>& point) {
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

	double length() const {
		double totalLength = 0.0;
		for (int i = 0; i < size - 1; i++) {
			// Расстояние между точками i и i+1
			T dx = points[i + 1].x - points[i].x;
			T dy = points[i + 1].y - points[i].y;

			double segmentLength;

			segmentLength = sqrt(static_cast<double>(dx * dx + dy * dy));

			totalLength += segmentLength;
		}
		return totalLength;
	}

	friend ostream& operator<<(ostream& os, const Polyline<T>& polyline) {
		for (int i = 0; i < polyline.size; i++) {
			os << "(" << polyline.points[i].x << ", " << polyline.points[i].y << ") ";
		}
		return os;
	}
};

template<typename T>
struct Point<complex<T>> {
	complex<T> x;
	complex<T> y;
	Point() : x(0.0), y(0.0) {}
	Point(complex<T> _x, complex<T> _y) : x(_x), y(_y) {}
	friend ostream& operator<<(ostream& os, const Point<complex<T>>& point) {
		os << "(" << point.x << ", " << point.y << ") ";
		return os;
	}
};

template<typename T>
class Polyline<complex<T>> {
	Point<complex<T>>* points;
	int size;
public:
	Polyline() : points(nullptr), size(0) {};
	Polyline(int _size) : size(_size) {
		points = new Point<complex<T>>[size];
	}
	Polyline(Polyline<complex<T>>& other) {
		size = other.size;
		points = new Point<complex<T>>[size];
		for (int i = 0; i < size; ++i){
			points[i] = other[i];
		}
	}
	Polyline(int _size, const complex<T>& m1, const complex<T>& m2) : size(_size) {
		points = new Point<complex<T>>[size];
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<T> real_distrib(m1.real(), m2.real());
		uniform_real_distribution<T> imag_distrib(m1.imag(), m2.imag());
		for (int i = 0; i < size; i++) {
			complex<T> random_X = real_distrib(gen);
			complex<T> randomX = imag_distrib(gen);
			complex<T> random_Y = real_distrib(gen);
			complex<T> randomY = imag_distrib(gen);
			points[i] = Point<complex<T>>((random_X, randomX), (random_Y, randomY));
		}
	}
	~Polyline() {
		delete[] points;
	}

	void add(const Point<complex<T>>& point) {
		Point<complex<T>>* newElements = new Point<complex<T>>[size + 1];
		for (int i = 0; i < size; ++i) {
			newElements[i] = points[i];
		}
		newElements[size] = point;
		delete[] points;
		points = newElements;
		size += 1;
	}

	Point<complex<T>>& operator[](const int& index) {
		return points[index];
	}
	Polyline<complex<T>>& operator+(const Polyline<complex<T>>& other) {
		int newSize = size + other.size;
		Point<complex<T>>* newPoints = new Point<complex<T>>[newSize];
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
	Polyline<complex<T>>& operator-(const Point<complex<T>>& point) {
		Point<complex<T>>* newPoints = new Point<complex<T>>[size + 1];
		newPoints[0] = point;
		for (int i = 0; i < size; i++) {
			newPoints[i + 1] = points[i];
		}
		delete[] points;
		points = newPoints;
		size++;
		return *this;
	}

	Polyline<complex<T>>& operator+(const Point<complex<T>>& point) {
		Point<complex<T>>* newPoints = new Point<complex<T>>[size + 1];
		for (int i = 0; i < size; i++) {
			newPoints[i] = points[i];
		}
		newPoints[size] = point;
		delete[] points;
		points = newPoints;
		size++;
		return *this;
	}

	double length() const {
		double totalLength = 0.0;
		for (int i = 0; i < size - 1; i++) {
			// Расстояние между точками i и i+1
			complex<T> dx = points[i + 1].x - points[i].x;
			complex<T> dy = points[i + 1].y - points[i].y;

			double segmentLength;

			segmentLength = abs(points[i + 1].x - points[i].x);
			segmentLength += abs(points[i + 1].y - points[i].y);
			totalLength += segmentLength;
		}
		return totalLength;
	}
	
	friend ostream& operator<<(ostream& os, const Polyline<complex<T>>& polyline) {
		for (int i = 0; i < polyline.size; i++) {
			os << "(" << polyline.points[i].x << ", " << polyline.points[i].y << ") ";
		}
		return os;
	}
};

template<typename T>
void createRegularPolygon(int size, Point<T>* points) {
	if (size <= 2) {
		throw std::out_of_range("_size should be greater than 2");
	}
	else {
		const T radius = 2;
		const T centerX = 0;
		const T centerY = 0;
		for (int i = 0; i < size; i++) {
			points[i].x = centerX + radius * cos(2 * PI * i / size);
			points[i].y = centerY + radius * sin(2 * PI * i / size);
		}
	}
}

//
//template<typename T>
//void createRegularPolygon(int size, Point<complex<T>>* points) {
//	if (size <= 2) {
//		throw std::out_of_range("_size should be greater than 2");
//	}
//	else {
	//	
	//
	//	for (int i = 0; i < N; ++i) {
	//		T x = real(center) + radius * cos(2 * PI * i / N);
	//		T y = imag(center) + radius * sin(2 * PI * i / N);
	//		Point<complex<T>> p(complex<T>(x, y));
	//		polyline.add(p);
	//	}
	// 
//	return polyline;
//}

int main() {
	
	Polyline<int> polyline_int;
	Polyline<int> polyline_default;
	cout << "polyline_default: " << endl;
	cout << polyline_default << endl;

	Polyline<int> polyline_with_size(5);
	cout << "polyline_with_size: " << endl;
	cout << polyline_with_size << endl;

	Polyline<int> polyline_with_values(3, 1, 2);
	cout << "polyline_with_values: " << endl;
	cout << polyline_with_values << endl;

	Polyline<int> polyline_copy(polyline_with_values);
	cout << "polyline_copy: " << endl;
	cout << polyline_copy << endl;

	Point<int> new_point(8, 7);
	polyline_copy.add(new_point);
	cout << "polyline_add_point: " << endl;
	cout << polyline_copy << endl;

	cout << "retrieved_point: " << endl;
	cout << polyline_copy[3] << endl;

	Polyline<int> other_polyline;
	Polyline<int> combined_polyline = polyline_with_values + polyline_copy;
	cout << "combined_polyline: " << endl;
	cout << combined_polyline << endl;

	Polyline<int> point_polyline = combined_polyline - new_point;
	cout << "point_polyline: " << endl;
	cout << point_polyline << endl;
	
	Polyline<int> polyline_point = polyline_copy + new_point;
	cout << "polyline_point: " << endl;
	cout << polyline_point << endl;

	double combined_polyline_poly_length = combined_polyline.length();
	cout << "combined_polyline_poly_length: " << endl;
	cout << combined_polyline_poly_length << endl;

	// Создание правильного многоугольника
	Point<int>* points = new Point<int>[4];
	createRegularPolygon(4, points);
	cout << "Coordinates of the regular polygon: " << endl;
	for (int i = 0; i < 4; i++) {
		std::cout << points[i] << " ";
	}
	cout << "\n----------------------------------------------------" << endl;
	
	Point<complex<float>> complex_point1(complex<float>(1, 2), complex<float>(3, 4));
	cout << "complex_point1: " << endl;
	cout << complex_point1 << endl;

	Polyline<complex<float>> polyline_with_complex_values(2,complex<float>(-3, -4), complex<float>(1, 1));
	cout << "polyline_with_complex_values: " << endl;
	cout << polyline_with_complex_values << endl;

	Polyline<complex<float>> polyline_copy_complex(polyline_with_complex_values);
	cout << "polyline_copy_complex: " << endl;
	cout << polyline_copy_complex << endl;

	Point<complex<float>> complex_point2(complex<float>(1, 2), complex<float>(3, 4));
	polyline_copy_complex.add(complex_point2);
	cout << "polyline_add_complex_point: " << endl;
	cout << polyline_copy_complex << endl;

	cout << "retrieved_copmlex_point: " << endl;
	cout << polyline_copy_complex[3] << endl;

	Polyline<complex<float>> combined_complex_polyline = polyline_with_complex_values + polyline_copy_complex;
	cout << "combined_complex_polyline: " << endl;
	cout << combined_complex_polyline << endl;

	Polyline<complex<float>> complex_point_polyline = combined_complex_polyline - complex_point2;
	cout << "complex_point_polyline: " << endl;
	cout << complex_point_polyline << endl;

	Polyline<complex<float>> polyline_point_complex = combined_complex_polyline + complex_point2;
	cout << "polyline_point_complex: " << endl;
	cout << polyline_point_complex << endl;

	double combined_polyline_complex_poly_length = polyline_point_complex.length();
	cout << "combined_polyline_complex_poly_length: " << endl;
	cout << combined_polyline_complex_poly_length << endl;

	return 0;
}



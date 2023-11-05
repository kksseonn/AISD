#pragma once
#include <gtest/gtest.h>
#include <C:\Users\STNK\Desktop\AISD\Lab1-var5\src\polyline.cc>
#include <iostream>
#include <complex>
#include <stdexcept>
#include <random>
#include <cmath>
#include <vector>

// 1
TEST(PointTest, ConstructorsTest) {
    Point<int> _point;
    EXPECT_EQ(_point.get_x(), 0);
    EXPECT_EQ(_point.get_y(), 0);

    Point<float> i_point;
    EXPECT_NEAR(i_point.get_x(), 0, 0.00001);
    EXPECT_EQ(i_point.get_y(), 0, 0.00001);

    Point<double> b_point;
    EXPECT_EQ(b_point.get_x(), 0);
    EXPECT_EQ(b_point.get_y(), 0);

    Point<int> c_point(3, 4);
    EXPECT_EQ(c_point.get_x(), 3);
    EXPECT_EQ(c_point.get_y(), 4);

    Point<float> d_point(3.5, 4.5);
    EXPECT_NEAR(d_point.get_x(), 3.5, 0.0001);
    EXPECT_NEAR(d_point.get_y(), 4.5, 0.0001);

    Point<double> e_point(-3.5, 4.5);
    EXPECT_NEAR(e_point.get_x(), -3.5, 0.0001);
    EXPECT_NEAR(e_point.get_y(), 4.5, 0.0001);
}
//2
TEST(PointTest, GettersAndSetters) {
    Point<int> _point;
    _point.set_x(5);
    _point.set_y(10);
    EXPECT_EQ(_point.get_x(), 5);
    EXPECT_EQ(_point.get_y(), 10);

    Point<float> i_point;
    i_point.set_x(3.5);
    i_point.set_y(4.5);
    EXPECT_EQ(i_point.get_x(), 3.5);
    EXPECT_EQ(i_point.get_y(), 4.5);

    Point<double> b_point;
    b_point.set_x(-3.5);
    b_point.set_y(-4.5);
    EXPECT_EQ(b_point.get_x(), -3.5);
    EXPECT_EQ(b_point.get_y(), -4.5);
}
//3
TEST(PolylineTest, Constructors){
    Polyline<int> empty_polyline;
    EXPECT_EQ(empty_polyline.Size(), 0);

    Polyline<int> multiple_points_polyline(3);
    EXPECT_EQ(multiple_points_polyline.Size(), 3);

    Point<int> point1(3, 4);
    Polyline<int> polyline1;
    polyline1.add(point1);
    EXPECT_EQ(polyline1.Size(), 1);
    Polyline<int> polyline2(polyline1);
    EXPECT_EQ(polyline2.Size(), 1);
    
    Polyline<int> polyline3(3, 1, 10);
    EXPECT_EQ(polyline3.Size(), 3);
}
//4
TEST(PolylineTest, OperatorsTest) {
    Point<int> point1(3, 4);
    Polyline<int> polyline1;
    polyline1.add(point1);
    EXPECT_EQ(polyline1.Size(), 1);

    Point<int> p2(5, 6);
    Polyline<int> polyline2;
    polyline2.add(p2);
    EXPECT_EQ(polyline2[0].get_x(), 5);
    EXPECT_EQ(polyline2[0].get_y(), 6);

    Polyline<int> polyline3 = polyline1+ polyline2;
    EXPECT_EQ(polyline3.Size(), 2);

    Point<int> p3(6, 7);
    Polyline<int> polyline4 = polyline3 - p3;
    EXPECT_EQ(polyline4.Size(), 3);
    EXPECT_EQ(polyline4[2].get_x(), 6);
    EXPECT_EQ(polyline4[2].get_y(), 7);

    Polyline<int> polyline5 = polyline3 + p3;
    EXPECT_EQ(polyline5.Size(), 3);
    EXPECT_EQ(polyline5[0].get_x(), 6);
    EXPECT_EQ(polyline5[0].get_y(), 7);
}
//5
TEST(PolylineTest, LenghtTest) {
    Point<int> p1(1, 1);
    Point<int> p2(2, 2);
    Point<int> p3(3, 1);
    Polyline<int> polyline;
    polyline.add(p1);
    polyline.add(p2);
    polyline.add(p3);
    EXPECT_NEAR(polyline.length(), 2.83, 0.2);
}

TEST(PolylineTest, createRegularPolygonTest) {
    Polyline<double> polyline;
    polyline.createRegularPolygon(4, 2.0);  
    EXPECT_EQ(polyline.Size(), 4); 
    EXPECT_NEAR(polyline[0].get_x(), 2.0, 0.01);
    EXPECT_NEAR(polyline[0].get_y(), 0.0, 0.01);
    EXPECT_NEAR(polyline[1].get_x(), 0.0, 0.01);
    EXPECT_NEAR(polyline[1].get_y(), 2.0, 0.01);
    EXPECT_NEAR(polyline[2].get_x(), -2.0, 0.01);
    EXPECT_NEAR(polyline[2].get_y(), 0.0, 0.01);
    EXPECT_NEAR(polyline[3].get_x(), 0.0, 0.01);
    EXPECT_NEAR(polyline[3].get_y(), -2.0, 0.01);
}
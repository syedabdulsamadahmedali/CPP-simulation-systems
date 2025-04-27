#pragma once

class Vector2D {
public:
    double x;
    double y;

    Vector2D();
    Vector2D(double xVal, double yVal);

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(double scalar) const;
    Vector2D operator/(double scalar) const;

    double magnitude() const;
    Vector2D normalize() const;
};

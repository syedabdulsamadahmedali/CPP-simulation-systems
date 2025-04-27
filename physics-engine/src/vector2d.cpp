#include "vector2d.h"
#include <cmath>

Vector2D::Vector2D() : x(0), y(0) {}
Vector2D::Vector2D(double xVal, double yVal) : x(xVal), y(yVal) {}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(double scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(double scalar) const {
    return Vector2D(x / scalar, y / scalar);
}

double Vector2D::magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize() const {
    double mag = magnitude();
    if (mag == 0) return Vector2D(0, 0);
    return (*this) / mag;
}

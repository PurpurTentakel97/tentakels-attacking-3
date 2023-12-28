//
// Purpur Tentakel
// 08.08.2022
//

#pragma once
#include <cmath>
#include <stdexcept>
#include <string>


template<class T>
struct HVec2 final {
    T x, y;

    HVec2(T const x_, T const y_) : x{ x_ }, y{ y_ } { }

    HVec2(HVec2<T> const& toCopy) : x{ toCopy.x }, y{ toCopy.y } { }

    HVec2(HVec2&&) = default;
    HVec2& operator=(HVec2 const&) = default;
    HVec2& operator=(HVec2&&) = default;

    [[nodiscard]] HVec2<T> Normalize() const {
        double const length{ Length() };
        return { x / length, y / length };
    }

    [[nodiscard]] double Length() const {
        double const X{ static_cast<double>(x) };
        double const Y{ static_cast<double>(y) };
        return std::sqrt((X * X) + (Y * Y));
    }

    bool operator==(HVec2<T> const& other) const {
        return { x == other.x && y == other.y };
    }

    bool operator!=(HVec2<T> const& other) const {
        return { x != other.x or y != other.y };
    }

    HVec2<T> operator+(HVec2<T> const& other) const {
        return { x + other.x, y + other.y };
    }

    HVec2<T> operator-(HVec2<T> const& other) const {
        return { x - other.x, y - other.y };
    }

    HVec2<T> operator*(HVec2<T> const& other) const {
        return { x * other.x, y * other.y };
    }

    template<typename Scalar>
    HVec2<Scalar> To() const {
        static_assert(std::is_floating_point_v<Scalar>, "floating point required");
        return { static_cast<Scalar>(x), static_cast<Scalar>(y) };
    }

    [[nodiscard]] std::string ToString() const {
        return "X: " + std::to_string(x) + " Y: " + std::to_string(y);
    }
};

template<typename T>
HVec2<T> operator*(HVec2<T> const& vector, T const number) {
    return { vector.x * number, vector.y * number };
}

template<typename T>
HVec2<T> operator*(T const number, HVec2<T> const& vector) {
    return { vector * number };
}

template<typename T>
HVec2<T> operator/(HVec2<T> const& vector, T const number) {
    if (number == 0) {
        throw std::runtime_error("divide by zero");
    }
    return { vector.x / number, vector.y / number };
}

template<typename T>
inline HVec2<T> Abs(HVec2<T> const vec) {
    return { abs(vec.x), abs(vec.y) };
}

//
// Purpur Tentakel
// 08.08.2022
//

#pragma once

#include <cmath>
#include <stdexcept>
#include <string>

namespace utl {
    template<class T>
    struct Vec2 final {
        T x, y;

        Vec2(T const x_, T const y_) : x{ x_ }, y{ y_ } { }

        Vec2(Vec2<T> const& toCopy) : x{ toCopy.x }, y{ toCopy.y } { }

        Vec2(Vec2&&) = default;
        Vec2& operator=(Vec2 const&) = default;
        Vec2& operator=(Vec2&&) = default;

        [[nodiscard]] Vec2<T> Normalize() const {
            double const length{ Length() };
            return { x / length, y / length };
        }

        [[nodiscard]] double Length() const {
            double const X{ static_cast<double>(x) };
            double const Y{ static_cast<double>(y) };
            return std::sqrt((X * X) + (Y * Y));
        }

        bool operator==(Vec2<T> const& other) const {
            return { x == other.x && y == other.y };
        }

        bool operator!=(Vec2<T> const& other) const {
            return { x != other.x or y != other.y };
        }

        Vec2<T> operator+(Vec2<T> const& other) const {
            return { x + other.x, y + other.y };
        }

        Vec2<T> operator-(Vec2<T> const& other) const {
            return { x - other.x, y - other.y };
        }

        Vec2<T> operator*(Vec2<T> const& other) const {
            return { x * other.x, y * other.y };
        }

        template<typename Scalar>
        Vec2<Scalar> To() const {
            static_assert(std::is_floating_point_v<Scalar>, "floating point required");
            return { static_cast<Scalar>(x), static_cast<Scalar>(y) };
        }

        [[nodiscard]] std::string ToString() const {
            return "X: " + std::to_string(x) + " Y: " + std::to_string(y);
        }
    };

    template<typename T>
    Vec2<T> operator*(Vec2<T> const& vector, T const number) {
        return { vector.x * number, vector.y * number };
    }

    template<typename T>
    Vec2<T> operator*(T const number, Vec2<T> const& vector) {
        return { vector * number };
    }

    template<typename T>
    Vec2<T> operator/(Vec2<T> const& vector, T const number) {
        if (number == 0) {
            throw std::runtime_error("divide by zero");
        }
        return { vector.x / number, vector.y / number };
    }

    template<typename T>
    inline Vec2<T> Abs(Vec2<T> const vec) {
        return { abs(vec.x), abs(vec.y) };
    }
} // namespace utl

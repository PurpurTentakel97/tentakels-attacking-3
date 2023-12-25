//
// Purpur Tentakel
// 08.08.2022
//

#pragma once
#include <cmath>
#include <stdexcept>
#include <string>

/**
 * contains and manage 2 values.
 */
template<class T>
struct Vec2 final {
    T x, y; ///< contains the 2 values the Vec is holding,

    /**
	 * ctor.
	 * only initialisation.
	 */
    Vec2(T x_, T y_) : x{ x_ }, y{ y_ } { }
    /**
	 * generates a exact copy of the Vec.
	 */
    Vec2(Vec2<T> const& toCopy) : x{ toCopy.x }, y{ toCopy.y } { }

    Vec2(Vec2&&) = default;
    Vec2& operator=(Vec2 const&) = default;
    Vec2& operator=(Vec2&&) = default;

    /**
	 * returns a new Vec to match a length of 1 while not changing the direction.
	 */
    [[nodiscard]] Vec2<T> Normalize() const {
        double const length{ Length() };
        return { x / length, y / length };
    }
    /**
	 * returns the length of the Vec.
	 */
    [[nodiscard]] double Length() const {
        double const X{ static_cast<double>(x) };
        double const Y{ static_cast<double>(y) };
        return std::sqrt((X * X) + (Y * Y));
    }

    /**
	 * checks if the Vec are completely equal.
	 */
    bool operator==(Vec2<T> const& other) const {
        return { x == other.x && y == other.y };
    }
    /**
	 * check if the Vec are not equal.
	 */
    bool operator!=(Vec2<T> const& other) const {
        return { x != other.x or y != other.y };
    }
    /**
	 * adds to Vecs and returns a new one.
	 */
    Vec2<T> operator+(Vec2<T> const& other) const {
        return { x + other.x, y + other.y };
    }
    /**
	 * substracts to Vecs and returns a new one.
	 */
    Vec2<T> operator-(Vec2<T> const& other) const {
        return { x - other.x, y - other.y };
    }
    /**
	 * multiplies to Vecs and returns a new one.
	 */
    Vec2<T> operator*(Vec2<T> const& other) const {
        return { x * other.x, y * other.y };
    }

    /**
	 * generates new Vec with a new datatype and returns it.
	 */
    template<typename Scalar>
    Vec2<Scalar> To() const {
        static_assert(std::is_floating_point_v<Scalar>, "floating point required");
        return { static_cast<Scalar>(x), static_cast<Scalar>(y) };
    }
    /**
	 * returns a string representation of the Vec.
	 */
    [[nodiscard]] std::string ToString() const {
        return "X: " + std::to_string(x) + " Y: " + std::to_string(y);
    }
};

/**
 * multiplies a Vec with a number and returns a new Vec.
 */
template<typename T>
Vec2<T> operator*(Vec2<T> const& vector, T const number) {
    return { vector.x * number, vector.y * number };
}
/**
 * multiplies a number with a Vec and returns a new Vec.
 */
template<typename T>
Vec2<T> operator*(T const number, Vec2<T> const& vector) {
    return { vector * number };
}

/**
 * divides a Vec with a number and returns a new Vec.
 * if divide by zero: an exception is thrown.
 */
template<typename T>
Vec2<T> operator/(Vec2<T> const& vector, T const number) {
    if (number == 0) {
        throw std::runtime_error("divide by zero");
    }
    return { vector.x / number, vector.y / number };
}

/**
 * returns a positive vector.
 */
template<typename T>
inline Vec2<T> Abs(Vec2<T> vec) {
    return { abs(vec.x), abs(vec.y) };
}

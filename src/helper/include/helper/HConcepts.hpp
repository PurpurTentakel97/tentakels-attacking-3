//
// PurpurTentakel
// 22.11.22
//

#pragma once
#include <concepts>

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

template<typename T, typename... U>
concept AnyOf = std::disjunction_v<std::is_same<T, U>...>;
template<typename T>
concept CellValueType = AnyOf<T, int, double, std::monostate, std::string, Color>;

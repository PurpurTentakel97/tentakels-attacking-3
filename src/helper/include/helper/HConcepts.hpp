//
// PurpurTentakel
// 22.11.22
//

#pragma once
#include <concepts>

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

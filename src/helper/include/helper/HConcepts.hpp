//
// PurpurTentakel
// 22.11.22
//

#pragma once
#include <concepts>

/**
 * concepts for a template parameter to be only a arithmetic datatype.
 */
template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

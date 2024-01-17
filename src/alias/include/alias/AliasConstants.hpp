//
// Purpur Tentakel
// 28.12.2023
//

#pragma once

namespace cst {

    struct Window;
    using Window_ty   = Window&;
    using Window_ty_c = Window const&;


    enum class Resolution;
    // Resolution alias in raylib alias because it is not possible to forward declare a Vector2.

} // namespace cst

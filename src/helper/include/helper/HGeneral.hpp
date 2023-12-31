//
// Purpur Tentakel
// 05.09.2022
//

#pragma once

#include <CustomRaylib.hpp>
#include <alias/AliasUtils.hpp>
#include <cstddef>


namespace hlp {
    // Position
    Vector2 GetElementPosition(Vector2 const& pos, Vector2 const& size, float x, float y);

    Vector2 GetElementPositionReversed(Vector2 const& posP, Vector2 const& sizeP, Vector2 const& posC);

    Vector2 GetElementSize(Vector2 const& size, float x, float y);

    Vector2 GetElementSizeReversed(Vector2 const& sizeP, Vector2 const& sizeC);

    // Index
    utl::usize GetIndexFromRowAndColumn(utl::usize row, utl::usize column, utl::usize maxColumn);
} // namespace hlp

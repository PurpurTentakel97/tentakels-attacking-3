//
// Purpur Tentakel
// 05.09.2022
//

#include "HGeneral.hpp"

namespace hlp {
    // Position
    Vector2 GetElementPosition(Vector2 const& pos, Vector2 const& size, float const x, float const y) {
        return { pos.x + x * size.x, pos.y + y * size.y };
    }

    Vector2 GetElementPositionReversed(Vector2 const& posP, Vector2 const& sizeP, Vector2 const& posC) {
        return { (posC.x - posP.x) / sizeP.x, (posC.y - posP.y) / sizeP.y };
    }

    Vector2 GetElementSize(Vector2 const& size, float const x, float const y) {
        return { x * size.x, y * size.y };
    }

    Vector2 GetElementSizeReversed(Vector2 const& sizeP, Vector2 const& sizeC) {
        return { sizeC.x / sizeP.x, sizeC.y / sizeP.y };
    }

    // Index
    utl::usize GetIndexFromRowAndColumn(utl::usize const row, utl::usize const column, utl::usize const maxColumn) {
        return row * maxColumn + column;
    }
} // namespace hlp

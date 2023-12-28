//
// Purpur Tentakel
// 18.09.2022
//

#include "Alignment.hpp"
#include <AppContext.hpp>

Rectangle GetAlignedCollider(Vector2& pos, Vector2 size, Alignment alignment) {
    Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
    switch (alignment) {
        case Alignment::TOP_LEFT:
        case Alignment::DEFAULT:
        default:
            // no adjustment of x necessary
            // no adjustment of y necessary
            break;
        case Alignment::TOP_MID:
            pos.x -= size.x / 2;
            // no adjustment of y necessary
            break;
        case Alignment::TOP_RIGHT:
            pos.x -= size.x;
            // no adjustment of y necessary
            break;
        case Alignment::MID_LEFT:
            // no adjustment of x necessary
            pos.y -= size.y / 2;
            break;
        case Alignment::MID_MID:
            pos.x -= size.x / 2;
            pos.y -= size.y / 2;
            break;
        case Alignment::MID_RIGHT:
            pos.x -= size.x;
            pos.y -= size.y / 2;
            break;
        case Alignment::BOTTOM_LEFT:
            // no adjustment of x necessary
            pos.y -= size.y;
            break;
        case Alignment::BOTTOM_MID:
            pos.x -= size.x / 2;
            pos.y -= size.y;
            break;
        case Alignment::BOTTOM_RIGHT:
            pos.x -= size.x;
            pos.y -= size.y;
            break;
    }
    return { resolution.x * pos.x, resolution.y * pos.y, resolution.x * size.x, resolution.y * size.y };
}

Vector2 GetAlignedPosition(Alignment alignment, Vector2 position, Vector2 size) {
    switch (alignment) {
        case Alignment::TOP_LEFT:
        case Alignment::DEFAULT:
        default:
            // no adjustment of x necessary
            // no adjustment of y necessary
            break;
        case Alignment::TOP_MID:
            position.x -= size.x / 2;
            // no adjustment of y necessary
            break;
        case Alignment::TOP_RIGHT:
            position.x -= size.x;
            // no adjustment of y necessary
            break;
        case Alignment::MID_LEFT:
            // no adjustment of x necessary
            position.y -= size.y / 2;
            break;
        case Alignment::MID_MID:
            position.x -= size.x / 2;
            position.y -= size.y / 2;
            break;
        case Alignment::MID_RIGHT:
            position.x -= size.x;
            position.y -= size.y / 2;
            break;
        case Alignment::BOTTOM_LEFT:
            // no adjustment of x necessary
            position.y -= size.y;
            break;
        case Alignment::BOTTOM_MID:
            position.x -= size.x / 2;
            position.y -= size.y;
            break;
        case Alignment::BOTTOM_RIGHT:
            position.x -= size.x;
            position.y -= size.y;
            break;
    }

    return position;
}

Vector2 GetAlignedPositionReversed(Alignment alignment, Vector2 position, Vector2 size) {
    switch (alignment) {
        case Alignment::TOP_LEFT:
        case Alignment::DEFAULT:
        default:
            // no adjustment of x necessary
            // no adjustment of y necessary
            break;
        case Alignment::TOP_MID:
            position.x += size.x / 2;
            // no adjustment of y necessary
            break;
        case Alignment::TOP_RIGHT:
            position.x += size.x;
            // no adjustment of y necessary
            break;
        case Alignment::MID_LEFT:
            // no adjustment of x necessary
            position.y += size.y / 2;
            break;
        case Alignment::MID_MID:
            position.x += size.x / 2;
            position.y += size.y / 2;
            break;
        case Alignment::MID_RIGHT:
            position.x += size.x;
            position.y += size.y / 2;
            break;
        case Alignment::BOTTOM_LEFT:
            // no adjustment of x necessary
            position.y += size.y;
            break;
        case Alignment::BOTTOM_MID:
            position.x += size.x / 2;
            position.y += size.y;
            break;
        case Alignment::BOTTOM_RIGHT:
            position.x += size.x;
            position.y += size.y;
            break;
    }

    return position;
}

TextAlignment GetHorizontalTextAlignment(Alignment alignment) {
    switch (alignment) {
        case Alignment::TOP_LEFT:
        case Alignment::MID_LEFT:
        case Alignment::BOTTOM_LEFT:
        case Alignment::DEFAULT:
        default:
            return TextAlignment::LEFT;

        case Alignment::TOP_MID:
        case Alignment::MID_MID:
        case Alignment::BOTTOM_MID:
            return TextAlignment::MID;

        case Alignment::TOP_RIGHT:
        case Alignment::MID_RIGHT:
        case Alignment::BOTTOM_RIGHT:
            return TextAlignment::RIGHT;
    }
}

TextAlignment GetVerticalTextAlignment(Alignment alignment) {
    switch (alignment) {
        case Alignment::TOP_LEFT:
        case Alignment::TOP_MID:
        case Alignment::TOP_RIGHT:
        case Alignment::DEFAULT:
        default:
            return TextAlignment::TOP;

        case Alignment::MID_LEFT:
        case Alignment::MID_MID:
        case Alignment::MID_RIGHT:
            return TextAlignment::MID;

        case Alignment::BOTTOM_LEFT:
        case Alignment::BOTTOM_MID:
        case Alignment::BOTTOM_RIGHT:
            return TextAlignment::BOTTOM;
    }
}

//
// Purpur Tentakel
// 16.02.2024
//

#include "BlackHole.hpp"
#include <app/AppContext.hpp>

namespace lgk {
    BlackHole::BlackHole(utl::usize ID, utl::vec2pos_ty_ref_c position, Player_ty_c player, utl::usize startExtraSize)
        : SpaceObject{ ID, position, player },
          m_extraSize{ startExtraSize } { }

    bool BlackHole::IsBlackHole() const {
        return true;
    }

    void BlackHole::AddExtraSize(SpaceObject_ty_c object) {
        m_extraSize += object->GetShipCount();
        if (object->IsPlanet()) {
            m_extraSize += 100;
        }
    }

    utl::usize BlackHole::ExtraSize() const {
        return m_extraSize / 100;
    }

    utl::usize BlackHole::Size(int const galaxyWidth) const {
        auto const& constants = app::AppContext::GetInstance().constants.g_game_events;
        auto const size =
                static_cast<utl::usize>((constants.get_min_black_hole_range_factor() * static_cast<float>(galaxyWidth))) + ExtraSize();
        auto const maxSize = static_cast<utl::usize>(constants.get_max_black_hole_range_factor() * static_cast<float> (galaxyWidth));
        // clang-format off
        return constants.get_is_max_black_hole_range_factor() and size > maxSize
                     ? maxSize
                     : size;
        // clang-format on
    }

    void BlackHole::Update(Galaxy_ty_raw) { }
} // namespace lgk

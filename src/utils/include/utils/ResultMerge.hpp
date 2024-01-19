//
// Purpur Tentakel
// 09.06.2023
//

#pragma once

#include "RepresentationPlayer.hpp"
#include "RepresentationSpaceObject.hpp"
#include <alias/AliasUtils.hpp>

namespace utl {
    struct ResultMerge final {
    private:
        RepresentationPlayer m_player;
        RepresentationSpaceObject m_origin;
        RepresentationSpaceObject m_destination;
        usize m_count;

    public:
        ResultMerge(RepresentationPlayer player,
                    RepresentationSpaceObject origin,
                    RepresentationSpaceObject destination,
                    usize count);

        [[nodiscard]] RepresentationPlayer GetPlayer() const;
        [[nodiscard]] RepresentationSpaceObject GetOrigin() const;
        [[nodiscard]] RepresentationSpaceObject GetDestination() const;
        [[nodiscard]] usize GetCount() const;
    };
} // namespace utl

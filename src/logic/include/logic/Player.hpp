//
// PurpurTentakel
// 10.08.22
//

#pragma once

#include "PlayerType.hpp"
#include <alias/AliasUtils.hpp>


namespace lgk {
    class Player final {
    private:
        utl::usize m_ID;
        PlayerType m_playerType;
        bool m_isAlive{ true };

    public:
        Player(utl::usize ID, PlayerType playerType);

        [[nodiscard]] bool IsHumanPlayer() const;

        [[nodiscard]] utl::usize GetID() const;

        [[nodiscard]] bool IsAlive() const;

        void Kill();

        void Revive();

        friend bool operator==(Player const& lhs, Player const& rhs);
    };
} // namespace lgk

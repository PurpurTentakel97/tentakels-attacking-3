//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "PlayerType.hpp"

class Player final {
private:
    unsigned int m_ID;
    PlayerType m_playerType;
    bool m_isAlive{ true };

public:
    Player(unsigned int ID, PlayerType playerType);

    [[nodiscard]] bool IsHumanPlayer() const;

    [[nodiscard]] unsigned int GetID() const;

    [[nodiscard]] bool IsAlive() const;

    void Kill();

    void Revive();

    friend bool operator==(Player const& lhs, Player const& rhs);
};

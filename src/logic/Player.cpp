//
// PurpurTentakel
// 10.08.22
//

#include "Player.hpp"


namespace lgk {
    Player::Player(unsigned int const ID, PlayerType const playerType) : m_ID{ ID }, m_playerType{ playerType } { }

    bool Player::IsHumanPlayer() const {
        return m_playerType == PlayerType::HUMAN;
    }

    unsigned int Player::GetID() const {
        return m_ID;
    }

    bool Player::IsAlive() const {
        return m_isAlive;
    }

    void Player::Kill() {
        m_isAlive = false;
    }

    void Player::Revive() {
        m_isAlive = true;
    }

    bool operator==(Player const& lhs, Player const& rhs) {
        return lhs.m_ID == rhs.m_ID;
    }
} // namespace lgk

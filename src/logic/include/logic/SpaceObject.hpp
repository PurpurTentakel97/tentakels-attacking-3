//
// Purpur Tentakel
// 06.11.2022
//

#pragma once
#include "utils/Vec2.hpp"
#include <helper/HLogicAlias.hpp>
#include <memory>
#include <string>


class SpaceObject {
protected:
    unsigned int m_ID;
    size_t m_ships;
    utl::vec2pos_ty m_position;
    Player_ty m_player;
    bool m_isDiscovered{ false };

    [[nodiscard]] static bool IsInRange(SpaceObject_ty_raw first, SpaceObject_ty_raw second, int range);

public:
    SpaceObject(unsigned int ID, utl::vec2pos_ty_ref_c position, Player_ty_c player);

    SpaceObject(unsigned int ID, utl::vec2pos_ty position, size_t ships, Player_ty player);

    virtual ~SpaceObject() = default;

    void TransferShipsFrom(SpaceObject* origin);

    virtual void Update(Galaxy_ty_raw galaxy) = 0;

    [[nodiscard]] unsigned int GetID() const;

    void SetPlayer(Player_ty player);

    [[nodiscard]] Player_ty GetPlayer() const;

    void SetPos(utl::vec2pos_ty_ref_c pos);

    [[nodiscard]] utl::vec2pos_ty GetPos() const;

    void SetShipCount(size_t shipCount);

    [[nodiscard]] size_t GetShipCount() const;

    [[nodiscard]] virtual bool IsPlanet() const;

    [[nodiscard]] virtual bool IsFleet() const;

    [[nodiscard]] virtual bool IsTargetPoint() const;

    [[nodiscard]] bool IsInDiscoverRange(SpaceObject_ty_c object) const;

    [[nodiscard]] bool IsInFightRange(SpaceObject_ty_c object) const;

    void SetDiscovered(bool isDiscovered);

    [[nodiscard]] bool IsDiscovered() const;

    friend size_t operator+(SpaceObject const& object, size_t ships);

    friend size_t operator+(size_t ships, SpaceObject const& object);

    friend size_t operator+(SpaceObject const& lhs, SpaceObject const& rhs);

    friend size_t operator-(SpaceObject const& object, size_t ships);

    friend size_t operator-(size_t ships, SpaceObject const& object);

    friend size_t operator-(SpaceObject const& lhs, SpaceObject const& rhs);

    friend bool operator<(SpaceObject const& object, size_t ships);

    friend bool operator<(size_t ships, SpaceObject const& object);

    friend bool operator<(SpaceObject const& lhs, SpaceObject const& rhs);

    friend bool operator<=(SpaceObject const& object, size_t ships);

    friend bool operator<=(size_t ships, SpaceObject const& object);

    friend bool operator<=(SpaceObject const& lhs, SpaceObject const& rhs);

    friend bool operator>(SpaceObject const& object, size_t ships);

    friend bool operator>(size_t ships, SpaceObject const& object);

    friend bool operator>(SpaceObject const& lhs, SpaceObject const& rhs);

    friend bool operator>=(SpaceObject const& object, size_t ships);

    friend bool operator>=(size_t ships, SpaceObject const& object);

    friend bool operator>=(SpaceObject const& lhs, SpaceObject const& rhs);

    SpaceObject& operator+=(size_t ships);

    SpaceObject& operator+=(SpaceObject const& object);

    SpaceObject& operator-=(size_t ships);

    SpaceObject& operator-=(SpaceObject const& object);

    [[nodiscard]] bool operator==(SpaceObject const& other) const;
};

[[nodiscard]] size_t operator+(SpaceObject const& object, size_t ships);
[[nodiscard]] size_t operator+(size_t ships, SpaceObject& object);
[[nodiscard]] size_t operator+(SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] size_t operator-(SpaceObject const& object, size_t ships);
[[nodiscard]] size_t operator-(size_t ships, SpaceObject const& object);
[[nodiscard]] size_t operator-(SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator<(SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator<(size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator<(SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator<=(SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator<=(size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator<=(SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator>(SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator>(size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator>(SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator>=(SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator>=(size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator>=(SpaceObject const& lhs, SpaceObject const& rhs);
